#include "planification.h"

vector<TClient> Planification::getRdv(QSqlQuery query)
{
    vector<TClient> clients;
    while(query.next())
    {
        if(clients.size()==0 ||clients.at(clients.size()-1).getId()!=query.value(1).toInt())
        {
            vector<int> idRessourcesVecteur;
            idRessourcesVecteur.push_back(query.value(2).toInt());
            TClient tClient(query.value(1).toInt(),
                            query.value(4).toString(),
                            query.value(5).toString(),
                            query.value(6).toString(),
                            query.value(7).toString(),
                            query.value(8).toInt(),
                            query.value(9).toString(),
                            query.value(10).toInt(),
                            query.value(11).toString(),
                            query.value(12).toInt(),
                            query.value(13).toInt(),
                            idRessourcesVecteur);
            clients.push_back(tClient);
        }
        else
        {
            clients.at(clients.size()-1).addIdRessource(query.value(2).toInt());
        }
    }
    return clients;
}

vector<TClient> Planification::trierPriorite(vector<TClient> clients)
{
    sort(clients.begin(),clients.end(),SortPriorite());
    return clients;
}

vector<PlanDeRessource> Planification::planifier(vector<TClient> clients)
{
    QString date=clients.at(0).getDateRdv();

    vector<PlanDeRessource> planifications;
    QSqlQuery query=tRdvDAO.rechercherRessource(date);
    while(query.next())
    {
        PlanDeRessource planDeRessource;
        planDeRessource.setDate(date);
        planDeRessource.setIdRessource(query.value(0).toInt());
        vector<vector<int>> plan;
        vector<int> temp;
        temp.push_back(0);
        temp.push_back(8);
        temp.push_back(0);
        temp.push_back(8);
        temp.push_back(0);
        plan.push_back(temp);
        planDeRessource.setPlans(plan);
        planifications.push_back(planDeRessource);
    }

    vector<PlanDeRessource> planificationsClients;
    vector<TClient>::iterator itClient;

    for(itClient=clients.begin();itClient!=clients.end();itClient++)
    {

        PlanDeRessource planDeClient;
        planDeClient.setDate(date);
        planDeClient.setIdRessource(itClient->getId());
        vector<vector<int>> plansClient;
        vector<int> temp;
        temp.push_back(0);
        temp.push_back(8);
        temp.push_back(0);
        temp.push_back(8);
        temp.push_back(0);
        plansClient.push_back(temp);
        planDeClient.setPlans(plansClient);
        planificationsClients.push_back(planDeClient);
    }


    for(unsigned int c=0;c<clients.size();c++)
    {

        for(unsigned cp=0;cp<clients.at(c).getIdRessourcesVecteur().size();cp++)
        {

            for(unsigned r=0; r<planifications.size();r++)
            {
                if(clients.at(c).getIdRessourcesVecteur().at(cp)==planifications.at(r).getIdRessource())
                {
                    int duree=clients.at(c).getDureeRdv();
                    int flag=verifierPlan(planificationsClients.at(c),planifications.at(r),duree);
                    if(flag==0)
                    {
                        vector<int> planRessource;
                        planRessource.push_back(clients.at(c).getId());
                        planRessource.push_back(8);
                        planRessource.push_back(0);
                        planRessource.push_back(8 + (duree)/60);
                        planRessource.push_back((duree)%60);
                        planifications.at(r).ajouterPlan(planRessource);

                        vector<int> planClient;
                        planClient.push_back(planifications.at(r).getIdRessource());
                        planClient.push_back(8);
                        planClient.push_back(0);
                        planClient.push_back(8 + (duree)/60);
                        planClient.push_back((duree)%60);
                        planificationsClients.at(c).ajouterPlan(planClient);
                     }
                    else if(flag >0)
                    {
                        vector<int> planPre=planifications.at(r).getPlans().at(flag-1);                      
                        if(planPre.at(4)%15 !=0)
                        {
                            vector<int> planRessource;
                            planRessource.push_back(clients.at(c).getId());
                            planRessource.push_back(planPre.at(3) + (planPre.at(4)/15 +1)/4);
                            planRessource.push_back(((planPre.at(4)/15 +1)*15) %60);
                            planRessource.push_back(planRessource.at(1) + (duree+planRessource.at(2))/60);
                            planRessource.push_back((duree+planRessource.at(2))%60);
                            planifications.at(r).ajouterPlan(planRessource);

                            vector<int> planClient;
                            planClient.push_back(planifications.at(r).getIdRessource());
                            planClient.push_back(planPre.at(3) + (planPre.at(4)/15 +1)/4);
                            planClient.push_back(((planPre.at(4)/15 +1)*15) %60);
                            planClient.push_back(planRessource.at(3));
                            planClient.push_back(planRessource.at(4));
                            planificationsClients.at(c).ajouterPlan(planClient);
                        }
                        else
                        {
                            vector<int> planRessource;
                            planRessource.push_back(clients.at(c).getId());
                            planRessource.push_back(planPre.at(3));
                            planRessource.push_back(planPre.at(4));
                            planRessource.push_back(planRessource.at(1) + (duree + planRessource.at(2))/60);
                            planRessource.push_back((duree + planRessource.at(2))%60);
                            planifications.at(r).ajouterPlan(planRessource);

                            vector<int> planClient;
                            planClient.push_back(planifications.at(r).getIdRessource());
                            planClient.push_back(planPre.at(3));
                            planClient.push_back(planPre.at(4));
                            planClient.push_back(planRessource.at(3));
                            planClient.push_back(planRessource.at(4));
                            planificationsClients.at(c).ajouterPlan(planClient);
                        }
                    }
                    else
                    {
                        int position=abs(flag)-1;
                        vector<int> planPre=planificationsClients.at(c).getPlans().at(position-1);
                        if(planPre.at(4)%15 !=0)
                        {
                            vector<int> planRessource;
                            planRessource.push_back(clients.at(c).getId());
                            planRessource.push_back(planPre.at(3) + (planPre.at(4)/15 +1)/4);
                            planRessource.push_back(((planPre.at(4)/15 +1)*15) %60);
                            planRessource.push_back(planRessource.at(1) + (duree+ planRessource.at(2))/60);
                            planRessource.push_back((duree+ planRessource.at(2))%60);
                            planifications.at(r).ajouterPlan(planRessource);

                            vector<int> planClient;
                            planClient.push_back(planifications.at(r).getIdRessource());
                            planClient.push_back(planPre.at(3) + (planPre.at(2)/15 +1)/4);
                            planClient.push_back(((planPre.at(4)/15 +1)*15) %60);
                            planClient.push_back(planRessource.at(3));
                            planClient.push_back(planRessource.at(4));
                            planificationsClients.at(c).ajouterPlan(planClient);
                        }
                        else
                        {
                            vector<int> planRessource;
                            planRessource.push_back(clients.at(c).getId());
                            planRessource.push_back(planPre.at(3));
                            planRessource.push_back(planPre.at(4));
                            planRessource.push_back(planRessource.at(1) + (duree+planRessource.at(2))/60);
                            planRessource.push_back((planRessource.at(2)+duree)%60);
                            planifications.at(r).ajouterPlan(planRessource);

                            vector<int> planClient;
                            planClient.push_back(planifications.at(r).getIdRessource());
                            planClient.push_back(planPre.at(3));
                            planClient.push_back(planPre.at(4));
                            planClient.push_back(planRessource.at(3));
                            planClient.push_back(planRessource.at(4));
                            planificationsClients.at(c).ajouterPlan(planClient);
                        }
                    }
                }
            }
        }
    }
    return planifications;
}

