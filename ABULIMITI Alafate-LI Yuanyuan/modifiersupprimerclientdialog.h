#ifndef MODIFIERSUPPRIMERCLIENTDIALOG_H
#define MODIFIERSUPPRIMERCLIENTDIALOG_H

#include <QDialog>
#include "tclient.h"
using namespace std;


namespace Ui {
class ModifiersupprimerclientDialog;
}

class ModifiersupprimerclientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifiersupprimerclientDialog(QWidget *parent = 0);
    ~ModifiersupprimerclientDialog();
    void receiveData(int id, QString nom,QString prenom,
                     QString adresse,QString ville,int cp,QString commentaire,int tel ,
                     QString date, int duree,int prio);

private slots:
    void on_pushButtonAnnuler_clicked();

    void on_pushButtonModifier_clicked();

    void on_pushButtonSupprimer_clicked();



    void on_lineEditNom_textChanged(const QString &arg1);

    void on_lineEditPrenom_textChanged(const QString &arg1);

    void on_lineEditVille_textChanged(const QString &arg1);

private:
    Ui::ModifiersupprimerclientDialog *ui;
};

#endif // MODIFIERSUPPRIMERCLIENTDIALOG_H
