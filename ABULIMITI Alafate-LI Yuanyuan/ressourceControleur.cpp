#include "ressourceControleur.h"


RessourceControleur::RessourceControleur()
{

}

QStandardItemModel* RessourceControleur::setModel()
{
    QStandardItemModel* model=new QStandardItemModel() ;
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("Ressources")<<QStringLiteral("Attribut"));
    QStandardItem* item=new QStandardItem("Type de ressources");
    model->appendRow(item);
    model->setItem(model->indexFromItem(item).row(),1,new QStandardItem(QStringLiteral("info")));
    QSqlQuery query=tRessourceDAO.rechercherAllType();
    QStringList listType=tRessourceDAO.inverseToString(query);
    for(int i=0;i<listType.size();i++)
    {
        QStandardItem *item1 = new QStandardItem(listType.at(i));
        item->appendRow(item1);
        item->setChild(item1->index().row(),1,new QStandardItem(QStringLiteral("Type")));
        QSqlQuery query2=tRessourceDAO.rechercherTypeLabel(listType.at(i));
        while(query2.next())
        {
            QStandardItem *item2 = new QStandardItem(query2.value(1).toString());
            item1->appendRow(item2);
            item1->setChild(item2->index().row(),1,new QStandardItem(QStringLiteral("Nom")));
        }
    }
    return model;
}
