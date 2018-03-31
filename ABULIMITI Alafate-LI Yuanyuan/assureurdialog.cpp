#include "assureurdialog.h"
#include "ui_assureurdialog.h"
#include "tressourcedao.h"
#include "ttypedao.h"
 #include <QSqlQuery>

AssureurDialog::AssureurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssureurDialog)
{
    ui->setupUi(this);
}

AssureurDialog::~AssureurDialog()
{
    delete ui;
}

void AssureurDialog::on_Annuler_clicked()
{
    accept();
}

void AssureurDialog::on_pushButtonAjouter_clicked()
{
   QString nom = ui->lineEditNom->text();
   QString prenom = ui->lineEditPrenom->text();

   TRessourceDAO reDAO;
   TTypeDAO tDAO;
   QSqlQuery query = tDAO.rechercherLabel("Assureur Vie");
   if(query.next()){
       QString id = query.value(0).toString();
        reDAO.ajouterRessource(nom,prenom,id);
        accept();
  }
}