void Planification::ajouterUnPlan(vector<PlanDeRessource>planDeRessources,TClient client)
{
    int duree=client.getDureeRdv();
    for(int unsigned i=0;i<client.getIdRessourcesVecteur().size();i++)
    {
        vector<PlanDeRessource>::iterator itPlan;
        for(itPlan=planDeRessources.begin();itPlan!=planDeRessources.end();itPlan++)
        {
            if(itPlan->getIdRessource()==client.getIdRessourcesVecteur().at(i))
            {
                if(itPlan->getPlans().size()==0)
                {
                    vector<int> plan;
                    plan.push_back(8);
                    plan.push_back(0);
                    plan.push_back((duree/60)+8);
                    plan.push_back(duree%60);
                    itPlan->ajouterPlan(plan);
                }
                else if(itPlan->getPlans().size()==1)
                {
                    int repos=60*(itPlan->getPlans().at(0).at(0)-8)+itPlan->getPlans().at(0).at(1);
                    if(repos>duree)
                    {
                        vector<int> plan;
                        plan.push_back(8);
                        plan.push_back(0);
                        plan.push_back((duree/60)+8);
                        plan.push_back(duree%60);
                        itPlan->ajouterPlan(plan);
                    }
                    else
                    {
                        vector<int> plan;
                        plan.push_back(itPlan->getPlans().at(0).at(2)+(itPlan->getPlans().at(0).at(3))/45);
                        plan.push_back((((itPlan->getPlans().at(0).at(3))/15 + 1)*15)%60);
                        plan.push_back(plan.at(0)+duree/60);
                        plan.push_back(plan.at(1)+duree%60);
                        itPlan->ajouterPlan(plan);
                    }
                }
                else
                {
                    int unsigned j=1;
                    for(j=1;j<itPlan->getPlans().size();j++)
                    {
                        int repos=60*(itPlan->getPlans().at(j).at(0)-itPlan->getPlans().at(j-1).at(2))
                                +15*(itPlan->getPlans().at(j).at(1)-15*(itPlan->getPlans().at(j-1).at(0)/15 + 1));
                        if(repos>duree)
                        {
                            vector<int> plan;
                            plan.push_back(itPlan->getPlans().at(j-1).at(2)+(itPlan->getPlans().at(j-1).at(3))/45);
                            plan.push_back((((itPlan->getPlans().at(j-1).at(3))/15 + 1)*15)%60);
                            plan.push_back(plan.at(0)+duree/60);
                            plan.push_back(plan.at(1)+duree%60);
                            itPlan->ajouterPlan(plan);
                            break;
                        }
                    }
                    if(j==itPlan->getPlans().size())
                    {
                        vector<int> plan;
                        plan.push_back(itPlan->getPlans().at(j-1).at(2)+(itPlan->getPlans().at(j-1).at(3))/45);
                        plan.push_back((((itPlan->getPlans().at(j-1).at(3))/15 + 1)*15)%60);
                        plan.push_back(plan.at(0)+duree/60);
                        plan.push_back(plan.at(1)+duree%60);
                        itPlan->ajouterPlan(plan);
                    }
                }
            }
        }
    }
}

