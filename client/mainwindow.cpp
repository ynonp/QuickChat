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

    QObject::connect(ui->actionSet_Username, SIGNAL(triggered()),
                     this, SLOT(setUsername()));

    QObject::connect(ui->btnConnect, SIGNAL(clicked()),
                     this, SLOT(connect()));

    QObject::connect(ui->edtMsg, SIGNAL(returnPressed()),
                     this, SLOT(sendMsg()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUsername()
{
    QString username = QInputDialog::getText(this, tr("Username"), tr("Type in your username"));
    QSettings settings;

    settings.setValue(PeersMgr::kKeyUsername, username);
}

void MainWindow::connect()
{
    if ( iConnected )
    {
        disconnect();
    }
    else
    {
        QHostAddress addr(ui->edtAddress->text());
        quint16 port = ui->spnPort->value();

        delete iPeersModel;
        iPeersModel = new PeersMgr(addr, port, this);
        ui->lstFriends->setModel(iPeersModel);

        QObject::connect(iPeersModel, SIGNAL(connected()),
                         this, SLOT(onConnectOK()));

        QObject::connect(iPeersModel, SIGNAL(newBroadcastMsg(QString,QString)),
                         this, SLOT(addChatLine(QString,QString)));

        ui->btnConnect->setDisabled(true);
        ui->edtAddress->setDisabled(true);
        ui->spnPort->setDisabled(true);
    }


}

void MainWindow::onConnectOK()
{
    ui->btnConnect->setText(tr("Disconnect"));
    iConnected = true;
    ui->btnConnect->setDisabled(false);
}

void MainWindow::disconnect()
{
    ui->lstFriends->setModel(NULL);
    delete iPeersModel;
    iPeersModel = NULL;
    iConnected = false;
    ui->edtAddress->setEnabled(true);
    ui->spnPort->setEnabled(true);
    ui->btnConnect->setText(tr("Connect"));
}

void MainWindow::sendMsg()
{
    if ( iPeersModel )
    {
        QString msg = ui->edtMsg->text();
        iPeersModel->broadcastMsg(msg);
        QSettings settings;
        QString username = settings.value(PeersMgr::kKeyUsername, PeersMgr::kDefaultUsername).toString();
        addChatLine(username, msg);
    }

    ui->edtMsg->clear();
}

void MainWindow::addChatLine(QString sender, QString content)
{
    ui->txtChat->append(QString("<b>%1: </b>%2").arg(sender, content));
}

