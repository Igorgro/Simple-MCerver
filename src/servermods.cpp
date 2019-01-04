#include <QDir>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "quazip.h"
#include "quazipfile.h"
#include "servermods.h"
#include "settings.h"

bool ServerMods::_is_created = false;

ServerMods* ServerMods::get_instance()
{
    static ServerMods* _instance = new ServerMods();
    _is_created = true;
    return _instance;
}

bool ServerMods::is_created() {return  _is_created;}

ServerMods::ServerMods()
{
    load_mods();
}

void ServerMods::load_mods()
{
    _mods.clear();

    QDir mods_dir (Settings::get_instance()->get_working_dir().append("/mods"));

    QStringList filter;
    filter<<"*.jar";

    mods_dir.setNameFilters(filter);
    QStringList mods_jars = mods_dir.entryList();

    for (int i = 0; i < mods_jars.size(); i++)
    {
        load_mod(mods_jars.at(i));
    }
}

void ServerMods::load_mod (QString mod_filename)
{
    QuaZip mod_jar(Settings::get_instance()->get_working_dir().append("/mods/").append(mod_filename));
    mod_jar.open(QuaZip::mdUnzip);
    mod_jar.setCurrentFile(QString("mcmod.info"));

    QuaZipFile mcmod_file (&mod_jar);
    mcmod_file.open(QIODevice::ReadOnly);
    QByteArray mcmod = mcmod_file.readAll();


    QJsonDocument doc = QJsonDocument::fromJson(mcmod);
    QJsonArray mcmod_arr = doc.array();
    QJsonObject mcmod_obj = mcmod_arr.at(0).toObject();

    QString mod_id = mcmod_obj.value("modid").toString();
    QString mod_name = mcmod_obj.value("name").toString();
    QString mod_version = mcmod_obj.value("version").toString();
    QString mod_desc = mcmod_obj.value("description").toString();
    QString mod_cred = mcmod_obj.value("credits").toString();

    _mods.insert(mod_filename, Mod(mod_id, mod_name, mod_version, mod_desc, mod_cred));

    mcmod_file.close();
    mod_jar.close();
}

QList<QString> ServerMods::get_mods_filenames() {return _mods.keys();}
Mod ServerMods::get_mod_at(QString mod_filename) {return _mods.value(mod_filename);}







































