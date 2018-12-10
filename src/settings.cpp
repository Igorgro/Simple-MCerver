#include "settings.h"
#include "bannedplayers.h"
#include "operators.h"
#include "serverproperties.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QCoreApplication>
#include <QIODevice>
#include <QDir>
#include <QDebug>
#include <iostream>


Settings::Settings()
{
    QFile in (QCoreApplication::applicationDirPath().append(QString("/settings.json")));

    if (in.exists())
    {
        in.open(QIODevice::ReadOnly);
        QByteArray arr = in.readAll();
        in.close();

        QJsonDocument doc = QJsonDocument::fromJson(arr);
        QJsonObject obj = doc.object();

        set_working_dir(_working_dir = obj.value(QString("working_dir")).toString(QCoreApplication::applicationDirPath()));
        set_jar(obj.value(QString("jar")).toString(QString("")));
        set_ram(obj.value("ram").toInt(1024));
        set_play_sound(obj.value(QString("play_sound")).toBool(false));
        QString log_level_str = obj.value (QString ("log_level")).toString (QString("info"));
        set_log_level (string_to_log_level(log_level_str));
    }

    else apply_default_values();

}

void Settings::apply_default_values()
{
    set_working_dir(QCoreApplication::applicationDirPath());
    set_jar(QString(""));
    set_ram(1024);
    set_play_sound(false);
    set_log_level(LogLevel::info);

}

void Settings::load_available_jars()
{
    QDir work_dir (get_working_dir());

    QStringList filters;
    filters<<"*.jar";

    work_dir.setNameFilters(filters);
    _available_jars = work_dir.entryList();
}

void Settings::load_available_worlds()
{
    QDir work_dir (get_working_dir());
    work_dir.setFilter(QDir::Dirs);

    QStringList dirs = work_dir.entryList();
    _available_worlds = QStringList();
    for (int i = 0; i < dirs.size(); i++)
    {
        QFile test_file (get_working_dir().append("/").append(dirs.at(i)).append("/level.dat"));
        if (test_file.exists())
        {
            _available_worlds.append(dirs.at(i));
        }
    }
}

void Settings::save_to_disk()
{
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("working_dir", QJsonValue(get_working_dir()));
    obj.insert("jar", QJsonValue(get_jar()));
    obj.insert("ram", QJsonValue(get_ram()));
    obj.insert("log_level", QJsonValue(log_level_to_string(get_log_level())));
    obj.insert("play_sound", QJsonValue(get_play_sound()));
    doc.setObject(obj);

    QFile out (QCoreApplication::applicationDirPath().append(QString("/settings.json")));
    out.open(QIODevice::WriteOnly);
    out.write(doc.toJson());
    out.close();
}

Settings* Settings::getInstance()
{
    static Settings* _instance = new Settings();
    return _instance;
}


Settings::LogLevel Settings::string_to_log_level (QString str)
{
    if (!str.compare(QString ("info")) || !str.compare(QString ("Info"))) return LogLevel::info;
    if (!str.compare(QString ("warn")) || !str.compare(QString ("Warning"))) return LogLevel::warn;
    if (!str.compare(QString ("error")) || !str.compare(QString ("Error"))) return LogLevel::error;
    return LogLevel::info;
}
QString Settings::log_level_to_string(LogLevel log_level)
{
    switch (log_level)
    {
        case LogLevel::info:
            return QString("info");
            break;
        case LogLevel::warn:
            return QString("warn");
            break;
        case LogLevel::error:
            return QString("error");
            break;
    }
    return QString ("info");
}


QString Settings::get_working_dir() {return _working_dir;}
QString Settings::get_jar() {return _jar;}
int Settings::get_ram() {return _ram;}
bool Settings::get_play_sound() {return _play_sound;}
Settings::LogLevel Settings::get_log_level() {return _log_level;}

const QStringList* Settings::get_available_jars() {return &_available_jars;}
const QStringList* Settings::get_available_worlds() {return &_available_worlds;}


void Settings::set_working_dir(QString working_dir)
{
    _working_dir = working_dir;
    load_available_jars();
    load_available_worlds();
    if (Operators::is_created()) Operators::getInstance()->load_operators();
    if (BannedPlayers::is_created()) BannedPlayers::getInstance()->load_banned_players();
    if (ServerProperties::is_created()) ServerProperties::getInstance()->load_server_properties();
}
void Settings::set_jar(QString jar) {_jar = jar;}
void Settings::set_ram(int ram) {_ram = ram;}
void Settings::set_play_sound(bool play_sound) {_play_sound = play_sound;}
void Settings::set_log_level(LogLevel log_level) {_log_level = log_level;}






























