#include <QtCore/QCoreApplication>
#include "qcserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    new QCServer;

    return a.exec();
}
