#ifndef TCOMPTEDAO_H
#define TCOMPTEDAO_H
#include <qstring.h>
#include<cstdio>
#include<iostream>
#include <QDate>
using namespace std;

class TcompteDAO
{
public :
    bool verifierLogin(QString username, QString password);

};

#endif // TCOMPTEDAO_H