int Planification::verifierPlan(PlanDeRessource pClient,PlanDeRessource pRessource,int duree)
{
    int flag=0;
    int repos=0;

    if(pClient.getPlans().size()==1 && pRessource.getPlans().size()==1)
    {
        flag=1;
    }

     else if(pClient.getPlans().size()==1 && pRessource.getPlans().size()>1)
     {
        unsigned int i=1;
        for(i=1;i<pRessource.getPlans().size();i++)
        {
            repos=60*(pRessource.getPlans().at(i).at(1)-pRessource.getPlans().at(i-1).at(3))
                    +pRessource.getPlans().at(i).at(2)-pRessource.getPlans().at(i-1).at(4);
            if(repos>=duree)
            {
                flag=i;//insert into position=i
            }
        }
        if(i==pRessource.getPlans().size())
        {
            flag=pRessource.getPlans().size();//insert into position=i
        }
    }

    else if(pClient.getPlans().size()>1 && pRessource.getPlans().size()==1)
    {

        unsigned int i=0;
        for(i=1;i<pClient.getPlans().size();i++)
        {
            repos=60*(pClient.getPlans().at(i).at(1)-pClient.getPlans().at(i-1).at(3))
                    +pClient.getPlans().at(i).at(2)-pClient.getPlans().at(i-1).at(4);
            if(repos>=duree)
            {
                flag=-(i+1);//insert into i;
            }
        }
        if(i==pClient.getPlans().size())
        {
            flag=-(i+1);//insert into i;
        }
    }

    else if(pClient.getPlans().size()>1 && pRessource.getPlans().size()>1)
    {
        unsigned int x=0;
        for(x=1;x<pRessource.getPlans().size();x++)
        {
            int repos3=60*(pRessource.getPlans().at(x).at(1)-pRessource.getPlans().at(x-1).at(3))
                    +pRessource.getPlans().at(x).at(2)-pRessource.getPlans().at(x-1).at(4);
            if(repos3>=duree)
            {
                unsigned y=1;
                for(y=1;y<pClient.getPlans().size();x++)
                {

                    if((pRessource.getPlans().at(x-1).at(3)<pClient.getPlans().at(y-1).at(3)) ||
                            ((pRessource.getPlans().at(x-1).at(3)==pClient.getPlans().at(y-1).at(3))
                           &&(pRessource.getPlans().at(x-1).at(4)<=pClient.getPlans().at(y-1).at(4))))
                    {

                        if((pRessource.getPlans().at(x).at(1)<pClient.getPlans().at(y).at(1)) ||
                                ((pRessource.getPlans().at(x).at(1)==pClient.getPlans().at(y).at(1))
                                 &&(pRessource.getPlans().at(x).at(2)<=pClient.getPlans().at(y).at(2))))
                        {
                            repos=60*(pRessource.getPlans().at(x).at(1)-pClient.getPlans().at(y-1).at(3))
                                    +pRessource.getPlans().at(x).at(2)-pClient.getPlans().at(y-1).at(4);
                            if(repos>=duree)
                            {
                                flag=-(y+1);//insert into position=y
                            }
                        }
                        else if((pRessource.getPlans().at(x).at(1)>pClient.getPlans().at(y).at(1)) ||
                                ((pRessource.getPlans().at(x).at(1)==pClient.getPlans().at(y).at(1))
                                 &&(pRessource.getPlans().at(x).at(2)>=pClient.getPlans().at(y).at(2))))
                        {
                            repos=60*(pRessource.getPlans().at(y).at(1)-pRessource.getPlans().at(y-1).at(3))
                                    +pRessource.getPlans().at(y).at(2)-pRessource.getPlans().at(y-1).at(4);
                            if(repos>=duree)
                            {
                                flag=-(y+1);//insert into position=y
                            }
                        }
                    }

                    else if((pRessource.getPlans().at(x-1).at(3)>pClient.getPlans().at(y-1).at(3)) ||
                            ((pRessource.getPlans().at(x-1).at(3)==pClient.getPlans().at(y-1).at(3))
                             &&(pRessource.getPlans().at(x-1).at(4)>=pClient.getPlans().at(y-1).at(4))))
                    {
                        if((pRessource.getPlans().at(x).at(1)<pClient.getPlans().at(y).at(1)) ||
                                ((pRessource.getPlans().at(x).at(1)==pClient.getPlans().at(y).at(1))
                                 &&(pRessource.getPlans().at(x).at(1)<=pClient.getPlans().at(y).at(2))))
                        {
                            flag=x;//insert into position=x;
                        }
                        else if((pRessource.getPlans().at(x).at(1)>pClient.getPlans().at(y).at(1)) ||
                                ((pRessource.getPlans().at(x).at(1)==pClient.getPlans().at(y).at(1))
                                 &&(pRessource.getPlans().at(x).at(2)>=pClient.getPlans().at(y).at(2))))
                        {
                            repos=60*(pClient.getPlans().at(y).at(1)-pRessource.getPlans().at(x-1).at(3))
                                    +pClient.getPlans().at(y).at(2)-pRessource.getPlans().at(x-1).at(4);
                            if(repos>=duree)
                            {
                                flag=x;
                            }
                        }
                    }
                }
            }
        }

        if(((pRessource.getPlans().at(pRessource.getPlans().size()-1).at(3))>(pClient.getPlans().at(pClient.getPlans().size()-1).at(3)))
                || (((pRessource.getPlans().at(pRessource.getPlans().size()-1).at(3))
                     ==(pClient.getPlans().at(pClient.getPlans().size()-1).at(3)))
                    &&((pRessource.getPlans().at(pRessource.getPlans().size()-1).at(4))
                       >=(pClient.getPlans().at(pClient.getPlans().size()-1).at(4)))))
        {
            flag=pRessource.getPlans().size();
        }
        else
        {
            flag=-(pClient.getPlans().size() + 1);
        }
    }
    return flag;
}

