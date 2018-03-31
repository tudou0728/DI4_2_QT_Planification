#ifndef TCLIENT_H
#define TCLIENT_H
#include<cstdio>
#include<iostream>
#include <QDate>
#include <QString>
#include <vector>
using namespace std;

class TClient
{
public:
    TClient();
    TClient(int id,QString nom,QString prenom,QString adresse,
            QString ville,int cP,QString commentaire,int tel,
            QString dateRdv,int dureeRdv,int priorite,
    vector<int> idRessourcesVecteur);

    int getId() const;
    void setId(int value);

    QString getNom() const;
    void setNom(const QString &value);

    QString getAdresse() const;
    void setAdresse(const QString &value);

    QString getVille() const;
    void setVille(const QString &value);

    int getCP() const;
    void setCP(int value);

    QString getCommentaire() const;
    void setCommentaire(const QString &value);

    int getTel() const;
    void setTel(int value);

    QString getDateRdv() const;
    void setDateRdv(const QString &value);

    int getDureeRdv() const;
    void setDureeRdv(int value);

    int getPriorite() const;
    void setPriorite(int value);

    vector<int> getIdRessourcesVecteur() const;
    void setIdRessourcesVecteur(const vector<int> &value);

    void addIdRessource(int idRessource);

    QString getPrenom() const;
    void setPrenom(const QString &value);

private:
    int id;
    QString nom;
    QString prenom;
    QString adresse;
    QString ville;
    int cP;
    QString commentaire;
    int tel;
    QString dateRdv;
    int dureeRdv;
    int priorite;
    vector<int> idRessourcesVecteur;

};

#endif // TCLIENT_H
