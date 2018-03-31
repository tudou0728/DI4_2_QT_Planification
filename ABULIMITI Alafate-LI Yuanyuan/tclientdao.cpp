#include "tclientdao.h"
#include "gererbd.h"
#include<QXmlStreamWriter>
TClientDAO::TClientDAO()
{

}
vector<TClient> TClientDAO::getClientVector() const
{
    return clientVector;
}

void TClientDAO::setClientVector(const vector<TClient> &value)
{
    clientVector = value;
}

QSqlQuery TClientDAO::rechercherClient(QString idClient)
{
    QSqlQuery query(GererBD::getBD());
    query.exec(QString("select * from TClient where TClient.Id='%1'").arg(idClient));
    return query;
}


QSqlQuery TClientDAO::rechercher(QString nomClient,QString prenomClient,QString idClient)
{
    QSqlQuery query(GererBD::getBD());
    query.prepare("SELECT * FROM tclient WHERE Nom LIKE :nomClient "
                  "and Prenom LIKE :prenomClient and id LIKE :idClient order by TClient.DateRdv");
    query.bindValue(":nomClient",nomClient+"%");
    query.bindValue(":prenomClient",prenomClient+"%");
    query.bindValue(":idClient",idClient+"%");
    query.exec();
    return query;
}

QSqlQuery TClientDAO::rechercherDate(QString nomClient,QString prenomClient,QString idClient,QString daterdvDebut,QString daterdvFin)
{
    QSqlQuery query(GererBD::getBD());
    query.prepare("select* from TClient where TClient.Nom like :nomClient and TClient.Prenom like :prenomClient and TClient.Id like :idClient and TClient.DateRdv between :daterdvDebut and :daterdvFin order by TClient.DateRdv");
    query.bindValue(":nomClient",nomClient+"%");
    query.bindValue(":prenomClient",prenomClient+"%");
    query.bindValue(":idClient",idClient+"%");
    query.bindValue(":daterdvDebut",daterdvDebut);
    query.bindValue(":daterdvFin",daterdvFin);
    query.exec();
    qDebug()<<daterdvDebut+daterdvFin;
    return query;
}


void TClientDAO::lireC()
{
    QSqlQuery sqlQuery(GererBD::getBD());
    QString sql = "select * from TClient";
    sqlQuery.prepare(sql);
    sqlQuery.exec();
    while(sqlQuery.next())
    {
        int id = sqlQuery.value(0).toInt();
        QString nom = sqlQuery.value(1).toString();
        QString prenom = sqlQuery.value(2).toString();
        QString adresse = sqlQuery.value(3).toString();
        QString ville = sqlQuery.value(4).toString();
        int cp = sqlQuery.value(5).toInt();
        QString commentaire = sqlQuery.value(6).toString();
        int tel = sqlQuery.value(7).toInt();
        QString dateRdv = sqlQuery.value(8).toString();
        int dureeRdv = sqlQuery.value(9).toInt();
        int prio = sqlQuery.value(10).toInt();

        TClient client;
        client.setAdresse(adresse);
        client.setCommentaire(commentaire);
        client.setCP(cp);
        client.setDateRdv(dateRdv);
        client.setDureeRdv(dureeRdv);
        client.setId(id);
        client.setNom(nom);
        client.setPrenom(prenom);
        client.setPriorite(prio);
        client.setTel(tel);
        client.setVille(ville);
        clientVector.push_back(client);

    }

    TRdvDAO tRdvDAO;
    tRdvDAO.lireR();

    vector<TRdv> rdvVector=tRdvDAO.getRdvVecteur();

    if(rdvVector.size()>0)
    {
        vector<TRdv>::iterator it_R;
        vector<TClient>::iterator it_C;

        for(it_C=clientVector.begin();it_C!=clientVector.end();++it_C)
        {
            vector<int> idRessourceVecteurTemp;
            for(it_R=rdvVector.begin();it_R!=rdvVector.end();++it_R)
            {
                if(it_C->getId()==it_R->getIdClient())
                {
                    idRessourceVecteurTemp.push_back(it_R->getIdRessource());
                }
            }
            it_C->setIdRessourcesVecteur(idRessourceVecteurTemp);
        }
    }
}

