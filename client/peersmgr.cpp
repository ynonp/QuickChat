#include "peersmgr.h"
#include <QTcpSocket>
#include <QSettings>

QString PeersMgr::kDefaultUsername = "Anonymous";
QString PeersMgr::kKeyUsername = "username";

PeersMgr::PeersMgr(const QHostAddress &server, quint16 port, QObject *parent) :
    QAbstractListModel(parent)
{
}


int PeersMgr::rowCount(const QModelIndex &parent) const
{
}

QVariant PeersMgr::data(const QModelIndex &index, int role) const
{
}

void PeersMgr::broadcastMsg(const QString &msg)
{
}

void PeersMgr::linkReady()
{
}

void PeersMgr::linkError(QAbstractSocket::SocketError e)
{
}

void PeersMgr::byebye()
{
}

void PeersMgr::newServerMsg()
{
}


