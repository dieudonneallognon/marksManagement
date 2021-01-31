#include "fenetresupprimermatiere.h"
#include "ui_fenetresupprimermatiere.h"

#include <QMessageBox>

FenetreSupprimerMatiere::FenetreSupprimerMatiere(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreSupprimerMatiere)
{
    ui->setupUi(this);

    ui->comboBoxNomMatiere->addItem("---");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT nom_mat FROM matiere");
    requete.exec();

    while (requete.next()) {
        ui->comboBoxNomMatiere->addItem(requete.value("nom_mat").toString());
    }

    deconnecterBaseDeDonnee();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeMatiere()));
    timer->start(500);


    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonSupprimerMatiere, SIGNAL(pressed()), this, SLOT(enfoncerBoutonSupprimerMatiere()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonSupprimerMatiere, SIGNAL(released()), this, SLOT(relacherBoutonSupprimerMatiere()));

    connect(ui->boutonSupprimerMatiere, SIGNAL(clicked()), this, SLOT(supprimerMatiere()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreSupprimerMatiere::enfoncerBoutonSupprimerMatiere(){
    ui->boutonSupprimerMatiere->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreSupprimerMatiere::relacherBoutonSupprimerMatiere(){
    ui->boutonSupprimerMatiere->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonSupprimerMatiere->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

void FenetreSupprimerMatiere::supprimerMatiere()
{
    if (ui->comboBoxNomMatiere->currentIndex() != 0)
    {
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("DELETE FROM matiere WHERE nom_mat = :nom_mat ");

        requete.bindValue(":nom_mat", ui->comboBoxNomMatiere->currentText());

        requete.exec();

        deconnecterBaseDeDonnee();

        ui->comboBoxNomMatiere->removeItem(ui->comboBoxNomMatiere->currentIndex());
    }
}

void FenetreSupprimerMatiere::actualiserListeMatiere()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT COUNT(nom_mat) as nbr FROM matiere");
    requete.exec();
    requete.next();

    if(requete.value("nbr").toInt() > ui->comboBoxNomMatiere->count()-1)
    {
        while (ui->comboBoxNomMatiere->count() > 0) {
            ui->comboBoxNomMatiere->removeItem(ui->comboBoxNomMatiere->currentIndex());
        }

        ui->comboBoxNomMatiere->addItem("---");

        requete.prepare("SELECT nom_mat FROM matiere");
        requete.exec();

        while (requete.next()) {
            ui->comboBoxNomMatiere->addItem(requete.value("nom_mat").toString());
        }
    }

    deconnecterBaseDeDonnee();
}

FenetreSupprimerMatiere::~FenetreSupprimerMatiere()
{
    delete ui;
}
