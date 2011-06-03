#ifndef PEERSMGR_H
#define PEERSMGR_H

#include <QObject>
#include <QHash>
#include <QAbstractListModel>
#include <QHostAddress>

class Connection;
class QTcpSocket;

class PeersMgr : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PeersMgr(const QHostAddress &serverAddr, quint16 port, QObject *parent = 0);

protected:
    virtual int rowCount();
    virtual QVariant data(const QModelIndex &index, int role) const;
signals:


private slots:
    void broadcastMsg(QString *msg);

private:
    QTcpSocket *link;
};

#endif // PEERSMGR_H
