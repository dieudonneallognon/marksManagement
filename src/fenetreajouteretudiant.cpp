#include "fenetreajouteretudiant.h"
#include "ui_fenetreajouteretudiant.h"

FenetreAjouterEtudiant::FenetreAjouterEtudiant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreAjouterEtudiant)
{
    ui->setupUi(this);

    proposerAnneeAcademique();
    proposerAmphi();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeAmphi()));
    timer->start(500);



    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonAjouterEtudiant, SIGNAL(pressed()), this, SLOT(enfoncerBoutonAjouterEtudiant()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonAjouterEtudiant, SIGNAL(released()), this, SLOT(relacherBoutonAjouterEtudiant()));

    connect(ui->boutonAjouterEtudiant, SIGNAL(clicked()), this, SLOT(ajouterEtudiant()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------*/

void FenetreAjouterEtudiant::enfoncerBoutonAjouterEtudiant(){
    ui->boutonAjouterEtudiant->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreAjouterEtudiant::relacherBoutonAjouterEtudiant(){
    ui->boutonAjouterEtudiant->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonAjouterEtudiant->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}



bool FenetreAjouterEtudiant::nomEtudiantCorrect(QString nomEtudiant)
{
    QRegExp regexNomEtudiant ("^[A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ-]{3,}$");
    QRegExpValidator vldtr (regexNomEtudiant, this);

    int pos = 0;
    if (vldtr.validate(nomEtudiant, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}

bool FenetreAjouterEtudiant::prenomEtudiantCorrect(QString prenomEtudiant)
{
    QRegExp regexPrenomEtudiant ("^[A-ZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØŒÙÚÛÜÝŸ]{1}"
                                 "[A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ.-]{2,}$");
    QRegExpValidator vldtr (regexPrenomEtudiant, this);

    int pos = 0;
    if (vldtr.validate(prenomEtudiant, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}



bool FenetreAjouterEtudiant::etudiantExiste(int matricule)
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT matricule FROM etudiant");

    requete.exec();

    while (requete.next()) {
        if (requete.value("matricule").toInt() == matricule){
            QMessageBox::information(this, "Etudinant existant", "Un étudiant ayant le matricule "+
                                     requete.value("matricule").toString()+" existe déjà");
            deconnecterBaseDeDonnee();
            return true;
        }
    }
    deconnecterBaseDeDonnee();
    return false;
}

void FenetreAjouterEtudiant::proposerAnneeAcademique()
{
    QDate date;

    for (int i = 0; i < 3; i++) {
        int anneeCourante = date.currentDate().year() - 1 + i;
        int anneePrecedente = anneeCourante - 1;

        QString anneeAcademique = QString::number(anneePrecedente)+"-"+QString::number(anneeCourante);

        ui->comboBoxAnneeAcademique->addItem(anneeAcademique);
    }
}

void FenetreAjouterEtudiant::proposerAmphi()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT nom_amphi FROM amphi");
    requete.exec();

    while (requete.next()) {
        ui->comboBoxAmphi->addItem(requete.value("nom_amphi").toString());
    }

    deconnecterBaseDeDonnee();
}

void FenetreAjouterEtudiant::actualiserListeAmphi()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT COUNT(nom_amphi) as nbrAmphi FROM amphi");
    requete.exec();
    requete.next();

    if(requete.value("nbrAmphi").toInt() > ui->comboBoxAmphi->count()-1)
    {
        while (ui->comboBoxAmphi->count() > 1) {
            ui->comboBoxAmphi->removeItem(ui->comboBoxAmphi->currentIndex());
        }

        requete.prepare("SELECT nom_amphi FROM amphi");
        requete.exec();

        while (requete.next()) {
            ui->comboBoxAmphi->addItem(requete.value("nom_amphi").toString());
        }
    }

    deconnecterBaseDeDonnee();
}


void FenetreAjouterEtudiant::ajouterEtudiant()
{

    if (ui->lineEditNomEtudiant->text() == "" ||
            ui->lineEditPrenomEtudiant->text() == ""){
        QMessageBox::information(this, "Champs manquants", "Veuillez remplir tous les champs !");
    }
    else if (!nomEtudiantCorrect(ui->lineEditNomEtudiant->text())) {
        QMessageBox::critical(this, "Nom incorrect", "Le nom ne doit contenir que des lettres, un tiret "
                                                     "ou un espace et doit être long d'au moins 3 caractères!");
    }
    else if (!prenomEtudiantCorrect(ui->lineEditPrenomEtudiant->text())) {
        QMessageBox::critical(this, "Prénom incorrect", "Le prénom doit commencer par une lettre Majuscule, "
                                                        "ne doit contenir que des lettres, un tiret "
                                                        "ou un espace et doit être long d'au moins 3 caractères!");
    }
    else if (!etudiantExiste(ui->spinBoxMatricule->value())){

        connecterBaseDeDonnee();

        QString dateNaissance = QString::number(ui->spinBoxAnnee->value());

        if (ui->spinBoxMois->value() < 10) {
            dateNaissance+="-0"+QString::number(ui->spinBoxMois->value());
        }
        else {
            dateNaissance+="-"+QString::number(ui->spinBoxMois->value());
        }

        if (ui->spinBoxJour->value() < 10){
            dateNaissance+="-0"+QString::number(ui->spinBoxJour->value());
        }
        else {
            dateNaissance+="-"+QString::number(ui->spinBoxJour->value());
        }

        QSqlQuery requete;

        requete.prepare("INSERT INTO etudiant (matricule, nom, prenom, date_naissance) "
                        "VALUES(:matricule, :nom, :prenom, :date_naissance)");

        requete.bindValue(":matricule", ui->spinBoxMatricule->value());
        requete.bindValue(":nom", ui->lineEditNomEtudiant->text());
        requete.bindValue(":prenom", ui->lineEditPrenomEtudiant->text());
        requete.bindValue(":date_naissance", dateNaissance);

        requete.exec();

        deconnecterBaseDeDonnee();

        QMessageBox::information(this, "Etudiant ajouté", "L'étudiant "+ui->lineEditNomEtudiant->text()+" "+
                                 ui->lineEditPrenomEtudiant->text()+" a été bien ajouté");
    }

    if(nomEtudiantCorrect(ui->lineEditNomEtudiant->text()) && prenomEtudiantCorrect(ui->lineEditPrenomEtudiant->text())){
        ajouterAnneeAcademique();
        ajouterInscription();
    }
}

bool FenetreAjouterEtudiant::anneeAcademiqueCorrect(QString anneeAcademique)
{
    if (anneeAcademique == "---")
        return false;
    else
        return true;
}

bool FenetreAjouterEtudiant::anneeAcademiqueExiste(QString anneAcademique)
{

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT count(an_academiq) AS nbrAnnee FROM annee_academique WHERE an_academiq = :an_academiq");
    requete.bindValue(":an_academiq", anneAcademique);
    requete.exec();

    requete.next();

    if(requete.value("nbrAnnee").toInt() == 0){
        deconnecterBaseDeDonnee();
        return false;
    }
    else {
        deconnecterBaseDeDonnee();
        return true;
    }
}

void FenetreAjouterEtudiant::ajouterAnneeAcademique()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    if (!anneeAcademiqueExiste(ui->comboBoxAnneeAcademique->currentText())){
        requete.prepare("INSERT INTO annee_academique (an_academiq) VALUES(:an_academiq)");
        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
        requete.exec();
    }

    deconnecterBaseDeDonnee();
}

bool FenetreAjouterEtudiant::inscriptionExiste(int matricule, QString anneeAcademique)
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT COUNT() AS nbr FROM inscrire WHERE (matricule =:matricule) AND (an_academiq=:an_academiq)");

    requete.bindValue(":matricule", matricule);
    requete.bindValue(":an_academiq", anneeAcademique);

    requete.exec();
    requete.next();

    if (requete.value("nbr").toInt() == 0){
        deconnecterBaseDeDonnee();
        return false;
    }else {
        deconnecterBaseDeDonnee();
        return true;
    }
}

void FenetreAjouterEtudiant::ajouterInscription()
{
    if(!inscriptionExiste(ui->spinBoxMatricule->value(), ui->comboBoxAnneeAcademique->currentText())){

        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("INSERT INTO inscrire (matricule, an_academiq, nom_amphi) "
                        "VALUES(:matricule, :an_academiq, :nom_amphi)");

        requete.bindValue(":matricule", ui->spinBoxMatricule->value());
        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
        requete.bindValue(":nom_amphi", ui->comboBoxAmphi->currentText());
        requete.exec();

        QMessageBox::information(this, "Inscription réussie", "L'étudiant "+ui->lineEditNomEtudiant->text()+" "+ui->lineEditPrenomEtudiant->text()+
                                 " a été inscri pour l'année académique "+ui->comboBoxAnneeAcademique->currentText()+
                                 " dans l'amphi "+ui->comboBoxAmphi->currentText());
    }
    else {
        QMessageBox::critical(this, "Ajout impossible", "Un étudiant ayant le matricule "+
                              QString::number(ui->spinBoxMatricule->value())+" a déjé été inscris dans une amphi "
                                                                             "pour l'année académique "+ui->comboBoxAnneeAcademique->currentText());
    }

    deconnecterBaseDeDonnee();
}

FenetreAjouterEtudiant::~FenetreAjouterEtudiant()
{
    delete ui;
}
