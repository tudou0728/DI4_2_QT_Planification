#ifndef AJOUTERCDIALOG_H
#define AJOUTERCDIALOG_H

#include <QDialog>

namespace Ui {
class AjouterCDialog;
}

class AjouterCDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterCDialog(QWidget *parent = 0);
    ~AjouterCDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_ButtonAjouter_clicked();

    void on_lineEditNom_textChanged(const QString &arg1);

    void on_lineEditPrenom_textChanged(const QString &arg1);

    void on_lineEditVille_textChanged(const QString &arg1);

    void on_XMLButton_clicked();

private:
    Ui::AjouterCDialog *ui;
};

#endif // AJOUTERCDIALOG_H
