#ifndef RESSOURCECONTROLEUR_H
#define RESSOURCECONTROLEUR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QStandardItemModel>
#include "gererbd.h"
#include "tressourcedao.h"

class RessourceControleur
{
    public:
    RessourceControleur();
    QStandardItemModel* setModel();

private:
TRessourceDAO tRessourceDAO;
};

#endif // RESSOURCECONTROLEUR_H
