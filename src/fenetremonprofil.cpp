#include "fenetremonprofil.h"
#include "ui_fenetremonprofil.h"

FenetreMonProfil::FenetreMonProfil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreMonProfil)
{
    ui->setupUi(this);

    afficherProfilUtilistaur();

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonChangerMotDePasse, SIGNAL(pressed()), this, SLOT(enfoncerBoutonChangerMotDePasse()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonChangerMotDePasse, SIGNAL(released()), this, SLOT(relacherBoutonChangerMotDePasse()));

    connect(ui->boutonChangerMotDePasse, SIGNAL(clicked()), this, SLOT(modifiermotdepasse()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreMonProfil::enfoncerBoutonChangerMotDePasse(){
    ui->boutonChangerMotDePasse->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreMonProfil::relacherBoutonChangerMotDePasse(){
    ui->boutonChangerMotDePasse->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonChangerMotDePasse->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

FenetreMonProfil::~FenetreMonProfil()
{
    delete ui;
}
/*----------------------------------------Définition du slot ModifierMotDePasse---------------------------------*/

void FenetreMonProfil::modifiermotdepasse()
{
    if(ui->lineEditMotDePasseActuel->text() == "" ||
            ui->lineEditNouveauMotDePasse->text() == "" ||
            ui->lineEditConfirmationMotDePasse->text() == ""){

        QMessageBox::critical(this, "Champs manquants", "Veuillez remplir tous les champs !");
    }

    else if (ui->lineEditNouveauMotDePasse->text().length() < 5) {
        QMessageBox::critical(this, "Nouveau mot de Passe trop court", "Votre Mot de Passe doit être long d'au moins "
                                                                       "5 caractères !");
    }

    else if (ui->lineEditNouveauMotDePasse->text() != ui->lineEditConfirmationMotDePasse->text()) {
        QMessageBox::critical(this, "Confirmation du Mot de Passe", "Mot de Passe mal confirmé !");
    }
    else if (ui->lineEditMotDePasseActuel->text() != motDePasseUtilisateur){
        QMessageBox::critical(this, "Mot de passe incorrect", "Votre mot de passe est incorrect !");
    }
    else {

        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("UPDATE mbreadministration SET mot_de_passe = :mot_de_passe WHERE login = :login");

        requete.bindValue(":mot_de_passe", ui->lineEditNouveauMotDePasse->text());
        requete.bindValue(":login", loginUtilisateur);

        requete.exec();

        deconnecterBaseDeDonnee();

        QMessageBox::information(this, "Mot de passe modifié", "Votre mot de passe a été modifié avec succès");

        ui->lineEditMotDePasseActuel->setText("");
        ui->lineEditNouveauMotDePasse->setText("");
        ui->lineEditConfirmationMotDePasse->setText("");
    }
}

void FenetreMonProfil::recevoirInfoCompte(QString nom, QString prenom, QString login, QString motDePasse)
{
    nomUtilisateur = nom;
    prenomUtilisateur = prenom;
    loginUtilisateur = login;
    motDePasseUtilisateur = motDePasse;

    afficherProfilUtilistaur();
}

void FenetreMonProfil::afficherProfilUtilistaur()
{
    ui->labelInfosProfil->setText("Nom : "+nomUtilisateur+
                                  "\n\nPrénom : "+prenomUtilisateur+
                                  "\n\nLogin : "+loginUtilisateur);
}
