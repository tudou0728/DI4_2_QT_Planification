#include "tcomptedao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include "gererbd.h"

bool TcompteDAO::verifierLogin(QString username, QString password)
{
    bool resultat=false;
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from tcompte where Login='%1'and Mdp='%2'").arg(username).arg(password));
    if(query.next())
    {
        resultat=true;
    }
    return resultat;
}
