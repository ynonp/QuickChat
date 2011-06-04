#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "peersmgr.h"
#include <QInputDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iPeersModel ( NULL )
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
