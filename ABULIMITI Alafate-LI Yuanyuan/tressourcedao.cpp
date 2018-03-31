#include "tressourcedao.h"

TRessourceDAO::TRessourceDAO()
{

}
vector<TRessource> TRessourceDAO::getRessourceVecteur() const
{
    return ressourceVecteur;
}

void TRessourceDAO::setRessourceVecteur(const vector<TRessource> &value)
{
    ressourceVecteur = value;
}

QSqlQuery TRessourceDAO::rechercherAll()
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from TRessource left join TType on TRessource.IdType=TType.Id"));
    return query;
}

QSqlQuery TRessourceDAO::rechercherTypeLabel(QString label)
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from TRessource left join TType on TRessource.IdType=TType.Id where TType.Label='%1'").arg(label));
    return query;
}

QSqlQuery TRessourceDAO::rechercherAllType()
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select distinct TType.Label from TRessource left join TType on TRessource.IdType=TType.Id"));
    return query;
}

QSqlQuery TRessourceDAO::rechercherNomEtLabel(QString nom,QString label)
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from TRessource left join TType on TRessource.IdType=TType.Id where TRessource.Nom='%1' and TType.Label='%2'").arg(nom,label));
    return query;
}

QSqlQuery TRessourceDAO::rechercherIdR(QString idR)
{
     QSqlQuery query(GererBD::getBD());
     query.exec(QString("select * from TRessource left join TType on TRessource.IdType=TType.Id where TRessource.Id='%1'").arg(idR));
     return query;
}

QSqlQuery TRessourceDAO::rechercherParTous(QString nom,QString prenom,QString idType)
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from TRessource where TRessource.Nom='%1' and TRessource.Prenom='%2' and TRessource.IdType='%3'").arg(nom,prenom,idType));
    return query;
}

QStringList TRessourceDAO::inverseToString(QSqlQuery query)
{
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }
    return list;
}


bool TRessourceDAO::ajouterRessource(QString nom,QString prenom,QString idType)
{
    bool resultat;
    QString strNom;
    strNom.append( nom.at(0).toUpper());
    for(int i=1;i<nom.size();i++)
    {
        strNom.append(nom.at(i).toLower());
    }
    QString strPrenom;
    strPrenom.append(prenom.at(0).toUpper());
    for(int i=1;i<prenom.size();i++)
    {
         strPrenom.append(prenom.at(i).toLower());
    }
    if(rechercherParTous(nom,prenom,idType).next())
    {
        resultat=false;
    }
    else
    {
        QSqlQuery query(GererBD::getBD());
        query.prepare("insert into TRessource(Nom,Prenom,IdType) values(:nom,:prenom,:idType)");
        query.bindValue(":nom",strNom);
        query.bindValue(":prenom",strPrenom);
        query.bindValue(":idType",idType);
        resultat=query.exec();
    }
    return resultat;
}

 bool TRessourceDAO::supprimer(QString idR)
 {
     QSqlQuery query(GererBD::getBD());
     bool resultat=query.exec(QString("delete from TRessource where TRessource.Id= '%1'").arg(idR));
     return resultat;

 }

 bool TRessourceDAO::modifier(QString idR,QString nom,QString prenom,QString idType)
 {
     bool resultat;
     QString strNom;
     strNom.append( nom.at(0).toUpper());
     for(int i=1;i<nom.size();i++)
     {
         strNom.append(nom.at(i).toLower());
     }
     QString strPrenom;
     strPrenom.append(prenom.at(0).toUpper());
     for(int i=1;i<prenom.size();i++)
     {
          strPrenom.append(prenom.at(i).toLower());
     }
     QSqlQuery query(GererBD::getBD());
     resultat=query.exec(QString("update TRessource set Nom='%1',Prenom='%2',IdType='%3' where TRessource.id='%4'").arg(strNom,strPrenom,idType,idR));
     return resultat;
 }

 void TRessourceDAO::lireRe()
 {
     QSqlQuery sqlQuery(GererBD::getBD());

     QString sql = "select * from TRessource";
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
             QString nom = sqlQuery.value(1).toString();
             QString prenom = sqlQuery.value(2).toString();
             int idType = sqlQuery.value(3).toInt();

             TRessource ressource;
             ressource.setId(id);
             ressource.setNom(nom);
             ressource.setPrenom(prenom);
             ressource.setIdType(idType);
             ressourceVecteur.push_back(ressource);
         }
     }
 }
