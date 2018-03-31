#ifndef SORTPRIORITE_H
#define SORTPRIORITE_H
#include "tclient.h"


class SortPriorite{
    public:
        SortPriorite(){

        }
        bool operator()(TClient client1,TClient client2){
            int priorite1=client1.getPriorite()*100+client1.getIdRessourcesVecteur().size()*10+client1.getIdRessourcesVecteur().size()*client1.getDureeRdv();
            int priorite2=client2.getPriorite()*100+client2.getIdRessourcesVecteur().size()*10+client2.getIdRessourcesVecteur().size()*client2.getDureeRdv();
            if(priorite2<priorite1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};
#endif // SORTPRIORITE_H
