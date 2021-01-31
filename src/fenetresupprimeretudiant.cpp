#include "fenetresupprimeretudiant.h"
#include "ui_fenetresupprimeretudiant.h"

FenetreSupprimerEtudiant::FenetreSupprimerEtudiant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreSupprimerEtudiant)
{
    ui->setupUi(this);

    proposerEtudiant();


    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeEtudiant()));
    timer->start(500);

    connect(ui->boutonSupprimerEtudiant, SIGNAL(clicked()), this, SLOT(supprimerEtudiant()));
    connect(ui->comboBoxMatriculeEtudiant, SIGNAL(currentIndexChanged(int)), this, SLOT(afficherInfoEtudiant(int)));

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonSupprimerEtudiant, SIGNAL(pressed()), this, SLOT(enfoncerBoutonSupprimerEtudiant()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonSupprimerEtudiant, SIGNAL(released()), this, SLOT(relacherBoutonSupprimerEtudiant()));

}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreSupprimerEtudiant::enfoncerBoutonSupprimerEtudiant(){
    ui->boutonSupprimerEtudiant->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreSupprimerEtudiant::relacherBoutonSupprimerEtudiant(){
    ui->boutonSupprimerEtudiant->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonSupprimerEtudiant->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

void FenetreSupprimerEtudiant::proposerEtudiant()
{
    ui->comboBoxMatriculeEtudiant->addItem("---");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT matricule FROM etudiant");
    requete.exec();

    while (requete.next()) {
        ui->comboBoxMatriculeEtudiant->addItem(requete.value("matricule").toString());
    }

    deconnecterBaseDeDonnee();
}


void FenetreSupprimerEtudiant::actualiserListeEtudiant()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT COUNT(matricule) as nbr FROM etudiant");
    requete.exec();
    requete.next();

    if(requete.value("nbr").toInt() > ui->comboBoxMatriculeEtudiant->count()-1)
    {
        while (ui->comboBoxMatriculeEtudiant->count() > 0) {
            ui->comboBoxMatriculeEtudiant->removeItem(ui->comboBoxMatriculeEtudiant->currentIndex());
        }

        ui->comboBoxMatriculeEtudiant->addItem("---");

        requete.prepare("SELECT matricule FROM etudiant");
        requete.exec();

        while (requete.next()) {
            ui->comboBoxMatriculeEtudiant->addItem(requete.value("matricule").toString());
        }
    }

    deconnecterBaseDeDonnee();
}

void FenetreSupprimerEtudiant::supprimerEtudiant()
{
    if (ui->comboBoxMatriculeEtudiant->currentIndex() != 0)
    {
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("DELETE FROM etudiant WHERE matricule = :matricule ");

        requete.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText());

        requete.exec();

        deconnecterBaseDeDonnee();

        ui->comboBoxMatriculeEtudiant->removeItem(ui->comboBoxMatriculeEtudiant->currentIndex());
    }
}

void FenetreSupprimerEtudiant::afficherInfoEtudiant(int i)
{
    if(i >= 1) {
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("SELECT nom, prenom, date_naissance FROM etudiant WHERE matricule = :matricule ");

        requete.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->itemText(i));

        requete.exec();

        requete.next();

        ui->labelProfilEtudiant->setText("Matricule : "+ui->comboBoxMatriculeEtudiant->itemText(i)+"\n\nNom : "+
                                         requete.value("nom").toString()+"\n\nPrenom : "+
                                         requete.value("prenom").toString()+"\n\nDate de Naissance :"+
                                         requete.value("date_naissance").toString());

        deconnecterBaseDeDonnee();
    }
    else {
        ui->labelProfilEtudiant->setText("");
    }
}


FenetreSupprimerEtudiant::~FenetreSupprimerEtudiant()
{
    delete ui;
}
