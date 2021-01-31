#include "fenetrevoirlisteetudiant.h"
#include "ui_fenetrevoirlisteetudiant.h"

FenetreVoirListeEtudiant::FenetreVoirListeEtudiant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreVoirListeEtudiant)
{
    ui->setupUi(this);

    proposerAmphi();
    proposerAnneeAcademique();

    QTimer* timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeAmphi()));
    timer->start();

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonVoirListeEtudiant, SIGNAL(pressed()), this, SLOT(enfoncerBoutonVoirListeEtudiant()));

    /*--------------------------------connect relacherBouton----------------------------*/

    connect(ui->boutonVoirListeEtudiant, SIGNAL(released()), this, SLOT(relacherBoutonVoirListeEtudiant()));

    connect(ui->boutonVoirListeEtudiant, SIGNAL(clicked()), this, SLOT(afficherListeEtudiant()));
}

/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreVoirListeEtudiant::enfoncerBoutonVoirListeEtudiant(){
    ui->boutonVoirListeEtudiant->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreVoirListeEtudiant::relacherBoutonVoirListeEtudiant(){
    ui->boutonVoirListeEtudiant->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonVoirListeEtudiant->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

void FenetreVoirListeEtudiant::proposerAmphi()
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

void FenetreVoirListeEtudiant::proposerAnneeAcademique()
{
    ui->comboBoxAnneeAcademique->addItem("---");

    QDate date;

    for (int i = 0; i < 3; i++) {
        int anneeCourante = date.currentDate().year() - 1 + i;
        int anneePrecedente = anneeCourante - 1;

        QString anneeAcademique = QString::number(anneePrecedente)+"-"+QString::number(anneeCourante);

        ui->comboBoxAnneeAcademique->addItem(anneeAcademique);
    }
}

void FenetreVoirListeEtudiant::afficherListeEtudiant()
{
    ui->labelMatricule->setText("\nMATRICULES\n\n");
    ui->labelNom->setText("\nNOMS\n\n");
    ui->labelPrenom->setText("\nPRENOMS\n\n");
    ui->labelDateNaissance->setText("DATE\nDE NAISSANCE\n\n");
    ui->labelAnneAcademique->setText("ANNEE\nACADEMIQUE\n\n");
    ui->labelAmphi->setText("\nAMPHIS\n\n");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    if((ui->comboBoxNomAmphi->currentText() == "---") && (ui->comboBoxAnneeAcademique->currentText() == "---")){

        requete.prepare("SELECT * FROM etudiant INNER JOIN inscrire INNER JOIN annee_academique "
                        "WHERE (etudiant.matricule = inscrire.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = inscrire.an_academiq)");
    }
    else if ((ui->comboBoxAnneeAcademique->currentText() != "---") && (ui->comboBoxNomAmphi->currentText() == "---")) {

        requete.prepare("SELECT * FROM etudiant INNER JOIN inscrire INNER JOIN annee_academique "
                        "WHERE (etudiant.matricule = inscrire.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = inscrire.an_academiq) "
                        "AND "
                        "(annee_academique.an_academiq = :an_academiq)");

        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
    }
    else if ((ui->comboBoxAnneeAcademique->currentText() == "---") && (ui->comboBoxNomAmphi->currentText() != "---")) {

        requete.prepare("SELECT * FROM etudiant INNER JOIN inscrire INNER JOIN annee_academique "
                        "WHERE (etudiant.matricule = inscrire.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = inscrire.an_academiq) "
                        "AND "
                        "inscrire.nom_amphi = :nom_amphi");

        requete.bindValue(":nom_amphi", ui->comboBoxNomAmphi->currentText());
    }
    else if ((ui->comboBoxAnneeAcademique->currentText() != "---") && (ui->comboBoxNomAmphi->currentText() != "---")) {

        requete.prepare("SELECT * FROM etudiant INNER JOIN inscrire INNER JOIN annee_academique "
                        "WHERE (etudiant.matricule = inscrire.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = inscrire.an_academiq) "
                        "AND "
                        "(annee_academique.an_academiq = :an_academiq)"
                        "AND "
                        "(inscrire.nom_amphi = :nom_amphi)");

        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
        requete.bindValue(":nom_amphi", ui->comboBoxNomAmphi->currentText());
    }

    requete.exec();

    while (requete.next()) {
        ui->labelMatricule->setText(ui->labelMatricule->text()+requete.value("matricule").toString()+"\n\n");
        ui->labelNom->setText(ui->labelNom->text()+requete.value("nom").toString()+"\n\n");
        ui->labelPrenom->setText(ui->labelPrenom->text()+requete.value("prenom").toString()+"\n\n");
        ui->labelDateNaissance->setText(ui->labelDateNaissance->text()+requete.value("date_naissance").toString()+"\n\n");
        ui->labelAnneAcademique->setText(ui->labelAnneAcademique->text()+requete.value("an_academiq").toString()+"\n\n");
        ui->labelAmphi->setText(ui->labelAmphi->text()+requete.value("nom_amphi").toString()+"\n\n");
    }

    deconnecterBaseDeDonnee();
}

void FenetreVoirListeEtudiant::actualiserListeAmphi()
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

FenetreVoirListeEtudiant::~FenetreVoirListeEtudiant()
{
    delete ui;
}
