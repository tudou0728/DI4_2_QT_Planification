#ifndef TRDVDAO_H
#define TRDVDAO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include "gererbd.h"
#include "tclient.h"
#include"trdv.h"
#include<vector>
using namespace std;

class TRdvDAO
{
private:
    vector<TRdv> rdvVecteur;

public:
    TRdvDAO();
    QSqlQuery rechercherParDate(QString date);
    QSqlQuery rechercherRessource(QString date);

    void lireR();
    void ajouterR(vector<int> idRessourceVecteur,int IdCLient);
    vector<TRdv> getRdvVecteur() const;
    void setRdvVecteur(const vector<TRdv> &value);
};

#endif // TRDVDAO_H