void TClientDAO::ajouterC(TClient client)
{
    TClientDAO cDAO;
    cDAO.lireC();
    vector<TClient> cVecteur = cDAO.getClientVector();
    vector<TClient>::iterator icTemp;
    icTemp = cVecteur.end()-1;
    int idOrdre = icTemp->getId();
    QSqlQuery query(GererBD::getBD());
    query.prepare("insert into TClient(Id,Nom,Prenom,Adresse,Ville,CP,Commentaire,Tel,DateRdv,DureeRdv,Priorite) values(?,?,?,?,?,?,?,?,?,?,?)");
    client.setId(idOrdre+1);
    query.addBindValue(client.getId());
    query.addBindValue(client.getNom());
    query.addBindValue(client.getPrenom());
    query.addBindValue(client.getAdresse());
    query.addBindValue(client.getVille());
    query.addBindValue(client.getCP());
    query.addBindValue(client.getCommentaire());
    query.addBindValue(client.getTel());
    query.addBindValue(client.getDateRdv());
    query.addBindValue(client.getDureeRdv());
    query.addBindValue(client.getPriorite());
    query.exec();

    vector<int> idRessourceVecteur=client.getIdRessourcesVecteur();

    TRdvDAO tRdvDAO;
    tRdvDAO.ajouterR(idRessourceVecteur,client.getId());

}

void TClientDAO::supprimerC(QString idClient)
{   QSqlQuery query(GererBD::getBD());

    QString sql="delete from TClient where id="+idClient;
    query.prepare(sql);
    query.exec();
    sql="delete from TRdv where IdClient="+idClient;
    query.prepare(sql);
    query.exec();
}


void TClientDAO::modifierC(int id, QString nom, QString prenom, QString ville, int cP, QString date, int tel, int prio, QString adresse, QString commentaire,int duree)
{
    QSqlQuery sqlQuery(GererBD::getBD());
    QString sql = "update TClient set Nom=:nom, Prenom=:prenom, Ville=:ville ,CP=:cP,DateRdv=:date, Tel=:tel, Priorite=:prio, Adresse=:adresse, Commentaire=:commentaire, DureeRdv=:duree where TClient.Id=:id;";
    sqlQuery.prepare(sql);

    sqlQuery.bindValue(":id",id);
    sqlQuery.bindValue(":nom",nom);
    sqlQuery.bindValue(":prenom",prenom);
    sqlQuery.bindValue(":ville",ville);
    sqlQuery.bindValue(":cP",cP);
    sqlQuery.bindValue(":date",date);
    sqlQuery.bindValue(":tel",tel);
    sqlQuery.bindValue(":prio",prio);
    sqlQuery.bindValue(":adresse",adresse);
    sqlQuery.bindValue(":commentaire",commentaire);
    sqlQuery.bindValue(":duree",duree);

    sqlQuery.exec();
}

bool TClientDAO::verifierC(TClient client)
{
    QString adresse = client.getAdresse();
    qDebug()<<adresse;
    QString nom = client.getNom();
    qDebug()<<nom;
    QString prenom = client.getPrenom();
    qDebug()<<prenom;
    QString ville = client.getVille();
    qDebug()<<ville;
    QString commentaire = client.getCommentaire();
    qDebug()<<commentaire;
    QString date = client.getDateRdv();
    qDebug()<<date;
    int cp = client.getCP();
    qDebug()<<cp;
    int tel = client.getTel();
    qDebug()<<tel;
    int duree = client.getDureeRdv();
    qDebug()<<duree;
    int prio = client.getPriorite();
    qDebug()<<prio;
    int id = client.getId();
    qDebug()<<id;

    QSqlQuery sqlQuery(GererBD::getBD());
    QString sql = "select* from TClient where Nom=:nom and Prenom=:prenom and Ville=:ville and CP=:cp and DateRdv=:date and Tel=:tel and Priorite=:prio and Adresse=:adresse and Commentaire=:commentaire and DureeRdv=:duree and Id=:id;";
    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":id",id);
    sqlQuery.bindValue(":nom",nom);
    sqlQuery.bindValue(":prenom",prenom);
    sqlQuery.bindValue(":ville",ville);
    sqlQuery.bindValue(":cP",cp);
    sqlQuery.bindValue(":date",date);
    sqlQuery.bindValue(":tel",tel);
    sqlQuery.bindValue(":prio",prio);
    sqlQuery.bindValue(":adresse",adresse);
    sqlQuery.bindValue(":commentaire",commentaire);
    sqlQuery.bindValue(":duree",duree);
    sqlQuery.exec();
    bool b =false;
    if(sqlQuery.next())
    {
        b=true;
    }
    return b;
}

QString TClientDAO::enregestrerXML(vector<TClient> clients)
{
    QString fileNom;
    QFile file(fileNom);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("TClient");
    vector<TClient>::iterator it;
    for(it=clients.begin();it!=clients.end();it++)
    {
        xmlWriter.writeStartElement("Client Id="+it->getId());
        xmlWriter.writeTextElement("Nom",it->getNom());
        xmlWriter.writeTextElement("Prenom",it->getPrenom());
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    return fileNom;
}
