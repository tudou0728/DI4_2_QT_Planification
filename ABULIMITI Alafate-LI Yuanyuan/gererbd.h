#ifndef GERERBD_H
#define GERERBD_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include"c_init_bd.h"

class GererBD
{
private:
    static QSqlDatabase baseDeDonnes;
public:
    static QSqlDatabase getBD();
    static bool connecter();
    static bool fermer();

};
#endif // GERERBD_H
