#include "authentification.h"
#include "ui_authentification.h"

Authentification::Authentification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Authentification)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModal);
    setWindowTitle("Authentification");
    setFixedSize(300, 380);
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonValider, SIGNAL(pressed()), this, SLOT(enfoncerBoutonValider()));
    connect(ui->boutonVoirMotDePasse, SIGNAL(pressed()), this, SLOT(enfoncerBoutonVoirMotDePasse()));

    /*--------------------------------connect relacherBouton----------------------------*/

    connect(ui->boutonValider, SIGNAL(released()), this, SLOT(relacherBoutonValider()));
    connect(ui->boutonVoirMotDePasse, SIGNAL(released()), this, SLOT(relacherBoutonVoirMotDePasse()));

    /*-----------------------------------Autres connect----------------------------*/

    connect(ui->boutonValider, SIGNAL(clicked()), this, SLOT(authentifier()));
    connect(this, SIGNAL(rediriger()), this->parent(), SLOT(close()));
    connect(this, SIGNAL(envoyerInfosCompte(int)), this->parent(), SLOT(afficherInfosCompte(int)));
}


/*-------------------------------------------------Définition des getters---------------------------------------------*/


QString Authentification::getNom() const
{
    return nomUtilisateur;
}

QString Authentification::getPrenom() const
{
    return prenomUtilisateur;
}

QString Authentification::getPrivilege() const
{
    return privilegeUtilisateur;
}

QString Authentification::getLogin() const
{
    return ui->lineEditLogin->text();
}

QString Authentification::getMotDePasse() const
{
    return ui->lineEditMotDePasse->text();
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void Authentification::enfoncerBoutonValider(){
    ui->boutonValider->setStyleSheet("QPushButton { background-color: #264178; }");
}

void Authentification::enfoncerBoutonVoirMotDePasse(){
    ui->boutonVoirMotDePasse->setStyleSheet("QPushButton { 	background-color: #949494; }");
    ui->lineEditMotDePasse->setEchoMode(QLineEdit::Normal);
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void Authentification::relacherBoutonValider(){
    ui->boutonValider->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonValider->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

void Authentification::relacherBoutonVoirMotDePasse(){
    ui->boutonVoirMotDePasse->setStyleSheet("QPushButton { background-color: #fff; }");
    ui->boutonVoirMotDePasse->setStyleSheet("QPushButton:hover { background-color: rgb(232, 232, 232); }");
    ui->lineEditMotDePasse->setEchoMode(QLineEdit::Password);
}


/*----------------------------------------Définition du slot authentifier-----------------------------------------*/
void Authentification::authentifier()
{
    if (ui->lineEditLogin->text() == "" || ui->lineEditMotDePasse->text() == ""){
        QMessageBox::critical(this, "Champs manquants", "Veuillez remplir tous les champs !");
    }
    else if (utilisateurExiste())
    {
        emit envoyerInfosCompte(AUTHENTIFICATION);
        ui->lineEditLogin->setText("");
        ui->lineEditMotDePasse->setText("");
        this->hide();
    }
    else {
        QMessageBox::critical(this, "Accès Impossible", "Login ou Mot de passe invalide !");
    }
}


bool Authentification::utilisateurExiste()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT * FROM mbreadministration");
    requete.exec();

    while (requete.next()) {
        if(requete.value("login").toString() == ui->lineEditLogin->text())
            if (requete.value("mot_de_passe").toString() == ui->lineEditMotDePasse->text()){
                nomUtilisateur = requete.value("nom").toString();
                prenomUtilisateur = requete.value("prenom").toString();
                privilegeUtilisateur = (requete.value("id").toInt() == 1) ? "Super-Administrateur" : "Membre Administration";
                return true;
            }
    }

    deconnecterBaseDeDonnee();

    return false;
}

/*-------------------------------------------------------CloseEvent-------------------------------------------------*/

void Authentification::closeEvent(QCloseEvent *event)
{
    if( typeAuthentification == AUTHENTIFICATION_ESPACE_MEMBRE){
        event->ignore();
        this->hide();
        emit rediriger();
    }
    else if (typeAuthentification == AUTHENTIFICATION_PRINCIPALE) {

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
}

Authentification::~Authentification()
{
    delete ui;
}
