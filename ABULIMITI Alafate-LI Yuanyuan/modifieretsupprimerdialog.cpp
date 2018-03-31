#include "modifieretsupprimerdialog.h"
#include "ui_modifieretsupprimerdialog.h"

ModifierEtSupprimerDialog::ModifierEtSupprimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifierEtSupprimerDialog)
{
    ui->setupUi(this);
}

ModifierEtSupprimerDialog::~ModifierEtSupprimerDialog()
{
    delete ui;
}
void ModifierEtSupprimerDialog::receiveData(QString ressourceId)
{
    qDebug() << ressourceId;
    ui->idAfficherLabel->setText(ressourceId);
    QSqlQuery query=tRessourceDAO.rechercherIdR(ressourceId);
    if(query.next())
    {
        ui->nomLineEdit->setText(query.value(1).toString());
        ui->prenomLlineEdit->setText(query.value(2).toString());
        QStringList listType=tTypeDAO.inverseToString(tTypeDAO.rechercherAlltype());
        int index=listType.lastIndexOf(query.value(5).toString());
        for(int i=0;i<listType.size();i++)
        {
            ui->typeComboBox->addItem(listType.at(i));
        }
        ui->typeComboBox->setCurrentIndex(index);
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("Error ! "),QMessageBox::Yes);
    }
}



void ModifierEtSupprimerDialog::on_modifierPushButton_clicked()
{
    QString id=ui->idAfficherLabel->text();
    QString nom=ui->nomLineEdit->text();
    QString prenom=ui->prenomLlineEdit->text();
    if(nom==NULL || prenom==NULL)
    {
        QMessageBox::warning(this,tr("Warning"),tr("les trois saisies sont obligatoires de remplir ! "),QMessageBox::Yes);
    }
    else
    {
        QString type=ui->typeComboBox->currentText();
        int verifier=QMessageBox::question(NULL, "Verifier", "Modifier cette ressource ?", QMessageBox::Yes, QMessageBox::No);
        if(QMessageBox::Yes==verifier)
        {
            QSqlQuery query=tTypeDAO.rechercherLabel(type);
            if(query.next())
            {
                QString idT=query.value(0).toString();
                bool resultat=tRessourceDAO.modifier(id,nom,prenom,idT);
                if(resultat)
                {
                    QMessageBox::warning(this,tr("Modifier"),"Modifier la ressource "+ nom +" reussir!",QMessageBox::Yes);
                    accept();
                }
                else
                {
                    QMessageBox::warning(this,tr("Modifier"),tr("Error ! "),QMessageBox::Yes);
                }
            }
            else
            {
                QMessageBox::warning(this,tr("Modifier"),tr("ne peut pas modifier ! "),QMessageBox::Yes);
            }
        }
        if(QMessageBox::No==verifier)
        {
            QMessageBox::warning(this,tr("Modifier"),"La ressource: " + nom +" change rien.",QMessageBox::Yes);
            accept();
        }
    }
}

void ModifierEtSupprimerDialog::on_supprimerPushButton_clicked()
{
    QString idR=ui->idAfficherLabel->text();
    QSqlQuery query=tRessourceDAO.rechercherIdR(idR);
    if(query.next())
    {
        QString nomR=query.value(1).toString();
        int verifier=QMessageBox::question(NULL, "Verifier", "Supprimer cette ressource ?", QMessageBox::Yes, QMessageBox::No);
        if(QMessageBox::Yes==verifier)
        {
            if(tRessourceDAO.supprimer(idR))
            {
                QMessageBox::warning(this,tr("Supprimer"),"Supprimer la ressource: "+ nomR +" reussir!",QMessageBox::Yes);
                accept();
            }
            else
            {
                QMessageBox::warning(this,tr("Supprimer"),tr("Error ! "),QMessageBox::Yes);
            }
        }
        if(QMessageBox::No==verifier)
        {
            QMessageBox::warning(this,tr("Supprimer"),"La ressource: " + nomR +" change rien.",QMessageBox::Yes);
            accept();
        }
    }

}

void ModifierEtSupprimerDialog::on_annulerPushButton_clicked()
{
    accept();
}

void ModifierEtSupprimerDialog::on_nomLineEdit_textChanged(const QString &arg1)
{

    QString nom= ui->nomLineEdit->text();
    if(nom!=NULL)
    {
        QString strNom;
        strNom.append( nom.at(0).toUpper());
        for(int i=1;i<nom.size();i++)
        {
            strNom.append(nom.at(i).toLower());
        }
        ui->nomLineEdit->setText(strNom);
    }

}

void ModifierEtSupprimerDialog::on_prenomLlineEdit_textChanged(const QString &arg1)
{
    QString prenom= ui->prenomLlineEdit->text();
    if(prenom!=NULL)
    {
        QString strPrenom;
        strPrenom.append( prenom.at(0).toUpper());
        for(int i=1;i<prenom.size();i++)
        {
            strPrenom.append(prenom.at(i).toLower());
        }
        ui->prenomLlineEdit->setText(strPrenom);
    }
}
