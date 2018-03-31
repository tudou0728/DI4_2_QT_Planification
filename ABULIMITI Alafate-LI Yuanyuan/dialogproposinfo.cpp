#include "dialogproposinfo.h"
#include "ui_dialogproposinfo.h"

DialogProposInfo::DialogProposInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProposInfo)
{
    ui->setupUi(this);
    QPixmap pix;
    pix.load(":/myImages/polytech.png");
    ui->polytechPhotoLabel->setPixmap(pix);

}

DialogProposInfo::~DialogProposInfo()
{
    delete ui;
}
