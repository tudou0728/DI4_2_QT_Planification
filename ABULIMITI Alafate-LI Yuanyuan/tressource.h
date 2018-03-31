#ifndef TRESSOURCE_H
#define TRESSOURCE_H
#include<cstdio>
#include<iostream>
#include "ttype.h"
#include <QString>
using namespace std;

class TRessource
{
public:
    TRessource();


    int getId() const;
    void setId(int value);

    QString getNom() const;
    void setNom(const QString &value);

    QString getPrenom() const;
    void setPrenom(const QString &value);

    int getIdType() const;
    void setIdType(int value);

private:
    int id;
    QString nom;
    QString prenom;
    int idType;

};

#endif // TRESSOURCE_H
