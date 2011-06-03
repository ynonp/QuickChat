#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class PeersMgr;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setUsername();
    void connect();
    void disconnect();
    void onConnectOK();
    void sendMsg();

private:
    Ui::MainWindow *ui;
    PeersMgr       *iPeersModel;
    bool            iConnected;
};

#endif // MAINWINDOW_H
