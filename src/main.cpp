#include "mainwindow.h"
#include "settings.h"
#include "operators.h"
#include "bannedplayers.h"
#include "serverproperties.h"
#include "servermods.h"
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("windowsvista"));
    Settings::get_instance();
    Operators::getInstance();
    BannedPlayers::get_instance();
    ServerProperties::get_instance();
    ServerMods::get_instance();
    MainWindow w;

    w.show();

    return a.exec();
}
