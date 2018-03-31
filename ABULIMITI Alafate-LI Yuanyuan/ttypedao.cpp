#include "ttypedao.h"

TTypeDAO::TTypeDAO()
{

}

QSqlQuery TTypeDAO::rechercherAlltype()
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select distinct TType.Label from TType"));
    return query;
}

QStringList TTypeDAO::inverseToString(QSqlQuery query)
{
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }
    return list;
}

QSqlQuery TTypeDAO::rechercherLabel(QString label)
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from TType where TType.Label='%1'").arg(label));
    return query;
}
