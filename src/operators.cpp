#include "operators.h"
#include "settings.h"
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

bool Operators::_is_created = false;

Operators::Operators()
{
    load_operators();
}

Operators* Operators::getInstance()
{
    static Operators* _instance = new Operators();
    _is_created = true;
    return _instance;
}

void Operators::load_operators()
{
    _ops_arr = QVector<QString>();

    QFile in (Settings::get_instance()->get_working_dir().append("/ops.json"));
    if (in.exists())
    {
        in.open(QIODevice::ReadOnly);
        QJsonDocument doc = QJsonDocument::fromJson(in.readAll());
        in.close();

        QJsonArray j_ops_arr = doc.array();
        for (int i = 0; i < j_ops_arr.size(); i++)
        {
            _ops_arr.append(j_ops_arr.at(i).toObject().value("name").toString());
        }
    }
}

void Operators::add_operator (QString player_name)
{
    _ops_arr.append(player_name);
}

void Operators::remove_operator (QString player_name)
{
    _ops_arr.removeOne(player_name);
}

bool Operators::is_operator(QString player_name)
{
    return _ops_arr.contains(player_name);
}

bool Operators::is_created()
{
    return _is_created;
}

































