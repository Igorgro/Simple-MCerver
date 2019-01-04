#include "mod.h"

Mod::Mod(QString id, QString name, QString version,
    QString desc, QString cred):
    _id (id),
    _name (name),
    _version (version),
    _desc (desc),
    _cred (cred)
{
}

Mod::Mod():
    _id(""),
    _name(""),
    _version(""),
    _desc(""),
    _cred("")
{}

QString Mod::get_id() {return _id;}
QString Mod::get_name() {return _name;}
QString Mod::get_version() {return _version;}
QString Mod::get_desc() {return _desc;}
QString Mod::get_cred() {return _cred;}
