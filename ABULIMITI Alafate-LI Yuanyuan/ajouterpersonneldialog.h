#ifndef AJOUTERPERSONNELDIALOG_H
#define AJOUTERPERSONNELDIALOG_H

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
class AjouterPersonnelDialog;
}

class AjouterPersonnelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterPersonnelDialog(QWidget *parent = 0);
    ~AjouterPersonnelDialog();

private slots:
    void on_ajouterButton_clicked();

    void on_nomLineEdit_textChanged(const QString &arg1);

    void on_prenomLineEdit_textChanged(const QString &arg1);

private:
    Ui::AjouterPersonnelDialog *ui;
    TTypeDAO tTypeDAO;
};

#endif // AJOUTERPERSONNELDIALOG_H
