#include "mainwindow.h"
#include "settings.h"
#include "operators.h"
#include "bannedplayers.h"
#include "serverproperties.h"
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("windowsvista"));

    Settings::getInstance();
    Operators::getInstance();
    BannedPlayers::getInstance();
    ServerProperties::getInstance();

    MainWindow w;

    w.show();

    return a.exec();
}
