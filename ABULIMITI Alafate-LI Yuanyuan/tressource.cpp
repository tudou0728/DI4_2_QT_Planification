#include "tressource.h"

TRessource::TRessource()
{

}

int TRessource::getId() const
{
    return id;
}

void TRessource::setId(int value)
{
    id = value;
}

QString TRessource::getNom() const
{
    return nom;
}

void TRessource::setNom(const QString &value)
{
    nom = value;
}

QString TRessource::getPrenom() const
{
    return prenom;
}

void TRessource::setPrenom(const QString &value)
{
    prenom = value;
}

int TRessource::getIdType() const
{
    return idType;
}

void TRessource::setIdType(int value)
{
    idType = value;
}
