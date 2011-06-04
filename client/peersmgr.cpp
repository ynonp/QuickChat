#include "peersmgr.h"
#include <QTcpSocket>
#include <QSettings>

QString PeersMgr::kDefaultUsername = "Anonymous";
QString PeersMgr::kKeyUsername = "username";

PeersMgr::PeersMgr(const QHostAddress &server, quint16 port, QObject *parent) :
    QAbstractListModel(parent)
{
    iLink = new QTcpSocket(this);
    iLink->connectToHost(server, port);

    QObject::connect(iLink, SIGNAL(connected()),
                     this, SLOT(linkReady()));

    QObject::connect(iLink, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(linkError(QAbstractSocket::SocketError)));

    qDebug() << "trying to connect";
}


int PeersMgr::rowCount(const QModelIndex &parent) const
{
    return iData.length();
}

QVariant PeersMgr::data(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole )
    {
        return iData.at(index.row());
    }

    return QVariant::Invalid;
}

void PeersMgr::broadcastMsg(const QString &msg)
{
    QDataStream channel(iLink);
    channel << QString("send %1").arg(msg);
}

void PeersMgr::linkReady()
{
    QObject::connect(iLink, SIGNAL(disconnected()),
                     this, SLOT(byebye()));

    QObject::connect(iLink, SIGNAL(readyRead()),
                     this, SLOT(newServerMsg()));

    qDebug() << "link ready";
    emit connected();

    QSettings settings;
    QString username = settings.value(PeersMgr::kKeyUsername, PeersMgr::kDefaultUsername).toString();

    QDataStream channel(iLink);
    channel << QString("hello %1").arg(username);
}

void PeersMgr::linkError(QAbstractSocket::SocketError e)
{
    qDebug() << "Link error: " << e;
}

void PeersMgr::byebye()
{
    qDebug() << "socket disconnected";
}

void PeersMgr::newServerMsg()
{
    QDataStream channel(iLink);
    QString msgType;

    channel >> msgType;
    qDebug() << "server said: " << msgType;

    if ( msgType == "send" )
    {
        QString sender;
        QString msg;
        channel >> sender >> msg;

        emit newBroadcastMsg(sender, msg);
    }
    else if ( msgType == "ls" )
    {
        beginResetModel();
        channel >> iData;
        endResetModel();
    }
}


