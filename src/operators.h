#ifndef OPERATORS_H
#define OPERATORS_H
#include <QVector>
#include <QString>

class Operators
{
public:
    static Operators* getInstance();
    void load_operators();
    void add_operator (QString player_name);
    void remove_operator (QString player_name);
    bool is_operator(QString player_name);

    static bool is_created();

private:
    static bool _is_created;
    QVector<QString> _ops_arr;

    Operators();
};

#endif // OPERATORS_H
