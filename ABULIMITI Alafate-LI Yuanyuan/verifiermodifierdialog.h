#ifndef VERIFIERMODIFIERDIALOG_H
#define VERIFIERMODIFIERDIALOG_H

#include <QDialog>

namespace Ui {
class verifierModifierDialog;
}

class verifierModifierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit verifierModifierDialog(QWidget *parent = 0);
    ~verifierModifierDialog();

private:
    Ui::verifierModifierDialog *ui;
};

#endif // VERIFIERMODIFIERDIALOG_H
