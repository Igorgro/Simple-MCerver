#ifndef SETTINGS_H
#define SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QStringList>

class Settings
{
public:

    enum LogLevel {info, warn, error};

    static Settings* getInstance();

    static LogLevel string_to_log_level (QString str);
    static QString log_level_to_string (LogLevel log_level);


    void save_to_disk();
    QString get_working_dir();
    QString get_jar();
    int get_ram();
    bool get_play_sound();
    LogLevel get_log_level();

    void load_available_worlds();

    const QStringList* get_available_jars();
    const QStringList* get_available_worlds();


    void set_working_dir(QString working_dir);
    void set_jar (QString jar);
    void set_ram (int ram);
    void set_play_sound (bool play_soud);
    void set_log_level (LogLevel log_level);


private:
    Settings();
    void apply_default_values();
    void load_available_jars();


    QString _working_dir;
    QString _jar;
    int _ram;
    bool _play_sound;
    LogLevel _log_level;

    QStringList _available_jars;
    QStringList _available_worlds;
};

#endif // SETTINGS_H