QString Planification::enregistrerFile(vector<PlanDeRessource> planifications, QString fileNom)
{
    QFile file(fileNom);
    if(file.open(QIODevice::Text|QFile::WriteOnly|QIODevice::Truncate))
    {
        QTextStream out(&file);
        vector<PlanDeRessource>::iterator itPlianification;
        int i=1;
        for(itPlianification=planifications.begin();itPlianification!=planifications.end();itPlianification++)
        {
            unsigned int j=1;
            for(j=1;j<itPlianification->getPlans().size();j++)
            {
                out<<i<<'\n';
                out<<"Date de RDV: "<<itPlianification->getDate()<<'\n';
                out<<"Id de ressource: "<<itPlianification->getIdRessource()<<'\n';
                out<<"Id de client: "<<itPlianification->getPlans().at(j).at(0)<<'\n';
                out<<"Temps debut: "<<itPlianification->getPlans().at(j).at(1)<<" h "<<itPlianification->getPlans().at(j).at(2)<<" m"<<'\n';
                out<<"Temps fin: "<<itPlianification->getPlans().at(j).at(3)<<" h "<<itPlianification->getPlans().at(j).at(4)<<" m"<<'\n';
                out<<'\n';
                i++;
            }
        }
        file.close();
        return fileNom;
    }
    else
    {
        return "Enregistrer error!";
    }
}

