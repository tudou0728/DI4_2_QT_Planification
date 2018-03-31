#include "tcompte.h"

TCompte::TCompte()
{

}

int TCompte::getId() const
{
    return id;
}

void TCompte::setId(int value)
{
    id = value;
}

int TCompte::getIdRessource() const
{
    return idRessource;
}

void TCompte::setIdRessource(int value)
{
    idRessource = value;
}

QString TCompte::getLogIn() const
{
    return logIn;
}

void TCompte::setLogIn(const QString &value)
{
    logIn = value;
}

QString TCompte::getMdp() const
{
    return mdp;
}

void TCompte::setMdp(const QString &value)
{
    mdp = value;
}
