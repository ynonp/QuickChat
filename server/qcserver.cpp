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

    QDataStream stream(sock);
    QString msg;

    stream >> msg;

    QRegExp parser("^(\\w+) (.*)$");
    if ( parser.indexIn(msg) >= 0 )
    {
        QString cmd = parser.cap(1);
        QString params = parser.cap(2);

        if ( cmd == "hello" )
        {
            iClients[params] = sock;
        }
        else if ( cmd == "send" )
        {
            qDebug() << "sending: " << params;
            QHashIterator<QString, QTcpSocket *> i(iClients);
            while ( i.hasNext() )
            {
                i.next();
                if ( i.value() != sock )
                {
                    QDataStream remote(i.value());
                    remote << i.key() << params;
                }
            }

        }
        else if ( cmd == "ls" )
        {
            stream << iClients.keys();
        }
    }
}
