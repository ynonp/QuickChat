#include "qcserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QRegExp>

QCServer::QCServer(QObject *parent) :
    QObject(parent)
{
    QTcpServer *server = new QTcpServer(this);
    if ( ! server->listen(QHostAddress::Any, 1234) )
    {
        qDebug() << "Failed to bind port: 1234";
        return;
    }

    QObject::connect(server, SIGNAL(newConnection()),
                     this, SLOT(onNewConnection()));
    qDebug() << "Listening on: 1234";
}

void QCServer::onNewConnection()
{
    qDebug() << "New COnnection !";
    QTcpServer *server = qobject_cast<QTcpServer *>(sender());
    if ( ! server )
    {
        qDebug() << "onNewConnection called with invalid sender";
        return;
    }

    while (server->hasPendingConnections())
    {
        QTcpSocket *pending = server->nextPendingConnection();
        QObject::connect(pending, SIGNAL(readyRead()),
                         this, SLOT(dataReady()));
    }
}


void QCServer::dataReady()
{
    QTcpSocket *sock = qobject_cast<QTcpSocket *>(sender());

    if ( ! sock )
    {
        qDebug() << "dataReady called with invalid sender";
        return;
    }

    QDataStream channel(sock);
    QString msg;

    channel >> msg;
    while ( ! msg.isEmpty() )
    {
        qDebug() << "read: " << msg;

        QRegExp parser("^(hello|ls|send)(?:$|[ ]*([^ ].*)$)");
        if ( parser.indexIn(msg) >= 0 )
        {
            QString cmd = parser.cap(1);
            QString params = parser.cap(2);
            respondTo(sock, cmd, params);
        }
        channel >> msg;
    }
}



void QCServer::broadcastMsg(const QString &msg, QTcpSocket *sendingSocket)
{
    QHashIterator<QString, QTcpSocket *> i(iClients);
    while ( i.hasNext() )
    {
        i.next();
        if ( i.value() !=  sendingSocket )
        {
            QDataStream remote(i.value());
            remote << QString("send") << i.key() << msg;
        }
    }

}

void QCServer::respondTo(QTcpSocket *remote, const QString &cmd, const QString &args)
{
    qDebug() << cmd << args;
    if ( cmd == "hello" )
    {
        qDebug() << "New Client: " << args;
        iClients[args] = remote;
    }
    else if ( cmd == "send" )
    {
        qDebug() << "sending: " << args;
        broadcastMsg(args, remote);
    }
    else if ( cmd == "ls" )
    {
        QDataStream channel(remote);
        qDebug() << "Sending: " << iClients.keys();
        channel << QString("ls") << iClients.keys();
    }
}

