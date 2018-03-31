#ifndef TRESSOURCEDAO_H
#define TRESSOURCEDAO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include "gererbd.h"
#include <QStandardItemModel>
#include<vector>
#include"tressource.h"

class TRessourceDAO
{
public:
    TRessourceDAO();
    QSqlQuery rechercherTypeLabel(QString label);
    QSqlQuery rechercherAll();
    QSqlQuery rechercherAllType();
    QSqlQuery rechercherIdR(QString idR);
    QSqlQuery rechercherNomEtLabel(QString nom,QString label);
    bool supprimer(QString idR);
    bool modifier(QString idR,QString nom,QString prenom,QString idType);
    QStringList inverseToString(QSqlQuery query);
    bool ajouterRessource(QString nom,QString prenom,QString idType);
    QSqlQuery rechercherParTous(QString nom,QString prenom,QString idType);

    void lireRe();
    vector<TRessource> getRessourceVecteur() const;
    void setRessourceVecteur(const vector<TRessource> &value);

private:
    vector<TRessource> ressourceVecteur;
};

#endif // TRESSOURCEDAO_H
