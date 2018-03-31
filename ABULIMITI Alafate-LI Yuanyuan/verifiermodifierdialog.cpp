#include "verifiermodifierdialog.h"
#include "ui_verifiermodifierdialog.h"

VerifierModifierDialog::VerifierModifierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerifierModifierDialog)
{
    ui->setupUi(this);
}

VerifierModifierDialog::~VerifierModifierDialog()
{
    delete ui;
}
