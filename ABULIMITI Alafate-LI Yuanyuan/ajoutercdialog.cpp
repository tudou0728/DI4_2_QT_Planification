#include "ajoutercdialog.h"
#include "ui_ajoutercdialog.h"
#include "tclient.h"
#include "tclientdao.h"
#include <QMessageBox>
#include "tressourcedao.h"

AjouterCDialog::AjouterCDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterCDialog)
{
    ui->setupUi(this);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEditTel );
    ui->lineEditTel->setValidator(validator);
    ui->lineEditCP->setValidator(validator);
    ui->lineEditDuree->setValidator(validator);

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    TRessourceDAO reDAO;
    reDAO.lireRe();
    vector<TRessource> reVector=reDAO.getRessourceVecteur();
    vector<TRessource>::iterator it_re;
    for(it_re = reVector.begin();it_re!=reVector.end();++it_re){
        ui->listWidget->addItem(QString::number(it_re->getId()));
    }

}

AjouterCDialog::~AjouterCDialog()
{
    delete ui;
}

void AjouterCDialog::on_pushButton_2_clicked()
{
    accept();
}

void AjouterCDialog::on_ButtonAjouter_clicked()
{
    TClient client;

    QString nom = ui->lineEditNom->text();
    QString prenom = ui->lineEditPrenom->text();
    QString adresse = ui->lineEditAdresse->text();
    QString ville = ui->lineEditVille->text();
    int cp = ui->lineEditCP->text().toInt();
    int duree = ui->lineEditDuree->text().toInt();
    if(duree<10)
    {
        QMessageBox::warning(this,tr("Warning"),tr("la duree faut >10 ."),QMessageBox::Yes);
    }
    else
    {
        QString date = ui->dateEdit->text();
        int prio = ui->comboBoxPrio->currentText().toInt();
        QString commentaire = ui->lineEditCom->text();
        int tel = ui->lineEditTel->text().toInt();
        if ( nom.isEmpty()||prenom.isEmpty()||(adresse.isEmpty())||(ville.isEmpty())||cp==NULL||duree==NULL||date.isEmpty() || ui->listWidget->selectedItems().isEmpty())
        {
            QMessageBox::warning(this,tr("Warning"),tr("C'est oligatoire de remplir nom, prenom, ressources, adresse, ville,code Postale,dureeRDV,dateRDV et Priorite! "),QMessageBox::Yes);

        }
        else
        {   QDate current_date = QDate::currentDate();
            QDate dateTemp=QDate::fromString(date, "yyyy/MM/dd");

            if(dateTemp<=current_date){
                QMessageBox::warning(this,tr("Warning"),tr("date peut pas etre un jour anterieur"),QMessageBox::Yes);
                ui->dateEdit->clear();
            }else{
                client.setNom(nom);
                client.setPrenom(prenom);
                client.setAdresse(adresse);
                client.setVille(ville);
                client.setCP(cp);
                client.setDureeRdv(duree);
                client.setDateRdv(date);
                client.setPriorite(prio);
                client.setCommentaire(commentaire);
                client.setTel(tel);

                vector<int> idRessourceVecteur;
                QList<QListWidgetItem*> list= ui->listWidget->selectedItems();

                foreach(QListWidgetItem * a,list)
                {
                    idRessourceVecteur.push_back(a->text().toInt());
                }
                client.setIdRessourcesVecteur(idRessourceVecteur);

                TClientDAO cDAO;
                if(!(cDAO.verifierC(client))){
                    cDAO.ajouterC(client);
                    QMessageBox::warning(this,tr("Warning"),tr("reussir! Vous pouvez continuer d'ajouter "),QMessageBox::Yes);

                    ui->lineEditNom->clear();
                    ui->lineEditPrenom->clear();
                    ui->lineEditAdresse->clear();
                    ui->lineEditCP->clear();
                    ui->lineEditDuree->clear();
                    ui->dateEdit->clear();
                    ui->comboBoxPrio->setCurrentIndex(0);
                    ui->lineEditCom->clear();
                    ui->lineEditTel->clear();
                    ui->lineEditVille->clear();
                }else{
                    QMessageBox::warning(this,tr("Warning"),tr("Ce client est deja exsite"),QMessageBox::Yes);
                    ui->lineEditNom->clear();
                    ui->lineEditPrenom->clear();
                    ui->lineEditAdresse->clear();
                    ui->lineEditCP->clear();
                    ui->lineEditDuree->clear();
                    ui->dateEdit->clear();
                    ui->comboBoxPrio->setCurrentIndex(0);
                    ui->lineEditCom->clear();
                    ui->lineEditTel->clear();
                    ui->lineEditVille->clear();
                }
            }
        }

    }


}

void AjouterCDialog::on_lineEditNom_textChanged(const QString &arg1)
{
    QString nom= ui->lineEditNom->text();
    if(nom!=NULL)    {QString cNom;
        cNom.append( nom.at(0).toUpper());
        for(int i=1;i<nom.size();i++)        {cNom.append(nom.at(i).toLower());
        }ui->lineEditNom->setText(cNom);
    }
}



void AjouterCDialog::on_lineEditPrenom_textChanged(const QString &arg1)
{
    QString prenom= ui->lineEditPrenom->text();
    if(prenom!=NULL)    {QString cpNom;
        cpNom.append( prenom.at(0).toUpper());
        for(int i=1;i<prenom.size();i++)        {cpNom.append(prenom.at(i).toLower());
        }ui->lineEditPrenom->setText(cpNom);
    }
}

void AjouterCDialog::on_lineEditVille_textChanged(const QString &arg1)
{
    QString ville= ui->lineEditVille->text();
    if(ville!=NULL)    {QString cville;
        cville.append( ville.at(0).toUpper());
        for(int i=1;i<ville.size();i++)        {cville.append(ville.at(i).toLower());
        }ui->lineEditVille->setText(cville);
    }
}

void AjouterCDialog::on_XMLButton_clicked()
{
    QMessageBox::warning(this,tr("Warning"),tr("Pas finit, mais il ya une methode pour ecrire un fichier XML"),QMessageBox::Yes);
}
