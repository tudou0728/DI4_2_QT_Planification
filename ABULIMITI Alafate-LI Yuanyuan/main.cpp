#include "mainwindow.h"
#include "dialoglog.h"
#include <QApplication>
#include "dialogproposinfo.h"
#include "gererbd.h"
#include "c_init_bd.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include <vector>
#include "tclientdao.h"
#include "tressourcedao.h"
#include "trdvdao.h"
#include "planification.h"
#include "planderessource.h"
#include<QSet>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(GererBD::connecter())
    {
        MainWindow mainWindows;
        DialogLog dialogLog;

        QSet<int> set1 , set2;
        set1.insert(89);
        set1.insert(85);
        set1.insert(74);
        set1.insert(23);
        set1.insert(86);
        set1.insert(95);
        set2.insert(0);
        set2.insert(6);
        set2.insert(12);
        set2.insert(18);
        set2.insert(22);

        qDebug()<<set2;
        set1+=set2;
         qDebug()<<set1;

         for(int i =0 ; i<set1.size();i++){
            qDebug()<< set1.values().at(i);
         }





        if(dialogLog.exec()==QDialog::Accepted)
        {
            mainWindows.show();
            return a.exec();
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
