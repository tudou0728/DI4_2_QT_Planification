#include "modifiersupprimerclientdialog.h"
#include "ui_modifiersupprimerclientdialog.h"
#include "tclientdao.h"
#include <QMessageBox>
#include<QDebug>

ModifiersupprimerclientDialog::ModifiersupprimerclientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifiersupprimerclientDialog)
{
    ui->setupUi(this);
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEditTel );
    ui->lineEditTel->setValidator(validator);
    ui->lineEditCP->setValidator(validator);
    ui->lineEditDureeRdv->setValidator(validator);

}

ModifiersupprimerclientDialog::~ModifiersupprimerclientDialog()
{
    delete ui;

}

void ModifiersupprimerclientDialog::receiveData(int id, QString nom,QString prenom,
                                                QString adresse,QString ville,int cp,QString commentaire,int tel ,
                                                QString date, int duree,int prio)
{
    ui->labeliD->setText(QString::number(id));
    qDebug() <<date;
    ui->dateEditRdv->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    qDebug() <<QDate::fromString(date, "yyyy-MM-dd");
    ui->lineEditCommentaire->setText(commentaire);
    ui->lineEditCP->setText(QString::number(cp));
    ui->lineEditDureeRdv->setText(QString::number(duree));
    ui->lineEditNom->setText(nom);
    ui->lineEditPrenom->setText(prenom);
    ui->comboBoxPrio->setCurrentIndex(prio-1);
    ui->lineEditTel->setText(QString::number(tel));
    ui->lineEditVille->setText(ville);
    ui->lineEdit->setText(adresse);
}

void ModifiersupprimerclientDialog::on_pushButtonAnnuler_clicked()
{
    accept();
}

void ModifiersupprimerclientDialog::on_pushButtonModifier_clicked()
{
    QString dateRdv = ui->dateEditRdv->text();
    int duree = ui->lineEditDureeRdv->text().toInt();
    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    int cP = ui->lineEditCP->text().toInt();
    QString ville = ui->lineEditVille->text();
    int tel = ui->lineEditTel->text().toInt();
    int prio = ui->comboBoxPrio->currentIndex()+1;
    QString adresse = ui ->lineEdit->text();
    QString commentaire = ui->lineEditCommentaire->text();


    int id = ui ->labeliD->text().toInt();
    if ( nom.isEmpty()||prenom.isEmpty()||(adresse.isEmpty())||(ville.isEmpty())||(ui->lineEditCP->text().isEmpty())||(ui->lineEditDureeRdv->text().isEmpty())||dateRdv.isEmpty() )
    {
        QMessageBox::warning(this,tr("Warning"),tr("C'est oligatoire de remplir nom, prenom, adresse, ville,code Postale,dureeRDV,dateRDV et Priorite! "),QMessageBox::Yes);
    }else{
        QDate current_date = QDate::currentDate();
        QDate dateTemp=QDate::fromString(dateRdv, "yyyy/MM/dd");
        if(dateTemp<=current_date){
            QMessageBox::warning(this,tr("Warning"),tr("date peut pas etre un jour anterieur"),QMessageBox::Yes);
            ui->dateEditRdv->clear();
        }else{
            TClientDAO cDAO;
            cDAO.modifierC(id,nom,prenom,ville,cP,dateRdv,tel,prio,adresse,commentaire,duree);
            QMessageBox::warning(this,tr("Warning"),tr("Modification reussit ! "),QMessageBox::Yes);
            accept();
        }
    }
}



void ModifiersupprimerclientDialog::on_pushButtonSupprimer_clicked()
{
    TClientDAO cDAO;
    QString id = ui->labeliD->text();
    qDebug()<<id;
    cDAO.supprimerC(id);
    accept();
}

void ModifiersupprimerclientDialog::on_lineEditNom_textChanged(const QString &arg1)
{
    QString nom= ui->lineEditNom->text();
    if(nom!=NULL)    {QString cNom;
        cNom.append( nom.at(0).toUpper());
        for(int i=1;i<nom.size();i++)        {cNom.append(nom.at(i).toLower());
        }ui->lineEditNom->setText(cNom);
    }
}

void ModifiersupprimerclientDialog::on_lineEditPrenom_textChanged(const QString &arg1)
{
    QString prenom= ui->lineEditPrenom->text();
    if(prenom!=NULL)    {QString cpNom;
        cpNom.append( prenom.at(0).toUpper());
        for(int i=1;i<prenom.size();i++)        {cpNom.append(prenom.at(i).toLower());
        }ui->lineEditPrenom->setText(cpNom);
    }
}

void ModifiersupprimerclientDialog::on_lineEditVille_textChanged(const QString &arg1)
{
    QString ville= ui->lineEditVille->text();
    if(ville!=NULL)    {QString cville;
        cville.append( ville.at(0).toUpper());
        for(int i=1;i<ville.size();i++)        {cville.append(ville.at(i).toLower());
        }ui->lineEditVille->setText(cville);
    }
}
