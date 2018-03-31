#ifndef ASSUREURDIALOG_H
#define ASSUREURDIALOG_H

#include <QDialog>

namespace Ui {
class AssureurDialog;
}

class AssureurDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssureurDialog(QWidget *parent = 0);
    ~AssureurDialog();

private slots:
    void on_Annuler_clicked();

    void on_pushButtonAjouter_clicked();

private:
    Ui::AssureurDialog *ui;
};

#endif // ASSUREURDIALOG_H
