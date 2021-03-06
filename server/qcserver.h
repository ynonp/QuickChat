#ifndef QCSERVER_H
#define QCSERVER_H

#include <QObject>
#include <QHash>
class QTcpSocket;

class QCServer : public QObject
{
    Q_OBJECT
public:
    explicit QCServer(QObject *parent = 0);

signals:

private slots:
    void onNewConnection();
    void dataReady();

    void broadcastMsg(const QString &msg, QTcpSocket *sendingSocket);
    void sendClientListToAllConnectedClients();
    void handleClientDisconnected();

private:
    void respondTo(QTcpSocket *remote, const QString &cmd, const QString &args);
    void sendClientList(QTcpSocket *remote);
    QString findAvailableUsername(const QString &base);

private:
    QHash<QString, QTcpSocket *> iClients;
};

#endif // QCSERVER_H
