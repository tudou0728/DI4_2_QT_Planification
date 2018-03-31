#ifndef TCOMPTE_H
#define TCOMPTE_H
#include<cstdio>
#include<iostream>
#include <QString>
#include "tressource.h"
using namespace std;

class TCompte
{
public:
    TCompte();


    int getId() const;
    void setId(int value);

    int getIdRessource() const;
    void setIdRessource(int value);

    QString getLogIn() const;
    void setLogIn(const QString &value);

    QString getMdp() const;
    void setMdp(const QString &value);

private:
    int id;
    int idRessource;
    QString logIn;
    QString mdp;


};
#endif // TCOMPTE_H
