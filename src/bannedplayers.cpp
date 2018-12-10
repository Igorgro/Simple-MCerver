#include "bannedplayers.h"
#include "settings.h"
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

bool BannedPlayers::_is_created = false;

BannedPlayers::BannedPlayers()
{
    load_banned_players();
}

BannedPlayers* BannedPlayers::getInstance()
{
    static BannedPlayers* _instance = new BannedPlayers();
    _is_created = true;
    return _instance;
}
void BannedPlayers::load_banned_players()
{
    _ban_arr = QVector<QString>();

    QFile in (Settings::getInstance()->get_working_dir().append("/banned-players.json"));
    if (in.exists())
    {
        in.open(QIODevice::ReadOnly);
        QJsonDocument doc = QJsonDocument::fromJson(in.readAll());
        QJsonArray j_ban_arr = doc.array();
        for (int i = 0; i < j_ban_arr.size(); i++)
        {
            _ban_arr.append(j_ban_arr.at(i).toObject().value("name").toString());
        }

        in.close();
    }

}


int BannedPlayers::size()
{
    return _ban_arr.size();
}
const QString& BannedPlayers::at(int i)
{
    return _ban_arr.at(i);
}

bool BannedPlayers::is_created()
{
    return _is_created;
}




































