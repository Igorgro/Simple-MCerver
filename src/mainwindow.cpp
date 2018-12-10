#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "warndialog.h"
#include "settings.h"

#include <iostream>
#include <QCloseEvent>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    processing_thread (),
    _serv_thread (),
    stopped_icon (":/images/cross.png"),
    starting_icon (":/images/arrow.png"),
    running_icon (":/images/tick.png"),
    join_sound (":/sounds/join_sound.wav")
{
    ui->setupUi(this);
    connect_slots();

    init_gui();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    //warn if user haven't stoped server
    if (_serv_thread.is_running())
    {
        WarnDialog ewd (this, QString("Stop server before exiting Simple MCerver"));
        ewd.exec();
        event->ignore();
    }
    else
    {
       processing_thread.stop();
       Settings::getInstance()->save_to_disk();

       event->accept();
    }

}

void MainWindow::connect_slots()
{
    connect(&processing_thread, SIGNAL(server_running()), this, SLOT(gui_server_running()));
    connect(&processing_thread, SIGNAL(print_info (QString)), this, SLOT(gui_log_print_info(QString)));
    connect(&processing_thread, SIGNAL(print_warn (QString)), this, SLOT(gui_log_print_warn(QString)));
    connect(&processing_thread, SIGNAL(print_error(QString)), this, SLOT(gui_log_print_error(QString)));
    connect(&processing_thread, SIGNAL(make_player_online(QString)), this, SLOT(gui_make_player_online(QString)));
    connect(&processing_thread, SIGNAL(make_player_offline(QString)), this, SLOT(gui_make_player_offline(QString)));
    connect(&processing_thread, SIGNAL(make_player_opped(QString)), this, SLOT(gui_make_player_opped(QString)));
    connect(&processing_thread, SIGNAL(make_player_deopped(QString)), this, SLOT(gui_make_player_deopped(QString)));
    connect(&processing_thread, SIGNAL(make_player_banned(QString)), this, SLOT(gui_make_player_banned(QString)));
    connect(&processing_thread, SIGNAL(make_player_unbanned(QString)), this, SLOT(gui_make_player_unbanned(QString)));

    connect(&_serv_thread, SIGNAL(server_stoped()), this, SLOT(gui_server_stoped()));
    connect(&_serv_thread, SIGNAL(server_starting()), this, SLOT(gui_server_starting()));

}


void MainWindow::init_gui()
{
    unsigned long long ram_k = 0;
    GetPhysicallyInstalledSystemMemory(&ram_k);
    int ram_m = static_cast<int>(ram_k/1024);
    ui->ram_slider->setMaximum(ram_m);
    ui->ram_max_label->setText(QString::number(ram_m));

    gui_load_settings();
    gui_update_jars();
    gui_load_banned_players();
    gui_load_server_properties();
    gui_load_worlds();
    ui->online_players_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->online_players_list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_online_players_list_menu_requested(QPoint)));

    ui->worlds_list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect (ui->worlds_list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_worlds_list_menu_requested(QPoint)));

    ui->tabWidget->setTabEnabled(3, false);
    ui->tabWidget->setTabEnabled(4, false);


}




