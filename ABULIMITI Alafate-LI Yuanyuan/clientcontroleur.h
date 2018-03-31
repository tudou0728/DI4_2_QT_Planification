#ifndef CLIENTCONTROLEUR_H
#define CLIENTCONTROLEUR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QStandardItemModel>
#include "gererbd.h"
#include "tclientdao.h"

class ClientControleur
{
public:
    ClientControleur();
    QStandardItemModel* setModelParDate(QString nom,QString prenom,QString id,QString dateDebut,QString dateFin);
    QStandardItemModel* setModelNonDate(QString nom,QString prenom,QString id);

private:
    TClientDAO tClientDAO;

};
#endif // CLIENTCONTROLEUR_H
