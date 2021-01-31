#include "fenetrecreationsuperadministrateur.h"
#include "ui_fenetrecreationsuperadministrateur.h"

FenetreCreationSuperAdministrateur::FenetreCreationSuperAdministrateur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreCreationSuperAdministrateur)
{
    ui->setupUi(this);
    setFixedSize(380, 520);
    setWindowModality(Qt::WindowModal);
    setWindowTitle("Création du Super-Administrateur");
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonValider, SIGNAL(pressed()), this, SLOT(enfoncerBoutonValider()));
    connect(ui->boutonVoirMotDePasse, SIGNAL(pressed()), this, SLOT(enfoncerBoutonVoirMotDePasse()));

    /*--------------------------------connect relacherBouton----------------------------*/

    connect(ui->boutonValider, SIGNAL(released()), this, SLOT(relacherBoutonValider()));
    connect(ui->boutonVoirMotDePasse, SIGNAL(released()), this, SLOT(relacherBoutonVoirMotDePasse()));

    /*-----------------------------------Autres connect----------------------------*/

    connect(ui->boutonValider, SIGNAL(clicked()), this, SLOT(creerSuperAdministrateur()));
    connect(this, SIGNAL(envoyerInfosCompte(int)), this->parent(), SLOT(afficherInfosCompte(int)));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreCreationSuperAdministrateur::enfoncerBoutonValider(){
    ui->boutonValider->setStyleSheet("QPushButton { background-color: #069145; }");
}

void FenetreCreationSuperAdministrateur::enfoncerBoutonVoirMotDePasse(){
    ui->boutonVoirMotDePasse->setStyleSheet("QPushButton { 	background-color: #949494; }");
    ui->lineEditMotDePasse->setEchoMode(QLineEdit::Normal);
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------------*/

void FenetreCreationSuperAdministrateur::relacherBoutonValider(){
    ui->boutonValider->setStyleSheet("QPushButton { background-color: #0aac55; }");
    ui->boutonValider->setStyleSheet("QPushButton:hover { background-color: #08a24e; }");
}

void FenetreCreationSuperAdministrateur::relacherBoutonVoirMotDePasse(){
    ui->boutonVoirMotDePasse->setStyleSheet("QPushButton { background-color: #fff; }");
    ui->boutonVoirMotDePasse->setStyleSheet("QPushButton:hover { background-color: rgb(232, 232, 232); }");
    ui->lineEditMotDePasse->setEchoMode(QLineEdit::Password);
}


/*----------------------------------------Définition du slot creerSuperAdministrateur---------------------------------*/

bool FenetreCreationSuperAdministrateur::nomCorrect(QString nom)
{
    QRegExp regexNom ("^[A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ.-]{3,}$");
    QRegExpValidator vldtr (regexNom, this);

    int pos = 0;
    if (vldtr.validate(nom, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}

bool FenetreCreationSuperAdministrateur::prenomCorrect(QString nom)
{
    QRegExp regexPrenom ("^[A-ZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØŒÙÚÛÜÝŸ]{1}"
                         "[A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ.-]{2,}$");
    QRegExpValidator vldtr (regexPrenom, this);

    int pos = 0;
    if (vldtr.validate(nom, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}

bool FenetreCreationSuperAdministrateur::loginCorrect(QString login)
{
    QRegExp regexLogin ("^[0-9A-Za-z]{3,}");
    QRegExpValidator vldtr (regexLogin, this);
    int pos = 0;
    if (vldtr.validate(login, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return true;
    }
}


void FenetreCreationSuperAdministrateur::creerSuperAdministrateur()
{
    QString login;
    QString motDePasse;

    login = motDePasse = "admin";

    if (ui->lineEditNom->text() == "" ||
            ui->lineEditPrenom->text() == "" ||
            ui->lineEditLogin->text() == "" ||
            ui->lineEditMotDePasse->text() == "" ||
            ui->lineEditConfirmationMotDePasse->text() == ""){
        QMessageBox::information(this, "Champs manquants", "Veuillez remplir tous les champs !");
    }
    else if (!nomCorrect(ui->lineEditNom->text())) {
        QMessageBox::critical(this, "Nom incorrect", "Votre nom ne doit contenir que des lettres, un tiret, un point "
                                                     "ou un espace et doit être long d'au moins 3 caractères!");
    }
    else if (!prenomCorrect(ui->lineEditPrenom->text())) {
        QMessageBox::critical(this, "Prénom incorrect", "Votre prénom doit commencer par une lettre Majuscule, "
                                                        "ne doit contenir que des lettres, un tiret, un point "
                                                        "ou un espace et doit être long d'au moins 3 caractères!");
    }
    else if (!loginCorrect(ui->lineEditLogin->text())) {
        QMessageBox::information(this, "Login incorrect", "Votre Login ne doit contenir que des chiffres ou des lettres "
                                                          "et doit être long d'au moins 3 caractères !");
    }
    else if (ui->lineEditMotDePasse->text().length() < 5) {
        QMessageBox::information(this, "Mot de Passe trop court", "Votre Mot de Passe doit être long d'au moins "
                                                                  "5 caractères !");
    }
    else if (ui->lineEditMotDePasse->text() != ui->lineEditConfirmationMotDePasse->text()) {
        QMessageBox::critical(this, "Confirmation du Mot de Passe", "Mot de Passe mal confirmé !");
    }
    else {
        if(connecterBaseDeDonnee()){

            QSqlQuery requete;

            requete.prepare("INSERT INTO mbreadministration (nom, prenom, login, mot_de_passe) "
                            "VALUES(:nom, :prenom, :login, :mot_de_passe)");

            requete.bindValue(":nom", ui->lineEditNom->text());
            requete.bindValue(":prenom", ui->lineEditPrenom->text());
            requete.bindValue(":login", ui->lineEditLogin->text());
            requete.bindValue(":mot_de_passe", ui->lineEditMotDePasse->text());

            requete.exec();

            deconnecterBaseDeDonnee();
        }

        emit envoyerInfosCompte(CREATION_SUPER_ADMINISTRATEUR);
        this->hide();
    }
}

/*-------------------------------------------------------CloseEvent---------------------------------------------------*/

void FenetreCreationSuperAdministrateur::closeEvent(QCloseEvent *event)
{
    int reponse = QMessageBox::question(this,
                                        "Confirmation Sortie",
                                        "Êtes-vous sûr(e) de vouloir quitter l'application ?");
    if(reponse == QMessageBox::Yes) {
        qApp->quit();
        deconnecterBaseDeDonnee();
    }
    else if (reponse == QMessageBox::No) {
        event->ignore();
    }
}

QString FenetreCreationSuperAdministrateur::getNom() const
{
    return ui->lineEditNom->text();
}

QString FenetreCreationSuperAdministrateur::getPrenom() const
{
    return  ui->lineEditPrenom->text();
}

QString FenetreCreationSuperAdministrateur::getLogin() const
{
    return ui->lineEditLogin->text();
}

QString FenetreCreationSuperAdministrateur::getMotDePasse() const
{
    return ui->lineEditMotDePasse->text();
}


FenetreCreationSuperAdministrateur::~FenetreCreationSuperAdministrateur()
{
    delete ui;
}
