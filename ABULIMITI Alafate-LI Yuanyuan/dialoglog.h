#ifndef DIALOGLOG_H
#define DIALOGLOG_H

#include <QDialog>
#include <QMessageBox>
#include "tcomptedao.h"

namespace Ui {
class DialogLog;
}

class DialogLog : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLog(QWidget *parent = 0);
    ~DialogLog();

private slots:
    void on_connecterButton_clicked();

private:
    Ui::DialogLog *ui;
    TcompteDAO tcompteDAO;
};

#endif // DIALOGLOG_H
