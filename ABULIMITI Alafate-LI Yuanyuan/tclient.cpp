#include "tclient.h"

TClient::TClient()
{

}

TClient::TClient(int id,QString nom,QString prenom,QString adresse,
        QString ville,int cP,QString commentaire,int tel,
        QString dateRdv,int dureeRdv,int priorite,
vector<int> idRessourcesVecteur)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->ville=ville;
    this->cP=cP;
    this->commentaire=commentaire;
    this->tel=tel;
    this->dateRdv=dateRdv;
    this->dureeRdv=dureeRdv;
    this->priorite=priorite;
    this->idRessourcesVecteur=idRessourcesVecteur;

}
int TClient::getId() const
{
    return id;
}

void TClient::setId(int value)
{
    id = value;
}

QString TClient::getNom() const
{
    return nom;
}

void TClient::setNom(const QString &value)
{
    nom = value;
}

QString TClient::getAdresse() const
{
    return adresse;
}

void TClient::setAdresse(const QString &value)
{
    adresse = value;
}

QString TClient::getVille() const
{
    return ville;
}

void TClient::setVille(const QString &value)
{
    ville = value;
}

int TClient::getCP() const
{
    return cP;
}

void TClient::setCP(int value)
{
    cP = value;
}

QString TClient::getCommentaire() const
{
    return commentaire;
}

void TClient::setCommentaire(const QString &value)
{
    commentaire = value;
}

int TClient::getTel() const
{
    return tel;
}

void TClient::setTel(int value)
{
    tel = value;
}

QString TClient::getDateRdv() const
{
    return dateRdv;
}

void TClient::setDateRdv(const QString &value)
{
    dateRdv = value;
}

int TClient::getDureeRdv() const
{
    return dureeRdv;
}

void TClient::setDureeRdv(int value)
{
    dureeRdv = value;
}

int TClient::getPriorite() const
{
    return priorite;
}

void TClient::setPriorite(int value)
{
    priorite = value;
}

vector<int> TClient::getIdRessourcesVecteur() const
{
    return idRessourcesVecteur;
}

void TClient::setIdRessourcesVecteur(const vector<int> &value)
{
    idRessourcesVecteur = value;
}

void TClient::addIdRessource(int idRessource)
{
    this->idRessourcesVecteur.push_back(idRessource);
}

QString TClient::getPrenom() const
{
    return prenom;
}

void TClient::setPrenom(const QString &value)
{
    prenom = value;
}
