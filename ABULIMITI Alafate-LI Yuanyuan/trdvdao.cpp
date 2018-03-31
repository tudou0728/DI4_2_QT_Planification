#include "trdvdao.h"

TRdvDAO::TRdvDAO()
{

}

QSqlQuery TRdvDAO::rechercherParDate(QString date)
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from TRdv left join TClient on TRdv.IdClient=TClient.Id where TClient.DateRdv='%1' order by TRdv.IdClient").arg(date));
    return query;
}

QSqlQuery TRdvDAO::rechercherRessource(QString date)
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select distinct(TRdv.IdRessource) from TRdv left join TClient on TRdv.IdClient=TClient.Id where TClient.DateRdv='%1'").arg(date));
    return query;
}

vector<TRdv> TRdvDAO::getRdvVecteur() const
{
    return rdvVecteur;
}

void TRdvDAO::setRdvVecteur(const vector<TRdv> &value)
{
    rdvVecteur = value;
}


void TRdvDAO::lireR()
{
    QSqlQuery sqlQuery(GererBD::getBD());

    QString sql = "select * from TRdv";
    sqlQuery.prepare(sql);
    if(!sqlQuery.exec())
    {
        qDebug()<<"erreur";
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            int idClient = sqlQuery.value(1).toInt();
            int idRessource = sqlQuery.value(2).toInt();

            TRdv trdv;
            trdv.setId(id);
            trdv.setIdClient(idClient);
            trdv.setIdRessource(idRessource);
            //qDebug() <<trdv.getId();
            rdvVecteur.push_back(trdv);
        }
    }
}

void TRdvDAO::ajouterR(vector<int> idRessourceVecteur, int IdCLient)
{
    QVariantList IdList;
    QVariantList ClientList;
    QVariantList RessourceList;
    vector<int>::iterator itInt;

    TRdvDAO rdvDAO;
    rdvDAO.lireR();
    vector<TRdv> rdvVecteurTemp = rdvDAO.getRdvVecteur();
    vector<TRdv>::iterator itTemp2;

    itTemp2= rdvVecteurTemp.end()-1;
    int idOrdreRdv = itTemp2->getId();

    for(itInt=idRessourceVecteur.begin();itInt!=idRessourceVecteur.end();++itInt)
    {
        IdList.push_back(++idOrdreRdv);
        ClientList.push_back(IdCLient);
        RessourceList.push_back(*itInt);
    }

    QSqlQuery query(GererBD::getBD());
    query.prepare("insert into TRdv(Id,IdCLient,IdRessource) values(?,?,?)");
    query.addBindValue(IdList);
    query.addBindValue(ClientList);
    query.addBindValue(RessourceList);
}
