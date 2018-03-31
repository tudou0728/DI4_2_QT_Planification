#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QApplication>
#include "dialogproposinfo.h"
#include "widgetinfo.h"

#include "ajouterpersonneldialog.h"
#include "c_init_bd.h"
#include "gererbd.h"
#include <QMessageBox>
#include "tclientdao.h"
#include "tressourcedao.h"
#include "ressourceControleur.h"
#include <QTreeWidgetItem>
#include "modifieretsupprimerdialog.h"
#include "clientcontroleur.h"
#include "planification.h"
#include <vector>
#include <QFileDialog>
#include "ajoutercdialog.h"

#include "modifiersupprimerclientdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuitter_triggered();

    void on_actionA_Propos_triggered();

    void on_actionClient_triggered();

    void on_actionPersonnel_triggered();

    void on_selectCPushButton_clicked();

    void on_reloadPushButton_clicked();

    void on_personnelTreeView_doubleClicked(const QModelIndex &index);

    void on_planifierPushButton_clicked();

    void on_enregistrerPushButton_clicked();

    void on_clientTableView_doubleClicked(const QModelIndex &index);

    void on_actionAssureur_Vie_triggered();

private:
    Ui::MainWindow *ui;
    TRessourceDAO tRessourceDAO;
    TClientDAO tClientDAO;
    RessourceControleur ressourceControleur;
    ModifierEtSupprimerDialog *modifierEtSupprimerDialog;
    ClientControleur clientControleur;
    Planification planification;
    TRdvDAO tRdvDAO;
};

#endif // MAINWINDOW_H
