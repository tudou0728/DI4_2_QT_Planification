#include "trdv.h"

TRdv::TRdv()
{

}

int TRdv::getId() const
{
    return id;
}

void TRdv::setId(int value)
{
    id = value;
}

int TRdv::getIdClient() const
{
    return idClient;
}

void TRdv::setIdClient(int value)
{
    idClient = value;
}

int TRdv::getIdRessource() const
{
    return idRessource;
}

void TRdv::setIdRessource(int value)
{
    idRessource = value;
}
