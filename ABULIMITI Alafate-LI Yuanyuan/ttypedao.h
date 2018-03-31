#ifndef TTYPEDAO_H
#define TTYPEDAO_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include "gererbd.h"
class TTypeDAO
{
public:
    TTypeDAO();
    QSqlQuery rechercherAlltype();
    QSqlQuery rechercherLabel(QString label);
    QStringList inverseToString(QSqlQuery query);

};

#endif // TTYPEDAO_H
