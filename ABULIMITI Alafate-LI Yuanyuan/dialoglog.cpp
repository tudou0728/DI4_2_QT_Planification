#include "dialoglog.h"
#include "ui_dialoglog.h"
#include<QString>
#include "tcomptedao.h"

DialogLog::DialogLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLog)
{
    ui->setupUi(this);
    ui->usernameEdit->setText("val");

}

DialogLog::~DialogLog()
{
    delete ui;
}

void DialogLog::on_connecterButton_clicked()
{
   QString username=ui->usernameEdit->text();
   QString password=ui->passwordEdit->text();
    if(this->tcompteDAO.verifierLogin(username,password))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("Login ou Mot depasse incorrecte ! "),QMessageBox::Yes);
        ui->passwordEdit->clear();
    }

}
