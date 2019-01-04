#ifndef SERVERMODS_H
#define SERVERMODS_H

#include<QMap>

#include "mod.h"


class ServerMods
{
public:
    static ServerMods* get_instance();
    static bool is_created();

    void load_mods();
    QList<QString> get_mods_filenames();
    Mod get_mod_at(QString mod_filename);

private:
    QMap <QString, Mod> _mods;
    static bool _is_created;

    void load_mod (QString mod_filename);

    ServerMods();
};

#endif // SERVERMODS_H
