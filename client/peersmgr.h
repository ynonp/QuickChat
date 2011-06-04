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

    static QString kKeyUsername;
    static QString kDefaultUsername;

public slots:
    void broadcastMsg(const QString &msg);


signals:
    void connected();
    void newBroadcastMsg(QString sender, QString content);

protected:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private slots:

    void linkReady();
    void linkError(QAbstractSocket::SocketError);
    void byebye();
    void newServerMsg();

private:
    QTcpSocket *iLink;
    QList<QString> iData;
};

#endif // PEERSMGR_H
