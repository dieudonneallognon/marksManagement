#include "fenetreajoutermembreadministration.h"
#include "ui_fenetreajoutermembreadministration.h"

FenetreAjouterMembreAdministration::FenetreAjouterMembreAdministration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreAjouterMembreAdministration)
{
    ui->setupUi(this);

    fenetreAuthentification = new Authentification (this);
    fenetreAuthentification->hide();
    fenetreAuthentification->setTypeAuthentification(AUTHENTIFICATION_ESPACE_MEMBRE);

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonAjouterMembreAdministration,
            SIGNAL(pressed()),
            this,
            SLOT(enfoncerBoutonAjouterMembreAdministration()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonAjouterMembreAdministration,
            SIGNAL(released()),
            this,
            SLOT(relacherBoutonAjouterMembreAdministration()));

    connect(ui->boutonAjouterMembreAdministration, SIGNAL(clicked()), this, SLOT(ajouterMembreAdministration()));

    /*-----------------------------------------------------------------------------------*/
}

void FenetreAjouterMembreAdministration::afficherFenetreAuthentification(int f)
{
    if (f == 2)
        fenetreAuthentification->show();
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreAjouterMembreAdministration::enfoncerBoutonAjouterMembreAdministration(){
    ui->boutonAjouterMembreAdministration->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreAjouterMembreAdministration::relacherBoutonAjouterMembreAdministration(){
    ui->boutonAjouterMembreAdministration->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonAjouterMembreAdministration->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

void FenetreAjouterMembreAdministration::mousePressEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton){
        emit clicked_left();
    }
}

FenetreAjouterMembreAdministration::~FenetreAjouterMembreAdministration()
{
    delete ui;
}

/*----------------------------------------Définition du slot ajouterMembreAdministration------------------------------*/

bool FenetreAjouterMembreAdministration::nomMembreCorrect(QString nomMembre)
{
    QRegExp regexNomMembre ("^[A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ-]{3,}$");
    QRegExpValidator vldtr (regexNomMembre, this);

    int pos = 0;
    if (vldtr.validate(nomMembre, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}

bool FenetreAjouterMembreAdministration::prenomMembreCorrect(QString prenomMembre)
{
    QRegExp regexPrenomMembre ("^[A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ-]{3,}$");
    QRegExpValidator vldtr (regexPrenomMembre, this);

    int pos = 0;
    if (vldtr.validate(prenomMembre, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}

void FenetreAjouterMembreAdministration::ajouterMembreAdministration()
{

    if (ui->lineEditNom->text() == "" ||
            ui->lineEditPrenom->text() == ""){
        QMessageBox::critical(this, "Champs manquants", "Veuillez remplir tous les champs !");
    }
    else if (!nomMembreCorrect(ui->lineEditNom->text())) {
        QMessageBox::critical(this, "Nom incorrect", "Le nom ne doit contenir que des lettres, un tiret "
                                                     "ou un espace et doit être long d'au moins 3 caractères!");
    }
    else if (!prenomMembreCorrect(ui->lineEditPrenom->text())) {
        QMessageBox::critical(this, "Prénom incorrect", "Le prénom doit commencer par une lettre Majuscule, "
                                                        "ne doit contenir que des lettres, un tiret"
                                                        "ou un espace et doit être long d'au moins 3 caractères!");
    }

    else if (!MbreAdministrationExiste(ui->lineEditLogin->text())){
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("INSERT INTO mbreadministration (nom,prenom,login,mot_de_passe) VALUES(:nom,:prenom,:login,:mot_de_passe)");
        requete.bindValue(":nom", ui->lineEditNom->text());
        requete.bindValue(":prenom", ui->lineEditPrenom->text());
        requete.bindValue(":login", ui->lineEditLogin->text());
        requete.bindValue(":mot_de_passe", ui->lineEditMotDePasse->text());

        requete.exec();

        deconnecterBaseDeDonnee();

        QMessageBox::information(this, "MbreAdministration ajouté", "Le membre "+ui->lineEditNom->text()+" a été bien ajouté");
    }
}

bool FenetreAjouterMembreAdministration::MbreAdministrationExiste(QString MbreAdministration)
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT login FROM mbreadministration");
    requete.exec();

    while (requete.next()) {
        if (requete.value("login").toString() == MbreAdministration){
            QMessageBox::warning(this, "sqd", requete.value("login").toString());
            deconnecterBaseDeDonnee();
            return true;
        }
    }
    deconnecterBaseDeDonnee();
    return false;
}
