#include "ajouterpersonneldialog.h"
#include "ui_ajouterpersonneldialog.h"

AjouterPersonnelDialog::AjouterPersonnelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterPersonnelDialog)
{
    ui->setupUi(this);
    QStringList listType=tTypeDAO.inverseToString(tTypeDAO.rechercherAlltype());
    for(int i=0;i<listType.size();i++)
    {
        ui->typeComboBox->addItem(listType.at(i));
    }
}

AjouterPersonnelDialog::~AjouterPersonnelDialog()
{
    delete ui;
}

void AjouterPersonnelDialog::on_ajouterButton_clicked()
{
    QString nom= ui->nomLineEdit->text();
    QString prenom= ui->prenomLineEdit->text();
    QString label= ui->typeComboBox->currentText();
    if(nom==NULL || prenom==NULL)
    {
        QMessageBox::warning(this,tr("Warning"),tr("les trois saisies sont obligatoires de remplir ! "),QMessageBox::Yes);
    }
    else
    {
        TRessourceDAO tressourceDAO;
        QSqlQuery query=tTypeDAO.rechercherLabel(label);
        query.next();
        if(tressourceDAO.ajouterRessource(nom,prenom,query.value(0).toString()))
        {
            QMessageBox::warning(this,tr("Reussir"),tr("ajouter une personnel reussir,vous pouvez continuer dajouter unre ressource ! "),QMessageBox::Yes);
            ui->nomLineEdit->clear();
            ui->prenomLineEdit->clear();;
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("ajouter une personnel error ! "),QMessageBox::Yes);
        }
    }
}

void AjouterPersonnelDialog::on_nomLineEdit_textChanged(const QString &arg1)
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

void AjouterPersonnelDialog::on_prenomLineEdit_textChanged(const QString &arg1)
{

    QString prenom= ui->prenomLineEdit->text();
    if(prenom!=NULL)
    {
        QString stPrenom;
        stPrenom.append( prenom.at(0).toUpper());
        for(int i=1;i<prenom.size();i++)
        {
            stPrenom.append(prenom.at(i).toLower());
        }
        ui->prenomLineEdit->setText(stPrenom);
    }

}
