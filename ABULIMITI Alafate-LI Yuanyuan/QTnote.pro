#-------------------------------------------------
#
# Project created by QtCreator 2018-03-15T10:40:54
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTnote
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dialoglog.cpp \
    dialogproposinfo.cpp \
    widgetinfo.cpp \
    ajouterpersonneldialog.cpp \
    tcompte.cpp \
    tclient.cpp \
    trdv.cpp \
    tressource.cpp \
    ttype.cpp \
    tcomptedao.cpp \
    tclientdao.cpp \
    trdvdao.cpp \
    tressourcedao.cpp \
    ttypedao.cpp \
    c_init_bd.cpp \
    gererbd.cpp \
    ressourceControleur.cpp \
    modifieretsupprimerdialog.cpp \
    clientcontroleur.cpp \
    planification.cpp \
    planderessource.cpp \
    modifiersupprimerclientdialog.cpp \
    ajoutercdialog.cpp \
    assureurdialog.cpp

HEADERS  += mainwindow.h \
    dialoglog.h \
    dialogproposinfo.h \
    widgetinfo.h \
    ajouterpersonneldialog.h \
    tcompte.h \
    tclient.h \
    trdv.h \
    tressource.h \
    ttype.h \
    tcomptedao.h \
    tclientdao.h \
    trdvdao.h \
    tressourcedao.h \
    ttypedao.h \
    c_init_bd.h \
    gererbd.h \
    ressourceControleur.h \
    modifieretsupprimerdialog.h \
    clientcontroleur.h \
    planification.h \
    sortpriorite.h \
    planderessource.h \
    sortressource.h \
    modifiersupprimerclientdialog.h \
    ajoutercdialog.h \
    assureurdialog.h

FORMS    += mainwindow.ui \
    dialoglog.ui \
    dialogproposinfo.ui \
    widgetinfo.ui \
    ajouterpersonneldialog.ui \
    modifieretsupprimerdialog.ui \
    modifiersupprimerclientdialog.ui \
    ajoutercdialog.ui \
    assureurdialog.ui

RESOURCES += \
    images.qrc



