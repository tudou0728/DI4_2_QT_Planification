#include "clientcontroleur.h"

ClientControleur::ClientControleur()
{

}

QStandardItemModel* ClientControleur::setModelParDate(QString nom,QString prenom,QString id,QString dateDebut,QString dateFin)
{
    QStandardItemModel *model=new QStandardItemModel();
    QSqlQuery query=tClientDAO.rechercherDate(nom,prenom,id,dateDebut,dateFin);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Id")<<QStringLiteral("Nom")<<QStringLiteral("Prenom")<<QStringLiteral("Date de rendez-vous"));
    int ligne=0;
    while(query.next())
    {
        qDebug() << query.value(0).toString();
        QStandardItem *item0 = new QStandardItem(query.value(0).toString());
        model->setItem(ligne, 0, item0);
        QStandardItem *item1 = new QStandardItem(query.value(1).toString());
        model->setItem(ligne, 1, item1);
        QStandardItem *item2 = new QStandardItem(query.value(2).toString());
        model->setItem(ligne, 2, item2);
        QStandardItem *item3 = new QStandardItem(query.value(8).toString());
        model->setItem(ligne, 3, item3);
        ligne++;
    }
    return model;
}

QStandardItemModel* ClientControleur::setModelNonDate(QString nom,QString prenom,QString id)
{
    QStandardItemModel *model=new QStandardItemModel();
    QSqlQuery query=tClientDAO.rechercher(nom,prenom,id);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Id")<<QStringLiteral("Nom")<<QStringLiteral("Prenom")<<QStringLiteral("Date de rendez-vous"));
    int ligne=0;
    while(query.next())
    {
        qDebug() << query.value(0).toString();
        QStandardItem *item0 = new QStandardItem(query.value(0).toString());
        model->setItem(ligne, 0, item0);
        QStandardItem *item1 = new QStandardItem(query.value(1).toString());
        model->setItem(ligne, 1, item1);
        QStandardItem *item2 = new QStandardItem(query.value(2).toString());
        model->setItem(ligne, 2, item2);
        QStandardItem *item3 = new QStandardItem(query.value(8).toString());
        model->setItem(ligne, 3, item3);
        ligne++;
    }
    return model;
}

