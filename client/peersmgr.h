#ifndef PEERSMGR_H
#define PEERSMGR_H

#include <QObject>
#include <QHash>
#include <QAbstractListModel>

class PeersMgr : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PeersMgr(QObject *parent = 0);

signals:


private slots:
    void broadcastMsg(QString *msg);

private:
    QList<Connection *> iFriends;
};

#endif // PEERSMGR_H
