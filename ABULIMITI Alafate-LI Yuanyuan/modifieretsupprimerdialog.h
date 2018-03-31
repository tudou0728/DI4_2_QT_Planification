#ifndef MODIFIERETSUPPRIMERDIALOG_H
#define MODIFIERETSUPPRIMERDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFile>
#include "tressourcedao.h"
#include "ttypedao.h"
#include <QMessageBox>

namespace Ui {
class ModifierEtSupprimerDialog;
}

class ModifierEtSupprimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierEtSupprimerDialog(QWidget *parent = 0);
    ~ModifierEtSupprimerDialog();
    void receiveData(QString ressourceId);

private slots:
    void on_modifierPushButton_clicked();

    void on_supprimerPushButton_clicked();

    void on_annulerPushButton_clicked();

    void on_nomLineEdit_textChanged(const QString &arg1);

    void on_prenomLlineEdit_textChanged(const QString &arg1);

private:
    Ui::ModifierEtSupprimerDialog *ui;
    TRessourceDAO tRessourceDAO;
    TTypeDAO tTypeDAO;

};

#endif // MODIFIERETSUPPRIMERDIALOG_H
