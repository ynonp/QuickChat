#include "peersmgr.h"

PeersMgr::PeersMgr(QObject *parent) :
    QAbstractListModel(parent)
{
}


int PeersMgr::rowCount()
{
    return 0;
}

QVariant PeersMgr::data(const QModelIndex &index, int role) const
{
    return QVariant::Invalid;
}

void PeersMgr::broadcastMsg(QString *msg)
{
}

