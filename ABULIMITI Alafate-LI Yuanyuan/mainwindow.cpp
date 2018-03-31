#include "mainwindow.h"
#include "assureurdialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(tr("Vous venez de vous connecter."));
    ui->personnelTreeView->setEditTriggers(0);
    ui->clientTableView->setEditTriggers(0);
    ui->planificationTableView->setEditTriggers(0);
    ui->personnelTreeView->setModel(this->ressourceControleur.setModel());

}

MainWindow::~MainWindow()
{
    delete ui;
    GererBD::fermer();
}

void MainWindow::on_actionQuitter_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionA_Propos_triggered()
{
    DialogProposInfo dialogProposInfo;
    dialogProposInfo.exec();
    ui->statusBar->showMessage(tr("Projet info affichier."));
}

void MainWindow::on_actionClient_triggered()
{

    AjouterCDialog ajouterCDialog;
    ajouterCDialog.exec();
    ui->statusBar->showMessage(tr("Client ajouté. "));
}

void MainWindow::on_actionPersonnel_triggered()
{

    AjouterPersonnelDialog ajouterPersonnelDialog;
    ajouterPersonnelDialog.exec();
    ui->statusBar->showMessage(tr("Personne ajouté. "));
}

void MainWindow::on_selectCPushButton_clicked()
{
    if(ui->nomCLineEdit->text().isEmpty() && ui->prenomCLineEdit->text().isEmpty() &&
            ui->idLineEdit->text().isEmpty() && ((!ui->dateCheckBox->isChecked()) || ui->dateEdit->text().isEmpty()))
    {
        QMessageBox::warning(this,tr("Warning"),tr("Au moins un de ces quatre champs doit être remplis ! "),QMessageBox::Yes);

    }
    else  if(!ui->dateCheckBox->isChecked())
    {
        QString nom=ui->nomCLineEdit->text();
        QString prenom=ui->prenomCLineEdit->text();
        QString id=ui->idLineEdit->text();
        ui->clientTableView->setModel(clientControleur.setModelNonDate(nom,prenom,id));
    }
    else
    {
        QString nom=ui->nomCLineEdit->text();
        QString prenom=ui->prenomCLineEdit->text();
        QString id=ui->idLineEdit->text();
        QString dateD=ui->dateEdit->text();
        QString dateF=ui->dateEdit_2->text();
        QString dateD1=dateD.replace(QRegExp("\\/"),"-");
        QString dateF1=dateF.replace(QRegExp("\\/"),"-");
        ui->clientTableView->setModel(clientControleur.setModelParDate(nom,prenom,id,dateD1,dateF1));
    }
    ui->statusBar->showMessage(tr("Recherche de clients . "));
}

void MainWindow::on_reloadPushButton_clicked()
{
    ui->personnelTreeView->setModel(this->ressourceControleur.setModel());
    ui->statusBar->showMessage(tr("Ressources recharger."));
}

void MainWindow::on_personnelTreeView_doubleClicked(const QModelIndex &index)
{
    if(index.parent().parent().isValid())
    {
        QString ressourceNom=index.data().toString();
        QString ressourceLabel= index.parent().data().toString();
        QSqlQuery query=tRessourceDAO.rechercherNomEtLabel(ressourceNom,ressourceLabel);
        if(query.next())
        {
            QString id=query.value(0).toString();
            modifierEtSupprimerDialog=new ModifierEtSupprimerDialog();
            modifierEtSupprimerDialog->receiveData(id);
            modifierEtSupprimerDialog->exec();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("Charge en cours..., essayer d'autre fois , SVP! "),QMessageBox::Yes);
            qDebug() <<"fails";
        }
    }
    ui->personnelTreeView->setModel(this->ressourceControleur.setModel());
    ui->statusBar->showMessage(tr("Modifier ou supprimer une ressource."));
}

void MainWindow::on_planifierPushButton_clicked()
{
    QString date=ui->planifierDateEdit->text();
    QString datePlanifier=date.replace(QRegExp("\\/"),"-");
    QSqlQuery query=tRdvDAO.rechercherParDate(datePlanifier);
    if(query.next())
    {
        Planification planification;
        QSqlQuery query1=tRdvDAO.rechercherParDate(datePlanifier);
        vector<TClient> v1=planification.getRdv(query1);
        vector<TClient> v2=planification.trierPriorite(v1);
        vector<PlanDeRessource> v3=planification.planifier(v2);
        ui->planificationTableView->setModel(this->planification.setModelPlanification(v3));
    }
    else
    {
        QMessageBox::warning(this,tr("Nofitication"),tr("Pass de RDV. "),QMessageBox::Yes);
    }
    ui->statusBar->showMessage(tr("Planification."));
}

void MainWindow::on_enregistrerPushButton_clicked()
{
    QString date=ui->planifierDateEdit->text();
    QString datePlanifier=date.replace(QRegExp("\\/"),"-");
    QSqlQuery query=tRdvDAO.rechercherParDate(datePlanifier);
    if(query.next())
    {
        Planification planification;
        QSqlQuery query1=tRdvDAO.rechercherParDate(datePlanifier);
        vector<TClient> v1=planification.getRdv(query1);
        vector<TClient> v2=planification.trierPriorite(v1);
        vector<PlanDeRessource> v3=planification.planifier(v2);
        QString fileNom=QFileDialog::getSaveFileName(this,"Save as...","plan",tr("Config Files (*.txt)"));
        QString resultat=planification.enregistrerFile(v3,fileNom);
        if(resultat.compare("Enregistrer error!")==0)
        {
            QMessageBox::warning(this,tr("Warning"),tr("Enregistrer file error! "),QMessageBox::Yes);
        }
        else
        {
            QMessageBox::warning(this,tr("Notification"),"Enregistrer reussir! le chemin de file est: " + fileNom,QMessageBox::Yes);
        }
    }
    else
    {
        QMessageBox::warning(this,tr("Nofitication"),tr("Pass de RDV. "),QMessageBox::Yes);
    }
    ui->statusBar->showMessage(tr("Planification."));
}

void MainWindow::on_clientTableView_doubleClicked(const QModelIndex &index)
{
    ModifiersupprimerclientDialog mscDialog ;

    int row= ui->clientTableView->currentIndex().row();

    QAbstractItemModel *model = ui->clientTableView->model ();

    int id=model->data(model->index(row,0)).toInt();
    QSqlQuery query=tClientDAO.rechercherClient(QString::number(id,10));
    query.next();
    QString nom=query.value(1).toString();
    QString prenom=query.value(2).toString();
    QString adresse=query.value(3).toString();
    QString ville=query.value(4).toString();
    int cp=query.value(5).toInt();
    QString commentaire=query.value(6).toString();
    int tel=query.value(7).toInt();
    QString date=query.value(8).toString();
    qDebug()<<date;
    int duree =query.value(9).toInt();
    int prio = query.value(10).toInt();

    mscDialog.receiveData( id, nom, prenom,
                           adresse, ville, cp, commentaire, tel,
                           date,  duree, prio);
    mscDialog.exec();
}

void MainWindow::on_actionAssureur_Vie_triggered()
{
    AssureurDialog assureur;
    assureur.exec();
}
