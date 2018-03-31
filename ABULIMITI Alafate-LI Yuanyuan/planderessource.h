#ifndef PLANDERESSOURCE_H
#define PLANDERESSOURCE_H
#include<cstdio>
#include<iostream>
#include <QString>
#include <vector>
#include "sortressource.h"
using namespace std;

class PlanDeRessource{
public:
    PlanDeRessource(){}
    int getIdRessource() const;
    void setIdRessource(int value);

    vector<vector<int> > getPlans() const;
    void setPlans(const vector<vector<int> > &value);

    PlanDeRessource(int idRessource,vector<vector<int>> plans,QString date);
    void ajouterPlan(vector<int> plan);

    QString getDate() const;
    void setDate(const QString &value);

    void modifierPlan(int id,int heureDebut,int minuteDebut,int heureFin,int minuteFin);


private:
    int idRessource;
    QString date;
    vector<vector<int>> plans;

};
#endif // PLANDERESSOURCE_H
