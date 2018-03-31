#include "planderessource.h"


PlanDeRessource::PlanDeRessource(int idRessource,vector<vector<int>> plans,QString date)
{
    this->idRessource=idRessource;
    sort(plans.begin(),plans.end(),SortRessource());
    this->date=date;
    this->plans=plans;
}
int PlanDeRessource::getIdRessource() const
{
    return idRessource;
}

void PlanDeRessource::setIdRessource(int value)
{
    idRessource = value;
}

vector<vector<int> > PlanDeRessource::getPlans() const
{
    return plans;
}

void PlanDeRessource::setPlans(const vector<vector<int> > &value)
{
    plans = value;
}

void PlanDeRessource::ajouterPlan(vector<int> plan)
{
    this->plans.push_back(plan);
    sort(plans.begin(),plans.end(),SortRessource());
}

QString PlanDeRessource::getDate() const
{
    return date;
}

void PlanDeRessource::setDate(const QString &value)
{
    date = value;
}

void PlanDeRessource::modifierPlan(int id,int heureDebut,int minuteDebut,int heureFin,int minuteFin)
{
    for(unsigned i=0;i<plans.size();i++)
    {
        if(plans.at(i).at(0)==id)
        {
            plans.at(i).at(1)=heureDebut;
            plans.at(i).at(2)=minuteDebut;
            plans.at(i).at(3)=heureFin;
            plans.at(i).at(4)=minuteFin;
        }
    }
    sort(plans.begin(),plans.end(),SortRessource());
}

