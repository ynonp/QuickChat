#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "peersmgr.h"
#include <QInputDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iPeersModel ( NULL ),
    iConnected ( false )
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUsername()
{
}

void MainWindow::connect()
{
}

void MainWindow::onConnectOK()
{
}

void MainWindow::disconnect()
{
}

void MainWindow::sendMsg()
{
}

void MainWindow::addChatLine(QString sender, QString content)
{
}

