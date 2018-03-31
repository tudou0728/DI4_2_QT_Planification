#ifndef PLANIFICATION_H
#define PLANIFICATION_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include "gererbd.h"
#include <vector>
#include <functional>
#include <algorithm>
#include "tclient.h"
#include "sortpriorite.h"
#include "planderessource.h"
#include "trdvdao.h"
#include <QFile>
#include <QStandardItemModel>

class Planification
{
    public:
        vector<TClient> getRdv(QSqlQuery query);
        vector<TClient> trierPriorite(vector<TClient> clients);
        vector<PlanDeRessource> planifier(vector<TClient> clients);
        void ajouterUnPlan(vector<PlanDeRessource>planDeRessources,TClient client);
        int verifierPlan(PlanDeRessource pClient,PlanDeRessource pRessource,int duree);
        QString enregistrerFile(vector<PlanDeRessource> planifications, QString fileNom);
        QStandardItemModel* setModelPlanification(vector<PlanDeRessource> planifications);
    private:
        TRdvDAO tRdvDAO;
};
#endif // PLANIFICATION_H
