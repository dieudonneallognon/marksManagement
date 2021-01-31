#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setFixedSize(1000, 600);
    setWindowIcon(QIcon(QPixmap(":/imgs/images/logo.ico")));
    setWindowTitle("Marks Management");

    fenetreAuthentification = new Authentification (this);
    fenetreAuthentification->hide();
    fenetreAuthentification->setTypeAuthentification(AUTHENTIFICATION_PRINCIPALE);

    fenetreAjouterAmphi = new FenetreAjouterAmphi (this);
    fenetreAjouterAmphi->hide();

    fenetreSupprimerAmphi = new FenetreSupprimerAmphi (this);
    fenetreSupprimerAmphi->hide();

    fenetreAjouterEtudiant = new FenetreAjouterEtudiant (this);
    fenetreAjouterEtudiant->hide();

    fenetreSupprimerEtudiant = new FenetreSupprimerEtudiant;
    fenetreSupprimerEtudiant->hide();

    fenetreAjouterMatiere = new FenetreAjouterMatiere (this);
    fenetreAjouterMatiere->hide();

    fenetreSupprimerMatiere = new FenetreSupprimerMatiere (this);
    fenetreSupprimerMatiere->hide();

    fenetreVoirListeEtudiant = new FenetreVoirListeEtudiant (this);
    fenetreVoirListeEtudiant->hide();

    fenetreVoirNoteEtudiant = new FenetreVoirNoteEtudiant (this);
    fenetreVoirNoteEtudiant->hide();

    fenetreModifierNote = new FenetreModifierNote (this);
    fenetreModifierNote->hide();

    fenetreMonProfil = new FenetreMonProfil (this);
    fenetreMonProfil->hide();

    fenetreAjouterMembreAdministration = new FenetreAjouterMembreAdministration (this);
    fenetreAjouterMembreAdministration->hide();

    fenetreListeMembreAdministration = new FenetreListeMembreAdministration (this);
    fenetreListeMembreAdministration->hide();

    fenetreSupprimerMembreAdministration = new FenetreSupprimerMembreAdministration (this);
    fenetreSupprimerMembreAdministration->hide();

    /*------------------------------connect enfoncerBouton-------------------------------*/

    connect(ui->boutonGererAmphi, SIGNAL(pressed()), this, SLOT(enfoncerBoutonGererAmphi()));
    connect(ui->boutonGererEtudiant, SIGNAL(pressed()), this, SLOT(enfoncerBoutonGererEtudiant()));
    connect(ui->boutonGererMatiere, SIGNAL(pressed()), this, SLOT(enfoncerBoutonGererMatiere()));
    connect(ui->boutonGererNote, SIGNAL(pressed()), this, SLOT(enfoncerBoutonGererNote()));
    connect(ui->boutonEspaceMembreAdministration,
            SIGNAL(pressed()), this, SLOT(enfoncerBoutonEspaceMembreAdministration()));
    connect(ui->boutonDeconnexion, SIGNAL(pressed()), this, SLOT(enfoncerBoutonDeconnexion()));

    /*-----------------------------connect relacherBouton----------------------------------*/

    connect(ui->boutonGererAmphi, SIGNAL(released()), this, SLOT(relacherBoutonGererAmphi()));
    connect(ui->boutonGererEtudiant, SIGNAL(released()), this, SLOT(relacherBoutonGererEtudiant()));
    connect(ui->boutonGererMatiere, SIGNAL(released()), this, SLOT(relacherBoutonGererMatiere()));
    connect(ui->boutonGererNote, SIGNAL(released()), this, SLOT(relacherBoutonGererNote()));
    connect(ui->boutonEspaceMembreAdministration,
            SIGNAL(released()), this, SLOT(relacherBoutonEspaceMembreAdministration()));
    connect(ui->boutonDeconnexion, SIGNAL(released()), this, SLOT(relacherBoutonDeconnexion()));

    /*-------------------------------------------connect afficherTab-------------------------*/

    connect(ui->boutonGererAmphi, SIGNAL(clicked()), this, SLOT(afficherTabGererAmphi()));
    connect(ui->boutonGererEtudiant, SIGNAL(clicked()), this, SLOT(afficherTabGererEtudiant()));
    connect(ui->boutonGererMatiere, SIGNAL(clicked()), this, SLOT(afficherTabGererMatiere()));
    connect(ui->boutonGererNote, SIGNAL(clicked()), this, SLOT(afficherTabGererNote()));
    connect(ui->boutonEspaceMembreAdministration,
            SIGNAL(clicked()),
            this,
            SLOT(afficherTabEspaceMembreAdministration()));

    if (this->premiereUtilisation()) {
        creerBaseDeDonne();
        deconnecterBaseDeDonnee();
        fenetreCreationSuperAdministrateur = new FenetreCreationSuperAdministrateur (this);
        fenetreCreationSuperAdministrateur->show();
    }
    else {
        fenetreAuthentification->show();
    }

    /*-------------------------------------------connect deconnexion-------------------------*/

    connect(ui->boutonDeconnexion, SIGNAL(clicked()), this, SLOT(deconnexion()));

    connect(this, SIGNAL(envoyerInfoCompte(QString, QString, QString, QString)),
            fenetreMonProfil, SLOT(recevoirInfoCompte(QString, QString, QString, QString)));
}

