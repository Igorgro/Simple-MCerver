#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSound>
#include <string>
#include <windows.h>
#include <winbase.h>

#include "server_thread.h"
#include "message_processing_thread.h"

namespace Ui {
class MainWindow;
}

extern "C"
WINBASEAPI BOOL WINAPI GetPhysicallyInstalledSystemMemory (PULONGLONG );

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

    MessageProcessingThread processing_thread;

    ServerThread _serv_thread;

    QPixmap stopped_icon;
    QPixmap starting_icon;
    QPixmap running_icon;
    QSound join_sound;

    const QString redFont = QString ("<font color=\"#F03E3E\">");
    const QString yellowFont = QString ("<font color=\"#FFD700\">");
    const QString greenFont = QString ("<font color=\"#35CC35\">");
    const QString blueFont = QString ("<font color=\"#35A6CC\">");

    const QString endFont = QString ("</font>");

    void connect_slots();
    void init_gui();
    void gui_load_settings();
    void gui_load_banned_players();
    void gui_update_jars();
    void gui_load_worlds();
    void gui_load_server_properties();
    void gui_save_server_properties();

    QListWidgetItem* find_item (QListWidget* list_widget, QString& name);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_stop_button_clicked();
    void on_start_button_clicked();


    void on_kill_button_clicked();
    void on_send_button_clicked();
    void on_command_edit_returnPressed();



    void on_log_level_box_currentTextChanged(const QString &arg1);
    void on_export_log_button_clicked();
    void on_working_dir_choose_button_clicked();

    void on_ban_button_clicked();

    void on_unban_button_clicked();

    void on_ram_slider_sliderMoved(int value);
    void on_ram_slider_valueChanged(int value);

    void on_jar_combo_currentIndexChanged(int index);

    void on_properties_save_button_clicked();

    void on_worlds_update_button_clicked();

    void on_properties_update_button_clicked();

    void on_play_sound_checkbox_stateChanged(int arg1);

public slots:
    void on_online_players_list_menu_requested (QPoint point);
    void on_online_player_menu_kick();
    void on_online_player_menu_op();
    void on_online_player_menu_deop();

    void on_worlds_list_menu_requested (QPoint p);
    void on_worlds_list_menu_select();

    void gui_log_print_info (QString str);
    void gui_log_print_warn (QString str);
    void gui_log_print_error (QString str);
    void gui_server_stoped();
    void gui_server_starting();
    void gui_server_running();
    void gui_make_player_online (QString player_name);
    void gui_make_player_offline (QString player_name);
    void gui_make_player_opped (QString player_name);
    void gui_make_player_deopped (QString player_name);
    void gui_make_player_banned(QString player_name);
    void gui_make_player_unbanned(QString player_name);
};

#endif // MAINWINDOW_H

\











