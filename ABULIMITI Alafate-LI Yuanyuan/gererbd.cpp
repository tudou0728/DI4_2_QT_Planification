#include "gererbd.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>


QSqlDatabase GererBD::baseDeDonnes=QSqlDatabase::addDatabase("QSQLITE","connectBD");


bool GererBD::connecter()
{
    bool connecte=false;
    if(baseDeDonnes.isValid())
    {
        baseDeDonnes.setHostName("localhost");
        baseDeDonnes.setUserName("root");
        baseDeDonnes.setPassword("password");

        if(QFile::exists("base_tmp.sqli"))
        {
            baseDeDonnes.setDatabaseName("base_tmp.sqli");
            baseDeDonnes.open();
            if(!baseDeDonnes.isOpen())
            {
                qDebug() << baseDeDonnes.lastError().text();
                qDebug() << "Erreur à louverture de la base !\n";
            }
            else
            {
               qDebug() <<"gerer BD.\n";
               connecte=true;
            }
        }
        else
        {
            C_INIT_BD::Creation_BD();
            return connecter();
        }
    }
    else
    {
        qDebug() << baseDeDonnes.lastError().text();
        qDebug() << "Erreur à création de la base !\n";
    }
    return connecte;
}
bool GererBD::fermer()
{
    baseDeDonnes =QSqlDatabase::database("connectBD");
    if(baseDeDonnes.isOpen())
    {
        baseDeDonnes.close();
        baseDeDonnes.removeDatabase("QSQLITE");
        qDebug()<<"ferme la BD.\n";
    }
    return true;
}

QSqlDatabase GererBD::getBD()
{
    return baseDeDonnes;
}
