#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "settings.h"
#include "operators.h"
#include "serverproperties.h"
#include "warndialog.h"
#include "servermods.h"
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QList>

//main tab
void MainWindow::on_start_button_clicked()
{
    if (Settings::get_instance()->get_jar().compare(QString("")))
    {
        ui->console_area->setText("");
        _serv_thread.start();
    }
    else WarnDialog (this, "No JAR specified").exec();
}

void MainWindow::on_stop_button_clicked()
{
    _serv_thread.soft_stop();
}

void MainWindow::on_kill_button_clicked()
{
    _serv_thread.force_stop();
}

void MainWindow::on_send_button_clicked()
{
    _serv_thread.send_command(ui->command_edit->text());
    ui->command_edit->setText("");
}

void MainWindow::on_command_edit_returnPressed()
{
    _serv_thread.send_command(ui->command_edit->text());
    ui->command_edit->setText("");
}

void MainWindow::on_log_level_box_currentTextChanged(const QString &arg1)
{
    Settings::get_instance()->set_log_level(Settings::string_to_log_level(arg1));
}

void MainWindow::on_export_log_button_clicked()
{
    QString save_path = QFileDialog::getSaveFileName (this, QString("Export log..."),
                                                      Settings::get_instance()->get_working_dir(),
                                                      QString ("Log files (*.log)"));
    if (save_path.length() > 0)
    {
        QFile log_file (save_path);
        log_file.open (QIODevice::WriteOnly);
        log_file.write (ui->console_area->toPlainText().toLocal8Bit());
        log_file.close ();
    }

}





//players tab
void MainWindow::on_online_players_list_menu_requested(QPoint p)
{
    if (ui->online_players_list->itemAt(p) != nullptr)
    {
        bool is_op = Operators::getInstance()->is_operator(ui->online_players_list->selectedItems().at(0)->text());

        QMenu context_menu ("Some menu", ui->online_players_list);

        QAction* kick = context_menu.addAction("Kick");
        connect (kick, SIGNAL(triggered(bool)), this, SLOT(on_online_player_menu_kick()));


        if (is_op)
        {
            QAction* deop = context_menu.addAction("Deop");
            connect(deop, SIGNAL(triggered(bool)), this, SLOT (on_online_player_menu_deop()));

        }
        else
        {
            QAction* op = context_menu.addAction("Make operator");
            connect(op, SIGNAL(triggered(bool)), this, SLOT (on_online_player_menu_op()));
        }

        context_menu.exec(ui->online_players_list->mapToGlobal(p));
    }
}

void MainWindow::on_online_player_menu_kick()
{
    QString player_name = ui->online_players_list->selectedItems().at(0)->text();
    _serv_thread.send_command(QString("/kick ").append(player_name));
}

void MainWindow::on_online_player_menu_op()
{
    QString player_name = ui->online_players_list->selectedItems().at(0)->text();
    _serv_thread.send_command(QString("/op ").append(player_name));
}

void MainWindow::on_online_player_menu_deop()
{
    QString player_name = ui->online_players_list->selectedItems().at(0)->text();
    _serv_thread.send_command(QString("/deop ").append(player_name));
}

void MainWindow::on_ban_button_clicked()
{
    QList<QListWidgetItem*> selected_players = ui->online_players_list->selectedItems();
    if (selected_players.length() > 0) _serv_thread.send_command(QString("/ban ").append(selected_players.at(0)->text()));
}

void MainWindow::on_unban_button_clicked()
{
    QList<QListWidgetItem*> selected_players = ui->banned_players_list->selectedItems();
    if (selected_players.size() > 0) _serv_thread.send_command(QString("/pardon ")+selected_players.at(0)->text());
}





//worlds tab
void MainWindow::on_worlds_list_menu_requested (QPoint p)
{
    if (ui->worlds_list->itemAt(p) != nullptr && !_serv_thread.is_running())
    {
        QMenu context_menu ("Some menu", ui->worlds_list);

        QAction* select = context_menu.addAction ("Select");
        connect (select, SIGNAL(triggered(bool)), this, SLOT(on_worlds_list_menu_select()));

        context_menu.exec(ui->worlds_list->mapToGlobal(p));
    }
}

void MainWindow::on_worlds_list_menu_select()
{
    QString prev_world_name = ServerProperties::get_instance()->get_level_name();

    //change icon of deselected world
    QListWidgetItem* prev_world = find_item(ui->worlds_list, prev_world_name);
    if (prev_world != nullptr) prev_world->setIcon (QPixmap(QString(":/images/world_32.png")));

    QListWidgetItem* sel_world = ui->worlds_list->selectedItems().at(0);

    //change icon of selected world
    sel_world->setIcon (QPixmap(QString(":/images/world_32_tick.png")));

    ServerProperties::get_instance()->set_level_name(sel_world->text());
    ServerProperties::get_instance()->save_to_disk();
}

void MainWindow::on_worlds_update_button_clicked()
{
    Settings::get_instance()->load_available_worlds();
    gui_load_worlds();
}





//mods tab
void MainWindow::on_mods_list_itemClicked(QListWidgetItem *item)
{
    QString mod_filename = item->text();
    Mod curr_mod = ServerMods::get_instance()->get_mod_at(mod_filename);

    ui->mod_id_textfield->setText(curr_mod.get_id());
    ui->mod_name_textfield->setText(curr_mod.get_name());
    ui->mod_version_textfield->setText(curr_mod.get_version());
    ui->mod_desc_textfield->setText(curr_mod.get_desc());
    ui->mod_cred_textfield->setText(curr_mod.get_cred());
}

void MainWindow::on_update_mods_button_clicked()
{
    ServerMods::get_instance()->load_mods();
    gui_load_mods();
}





//server properties tab
void MainWindow::on_properties_update_button_clicked()
{
    ServerProperties::get_instance()->load_server_properties();
    gui_load_server_properties();
    gui_load_worlds();
}

void MainWindow::on_properties_save_button_clicked()
{
    gui_save_server_properties();
    ServerProperties::get_instance()->save_to_disk();
}





//settings tab
void MainWindow::on_working_dir_choose_button_clicked()
{
    QString new_dir = QFileDialog::getExistingDirectory(this, QString("Select working directory..."),
                                                        Settings::get_instance()->get_working_dir());
    if (new_dir.length() > 0)
    {
        Settings::get_instance()->set_working_dir(new_dir);
        ui->working_dir_field->setText(Settings::get_instance()->get_working_dir());
        gui_update_jars();
        gui_load_banned_players();
        gui_load_server_properties();
        gui_load_worlds();
        gui_load_mods();
    }
}

void MainWindow::on_jar_combo_currentIndexChanged(int index)
{
    Settings::get_instance()->set_jar(ui->jar_combo->currentText());
}

void MainWindow::on_ram_slider_sliderMoved(int value)
{
    ui->ram_value_label->setText(QString::number(value).append("MB"));
    Settings::get_instance()->set_ram(value);
}

void MainWindow::on_ram_slider_valueChanged(int value)
{
    ui->ram_value_label->setText(QString::number(value).append("MB"));
    Settings::get_instance()->set_ram(value);
}

void MainWindow::on_play_sound_checkbox_stateChanged(int arg1)
{
    Settings::get_instance()->set_play_sound(ui->play_sound_checkbox->isChecked());
}

































