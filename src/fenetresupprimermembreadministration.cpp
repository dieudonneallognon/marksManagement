#include "fenetresupprimermembreadministration.h"
#include "ui_fenetresupprimermembreadministration.h"

FenetreSupprimerMembreAdministration::FenetreSupprimerMembreAdministration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreSupprimerMembreAdministration)
{
    ui->setupUi(this);

    fenetreAuthentification = new Authentification (this);
    fenetreAuthentification->hide();
    fenetreAuthentification->setTypeAuthentification(AUTHENTIFICATION_ESPACE_MEMBRE);

    proposerMembreAdministration();

    QTimer* timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeMembreAdministration()));
    timer->start(500);

    connect(ui->boutonSupprimerMembreAdministration, SIGNAL(clicked()), this, SLOT(supprimerMembreAdministration()));
    connect(ui->comboBoxIdMembreAdministration, SIGNAL(currentIndexChanged(int)), this, SLOT(afficherInfoMembreAdministration(int)));


    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonSupprimerMembreAdministration, SIGNAL(pressed()), this, SLOT(enfoncerBoutonSupprimerMembreAdministration()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonSupprimerMembreAdministration, SIGNAL(released()), this, SLOT(relacherBoutonSupprimerMembreAdministration()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreSupprimerMembreAdministration::enfoncerBoutonSupprimerMembreAdministration(){
    ui->boutonSupprimerMembreAdministration->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreSupprimerMembreAdministration::relacherBoutonSupprimerMembreAdministration(){
    ui->boutonSupprimerMembreAdministration->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonSupprimerMembreAdministration->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

void FenetreSupprimerMembreAdministration::afficherFenetreAuthentification(int f)
{
    if (f == 3)
        fenetreAuthentification->show();
}

FenetreSupprimerMembreAdministration::~FenetreSupprimerMembreAdministration()
{
    delete ui;
}

void FenetreSupprimerMembreAdministration::supprimerMembreAdministration()
{
    if (ui->comboBoxIdMembreAdministration->currentIndex() != 0)
    {
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("DELETE FROM mbreadministration WHERE id = :id ");

        requete.bindValue(":id", ui->comboBoxIdMembreAdministration->currentText());

        requete.exec();

        deconnecterBaseDeDonnee();

        ui->comboBoxIdMembreAdministration->removeItem(ui->comboBoxIdMembreAdministration->currentIndex());
    }
}

void FenetreSupprimerMembreAdministration::afficherInfoMembreAdministration(int i)
{
    if(i >= 1) {
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("SELECT nom, prenom FROM mbreadministration WHERE id = :id ");

        requete.bindValue(":id", ui->comboBoxIdMembreAdministration->itemText(i));

        requete.exec();

        requete.next();

        ui->labelProfilMembre->setText(ui->comboBoxIdMembreAdministration->itemText(i)+"\n\nNom : "+
                                       requete.value("nom").toString()+"\n\nPrenom : "+
                                       requete.value("prenom").toString());

        deconnecterBaseDeDonnee();
    }
    else {
        ui->labelProfilMembre->setText("");
    }
}

void FenetreSupprimerMembreAdministration::actualiserListeMembreAdministration()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT COUNT(id) as nbr FROM mbreadministration");
    requete.exec();

    requete.next();

    if(requete.value("nbr").toInt() > ui->comboBoxIdMembreAdministration->count()-1)
    {

        while (ui->comboBoxIdMembreAdministration->count() > 0) {
            ui->comboBoxIdMembreAdministration->removeItem(ui->comboBoxIdMembreAdministration->currentIndex());
        }

        ui->comboBoxIdMembreAdministration->addItem("---");

        requete.prepare("SELECT id FROM mbreadministration");
        requete.exec();

        while (requete.next()) {
            ui->comboBoxIdMembreAdministration->addItem(requete.value("id").toString());
        }
    }

    deconnecterBaseDeDonnee();
}

void FenetreSupprimerMembreAdministration::proposerMembreAdministration()
{
    ui->comboBoxIdMembreAdministration->addItem("---");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT id FROM mbreadministration");

    requete.exec();

    while (requete.next()) {
        ui->comboBoxIdMembreAdministration->addItem(requete.value("id").toString());
    }

    deconnecterBaseDeDonnee();
}
