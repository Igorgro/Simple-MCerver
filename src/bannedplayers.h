#ifndef BANNEDPLAYERS_H
#define BANNEDPLAYERS_H
#include <QVector>
#include <QString>

class BannedPlayers
{
public:
    static BannedPlayers* getInstance();
    void load_banned_players();
    int size();
    const QString& at(int i);
    static bool is_created();

private:
    QVector<QString> _ban_arr;
    static bool _is_created;

    BannedPlayers();
};

#endif // BANNEDPLAYERS_H
