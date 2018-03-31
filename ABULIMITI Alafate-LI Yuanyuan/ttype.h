#ifndef TTYPE_H
#define TTYPE_H
#include<cstdio>
#include<iostream>
#include <QString>
using namespace std;

class TType
{
public:
    TType();

    int getId() const;
    void setId(int value);

    QString getLabel() const;
    void setLabel(const QString &value);

private:
    int id;
    QString label;
};

#endif // TTYPE_H