QStandardItemModel* Planification::setModelPlanification(vector<PlanDeRessource> planifications)
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("IdRessource")<<QStringLiteral("IdClient")<<QStringLiteral("DateRdv")<<QStringLiteral("Temps Debut")<<QStringLiteral("Temps Fin"));
    vector<PlanDeRessource>::iterator itPlan;
    int ligne=0;
    for(itPlan=planifications.begin();itPlan!=planifications.end();itPlan++)
    {

        unsigned i=1;
        for(i=1;i<itPlan->getPlans().size();i++)
        {
            QStandardItem *item0 = new QStandardItem(QString::number(itPlan->getIdRessource(),10));
            model->setItem(ligne, 0, item0);
            QStandardItem *item1 = new QStandardItem(QString::number(itPlan->getPlans().at(i).at(0),10));
            model->setItem(ligne, 1, item1);
            QStandardItem *item2 = new QStandardItem(itPlan->getDate());
            model->setItem(ligne, 2, item2);
            QString temps1=QString::number(itPlan->getPlans().at(i).at(1),10)+"h" + QString::number(itPlan->getPlans().at(i).at(2),10)+"m";
            QStandardItem *item3 = new QStandardItem(temps1);
            model->setItem(ligne, 3, item3);
            QString temps2=QString::number(itPlan->getPlans().at(i).at(3),10)+"h" + QString::number(itPlan->getPlans().at(i).at(4),10)+"m";
            QStandardItem *item4 = new QStandardItem(temps2);
            model->setItem(ligne, 4, item4);
            ligne++;
        }
    }
    return model;
}
