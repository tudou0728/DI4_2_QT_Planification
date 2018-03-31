#ifndef TCLIENTDAO_H
#define TCLIENTDAO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QSqlTableModel>
#include "tclient.h"
#include "trdv.h"
#include "trdvdao.h"
#include <QFile>

class TClientDAO
{
private:
    QSqlTableModel qsqlTableModel;
    vector<TClient> clientVector;

public:
    TClientDAO();

    void lireC();
    void ajouterC(TClient client);
    void supprimerC(QString idClient);
    QSqlQuery rechercher(QString nomClient,QString prenomClient,QString idClient);
    QSqlQuery rechercherDate(QString nomClient,QString prenomClient,QString idClient,QString daterdvDebut,QString daterdvFin);
    void modifierC(int id, QString nom, QString prenom, QString ville, int cP, QString date, int tel, int prio, QString adresse, QString commentaire,int duree);
    bool verifierC(TClient client);

    vector<TClient> getClientVector() const;
    void setClientVector(const vector<TClient> &value);
    QSqlQuery rechercherClient(QString idClient);
    QString enregestrerXML(vector<TClient> clients);

};

#endif // TCLIENTDAO_H
