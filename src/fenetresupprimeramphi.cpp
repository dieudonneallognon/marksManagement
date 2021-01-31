#include "fenetresupprimeramphi.h"
#include "ui_fenetresupprimeramphi.h"

FenetreSupprimerAmphi::FenetreSupprimerAmphi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreSupprimerAmphi)
{
    ui->setupUi(this);

    proposerAmphi();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeAmphi()));
    timer->start(500);

    connect(ui->boutonSupprimerAmphi, SIGNAL(clicked()), this, SLOT(supprimerAmphi()));
    connect(ui->comboBoxNomAmphi, SIGNAL(currentIndexChanged(int)), this, SLOT(AfficherInfoAmphi(int)));



    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonSupprimerAmphi, SIGNAL(pressed()), this, SLOT(enfoncerBoutonSupprimerAmphi()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonSupprimerAmphi, SIGNAL(released()), this, SLOT(relacherBoutonSupprimerAmphi()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreSupprimerAmphi::enfoncerBoutonSupprimerAmphi(){
    ui->boutonSupprimerAmphi->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreSupprimerAmphi::relacherBoutonSupprimerAmphi(){
    ui->boutonSupprimerAmphi->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonSupprimerAmphi->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

/*----------------------------------------Supprimer Amphi------------------------------------*/

void FenetreSupprimerAmphi::supprimerAmphi()
{
    if (ui->comboBoxNomAmphi->currentIndex() != 0)
    {
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("DELETE FROM amphi WHERE nom_amphi = :nom_amphi ");

        requete.bindValue(":nom_amphi", ui->comboBoxNomAmphi->currentText());

        requete.exec();

        deconnecterBaseDeDonnee();

        ui->comboBoxNomAmphi->removeItem(ui->comboBoxNomAmphi->currentIndex());
    }
}
/*----------------------------------------Afficher Info Amphi------------------------------------*/

void FenetreSupprimerAmphi::AfficherInfoAmphi(int i)
{
    if(i >= 1) {
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("SELECT nb_place FROM amphi WHERE nom_amphi = :nom_amphi ");

        requete.bindValue(":nom_amphi", ui->comboBoxNomAmphi->itemText(i));

        requete.exec();

        requete.next();

        ui->labelCaracteristiquesAmphi->setText(ui->comboBoxNomAmphi->itemText(i)+"\n\nNombre de place : "+
                                                requete.value("nb_place").toString());

        deconnecterBaseDeDonnee();
    }
    else {
        ui->labelCaracteristiquesAmphi->setText("");
    }
}

void FenetreSupprimerAmphi::actualiserListeAmphi()
{

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT COUNT(nom_amphi) as nbr FROM amphi");
    requete.exec();
    requete.next();

    if(requete.value("nbr").toInt() > ui->comboBoxNomAmphi->count()-1)
    {
        while (ui->comboBoxNomAmphi->count() > 0) {
            ui->comboBoxNomAmphi->removeItem(ui->comboBoxNomAmphi->currentIndex());
        }

        ui->comboBoxNomAmphi->addItem("---");

        requete.prepare("SELECT nom_amphi FROM amphi");
        requete.exec();

        while (requete.next()) {
            ui->comboBoxNomAmphi->addItem(requete.value("nom_amphi").toString());
        }
    }

    deconnecterBaseDeDonnee();
}

void FenetreSupprimerAmphi::proposerAmphi()
{
    ui->comboBoxNomAmphi->addItem("---");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT nom_amphi FROM amphi");
    requete.exec();

    while (requete.next()) {
        ui->comboBoxNomAmphi->addItem(requete.value("nom_amphi").toString());
    }

    deconnecterBaseDeDonnee();
}

FenetreSupprimerAmphi::~FenetreSupprimerAmphi()
{
    delete ui;
}
