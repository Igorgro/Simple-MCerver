#ifndef MOD_H
#define MOD_H

#include <QString>



class Mod
{
public:
    Mod(QString id, QString name, QString version,
        QString desc, QString cred);
    Mod();

    QString get_id();
    QString get_name();
    QString get_version();
    QString get_desc();
    QString get_cred();

private:
    QString _id;
    QString _name;
    QString _version;
    QString _desc;
    QString _cred;

};

#endif // MOD_H
