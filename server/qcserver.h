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

private:
    void respondTo(QTcpSocket *remote, const QString &cmd, const QString &args);

private:
    QHash<QString, QTcpSocket *> iClients;
};

#endif // QCSERVER_H
