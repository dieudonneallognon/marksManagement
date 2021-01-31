#-------------------------------------------------
#
# Project created by QtCreator 2019-04-26T17:06:44
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GestionNotes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        fenetreprincipale.cpp \
    fenetrecreationsuperadministrateur.cpp \
        authentification.cpp \
    fenetreajouteramphi.cpp \
    fenetresupprimeramphi.cpp \
    fenetrevoirlisteetudiant.cpp \
    fenetreajoutermatiere.cpp \
    fenetresupprimermatiere.cpp \
    fenetreajouteretudiant.cpp \
    fenetresupprimeretudiant.cpp \
    fenetresupprimermembreadministration.cpp \
    fenetrelistemembreadministration.cpp \
    fenetreajoutermembreadministration.cpp \
    fenetremonprofil.cpp \
    basededonnee.cpp \
    fenetrevoirnoteetudiant.cpp \
    fenetremodifiernote.cpp

HEADERS += \
        fenetreprincipale.h \
    fenetrecreationsuperadministrateur.h \
    authentification.h \
    fenetreajouteramphi.h \
    fenetresupprimeramphi.h \
    fenetrevoirlisteetudiant.h \
    fenetreajoutermatiere.h \
    fenetresupprimermatiere.h \
    fenetreajouteretudiant.h \
    fenetresupprimeretudiant.h \
    fenetresupprimermembreadministration.h \
    fenetrelistemembreadministration.h \
    fenetreajoutermembreadministration.h \
    fenetremonprofil.h \
    basededonnee.h \
    fenetrevoirnoteetudiant.h \
    fenetremodifiernote.h

FORMS += \
        fenetreprincipale.ui \
    fenetrecreationsuperadministrateur.ui \
    authentification.ui \
    fenetreajouteramphi.ui \
    fenetresupprimeramphi.ui \
    fenetrevoirlisteetudiant.ui \
    fenetreajoutermatiere.ui \
    fenetresupprimermatiere.ui \
    fenetreajouteretudiant.ui \
    fenetresupprimeretudiant.ui \
    fenetresupprimermembreadministration.ui \
    fenetrelistemembreadministration.ui \
    fenetreajoutermembreadministration.ui \
    fenetremonprofil.ui \
    fenetrevoirnoteetudiant.ui \
    fenetremodifiernote.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
