#ifndef TRDV_H
#define TRDV_H
#include "tclient.h"
#include "tressource.h"

class TRdv
{
public:
    TRdv();

    int getId() const;
    void setId(int value);

    int getIdClient() const;
    void setIdClient(int value);

    int getIdRessource() const;
    void setIdRessource(int value);

private:
    int id;
    int idClient;
    int idRessource;
};

#endif // TRDV_H
