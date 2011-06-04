#include "peersmgr.h"
#include <QTcpSocket>
#include <QSettings>

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