bool FenetrePrincipale::premiereUtilisation()
{
    QFile fichierBaseDeDonne ("gestionNotes.sdb");

    if(!fichierBaseDeDonne.exists()){
        return true;
    }
    else if (connecterBaseDeDonnee() && superAdminExiste()) {
        deconnecterBaseDeDonnee();
        return false;
    }
    else {
        deconnecterBaseDeDonnee();
        return true;
    }
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetrePrincipale::enfoncerBoutonGererAmphi()
{
    ui->boutonGererAmphi->setStyleSheet("QPushButton { background-color: #39a14f }");
}

void FenetrePrincipale::enfoncerBoutonGererEtudiant()
{
    ui->boutonGererEtudiant->setStyleSheet("QPushButton { background-color: #39a14f; }");
}

void FenetrePrincipale::enfoncerBoutonGererMatiere()
{
    ui->boutonGererMatiere->setStyleSheet("QPushButton { background-color: #39a14f; }");
}

void FenetrePrincipale::enfoncerBoutonGererNote()
{
    ui->boutonGererNote->setStyleSheet("QPushButton { background-color: #39a14f; }");
}

void FenetrePrincipale::enfoncerBoutonEspaceMembreAdministration()
{
    ui->boutonEspaceMembreAdministration->setStyleSheet("QPushButton { background-color: #1f6593; }");
}

void FenetrePrincipale::enfoncerBoutonDeconnexion()
{
    ui->boutonDeconnexion->setStyleSheet("QPushButton { background-color: #ab2a25; font-weight: bold; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetrePrincipale::relacherBoutonGererAmphi()
{
    ui->boutonGererAmphi->setStyleSheet("QPushButton { background-color: #efefef ; color: #7e7e7e; }");
    ui->boutonGererAmphi->setStyleSheet("QPushButton:hover { background-color: #40b55b; }");
}

void FenetrePrincipale::relacherBoutonGererEtudiant()
{
    ui->boutonGererEtudiant->setStyleSheet("QPushButton { background-color: #efefef ; color: #7e7e7e; }");
    ui->boutonGererEtudiant->setStyleSheet("QPushButton:hover { background-color: #40b55b; }");
}

void FenetrePrincipale::relacherBoutonGererMatiere()
{
    ui->boutonGererMatiere->setStyleSheet("QPushButton { background-color: #efefef ; color: #7e7e7e; }");
    ui->boutonGererMatiere->setStyleSheet("QPushButton:hover { background-color: #40b55b; }");
}

void FenetrePrincipale::relacherBoutonGererNote()
{
    ui->boutonGererNote->setStyleSheet("QPushButton { background-color: #efefef ; color: #7e7e7e; }");
    ui->boutonGererNote->setStyleSheet("QPushButton:hover { background-color: #40b55b; }");
}

void FenetrePrincipale::relacherBoutonEspaceMembreAdministration()
{
    ui->boutonEspaceMembreAdministration->setStyleSheet("QPushButton { background-color: #efefef ; color: #7e7e7e; }");
    ui->boutonEspaceMembreAdministration->setStyleSheet("QPushButton:hover { background-color: #2b88c6; }");
}

void FenetrePrincipale::relacherBoutonDeconnexion()
{
    ui->boutonDeconnexion->setStyleSheet("QPushButton { background-color: #efefef; color: #7e7e7e; } ");
    ui->boutonDeconnexion->setStyleSheet("QPushButton:hover { background-color: #d0342e; }");
}


/*------------------------------------Définition des slots afficherTab-----------------------------------------------*/

void FenetrePrincipale::afficherTabGererAmphi()
{
    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreAjouterMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreSupprimerMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    ui->tabPrincipal->clear();
    ui->tabPrincipal->addTab(fenetreAjouterAmphi, "Ajouter Amphi");
    ui->tabPrincipal->addTab(fenetreSupprimerAmphi, "Supprimer Amphi");
}

void FenetrePrincipale::afficherTabGererEtudiant()
{
    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreAjouterMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreSupprimerMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    ui->tabPrincipal->clear();
    ui->tabPrincipal->addTab(fenetreAjouterEtudiant, "Ajouter Etudiant");
    ui->tabPrincipal->addTab(fenetreSupprimerEtudiant, "Supprimer Etudiant");
    ui->tabPrincipal->addTab(fenetreVoirListeEtudiant, "Liste Etudiants");
}

void FenetrePrincipale::afficherTabGererMatiere()
{
    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreAjouterMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreSupprimerMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    ui->tabPrincipal->clear();
    ui->tabPrincipal->addTab(fenetreAjouterMatiere, "Ajouter Matière");
    ui->tabPrincipal->addTab(fenetreSupprimerMatiere, "Supprimer Matière");
}

void FenetrePrincipale::afficherTabGererNote()
{
    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreAjouterMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    disconnect(ui->tabPrincipal,
               SIGNAL(currentChanged(int)),
               fenetreSupprimerMembreAdministration,
               SLOT(afficherFenetreAuthentification(int)));

    ui->tabPrincipal->clear();
    ui->tabPrincipal->addTab(fenetreVoirNoteEtudiant, "Consulter Notes");
    ui->tabPrincipal->addTab(fenetreModifierNote, "Modifier Notes");
}

void FenetrePrincipale::afficherTabEspaceMembreAdministration()
{
    ui->tabPrincipal->clear();
    ui->tabPrincipal->addTab(fenetreMonProfil, "Mon Profil");
    ui->tabPrincipal->addTab(fenetreListeMembreAdministration, "Liste Membres Administration");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT login from mbreadministration WHERE id = 1");
    requete.exec();
    requete.next();

    if (requete.value("login").toString() == loginUtilisateur){
        ui->tabPrincipal->addTab(fenetreAjouterMembreAdministration, "Ajouter Membre Administration");
        ui->tabPrincipal->addTab(fenetreSupprimerMembreAdministration, "Supprimer Membre Administration");

        connect(ui->tabPrincipal,
                SIGNAL(currentChanged(int)),
                fenetreAjouterMembreAdministration,
                SLOT(afficherFenetreAuthentification(int)));

        connect(ui->tabPrincipal,
                SIGNAL(currentChanged(int)),
                fenetreSupprimerMembreAdministration,
                SLOT(afficherFenetreAuthentification(int)));
    }
}


/*----------------------------------------------Définition slot deconnexion--------------------------------------*/

void FenetrePrincipale::deconnexion()
{
    ui->tabPrincipal->clear();
    ui->labelInfosCompte->setText("...\n\n...\n\n...");
    fenetreAuthentification->show();
}


/*---------------------------------------Fonction pour afficher les infos du comptes----------------------------*/

void FenetrePrincipale::afficherInfosCompte(int typeInfo)
{   
    ui->tabPrincipal->show();

    if (typeInfo == CREATION_SUPER_ADMINISTRATEUR){

        nomUtilisateur = fenetreCreationSuperAdministrateur->getNom();
        prenomUtilisateur = fenetreCreationSuperAdministrateur->getPrenom();
        loginUtilisateur = fenetreCreationSuperAdministrateur->getLogin();
        motDePasse = fenetreCreationSuperAdministrateur->getMotDePasse();

        ui->labelInfosCompte->setText("Super-Administrateur\n\n"+nomUtilisateur
                                      +"\n\n"+prenomUtilisateur);

        emit envoyerInfoCompte(nomUtilisateur, prenomUtilisateur, loginUtilisateur, motDePasse);

    }
    else if (typeInfo == AUTHENTIFICATION) {

        nomUtilisateur = fenetreAuthentification->getNom();
        prenomUtilisateur = fenetreAuthentification->getPrenom();
        privilegeUtilisateur = fenetreAuthentification->getPrivilege();
        loginUtilisateur = fenetreAuthentification->getLogin();
        motDePasse = fenetreAuthentification->getMotDePasse();

        emit envoyerInfoCompte(nomUtilisateur, prenomUtilisateur, loginUtilisateur, motDePasse);

        ui->labelInfosCompte->setText(privilegeUtilisateur+"\n\n"+nomUtilisateur+"\n\n"+prenomUtilisateur);
    }
}

void Authentification::setTypeAuthentification(int type)
{
    typeAuthentification = type;
}
/*---------------------------------------------------------CloseEvent-------------------------------------------------*/

void FenetrePrincipale::closeEvent(QCloseEvent *event)
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

void FenetrePrincipale::aZero()
{
    ui->tabPrincipal->clear();
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}
