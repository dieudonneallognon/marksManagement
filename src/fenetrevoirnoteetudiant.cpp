#include "fenetrevoirnoteetudiant.h"
#include "ui_fenetrevoirnoteetudiant.h"

FenetreVoirNoteEtudiant::FenetreVoirNoteEtudiant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreVoirNoteEtudiant)


{
    ui->setupUi(this);

    proposerMatricule();
    proposerMatiere();
    proposerAnneeAcademique();

    QTimer* timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeEtudiant()));
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeMatiere()));
    timer->start(500);

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonVoirNote, SIGNAL(pressed()), this, SLOT(enfoncerBoutonVoirNote()));

    /*--------------------------------connect relacherBouton----------------------------*/

    connect(ui->boutonVoirNote, SIGNAL(released()), this, SLOT(relacherBoutonVoirNote()));
    connect(ui->boutonVoirNote, SIGNAL(clicked()), this, SLOT(afficherNoteEtudiant()));
}

/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreVoirNoteEtudiant::enfoncerBoutonVoirNote(){
    ui->boutonVoirNote->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreVoirNoteEtudiant::relacherBoutonVoirNote(){
    ui->boutonVoirNote->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonVoirNote->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

FenetreVoirNoteEtudiant::~FenetreVoirNoteEtudiant()
{
    delete ui;
}

void FenetreVoirNoteEtudiant::proposerMatricule()
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

void FenetreVoirNoteEtudiant::proposerMatiere()
{
    ui->comboBoxNomMatiere->addItem("---");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT nom_mat FROM matiere");
    requete.exec();

    while (requete.next()) {
        ui->comboBoxNomMatiere->addItem(requete.value("nom_mat").toString());
    }

    deconnecterBaseDeDonnee();
}

void FenetreVoirNoteEtudiant::proposerAnneeAcademique()
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

void FenetreVoirNoteEtudiant::afficherNoteEtudiant()
{
    ui->labelMatricule->setText("MATRICULES\n");
    ui->labelNomEtudiant->setText("NOMS\n");
    ui->labelPrenomEtudiant->setText("PRENOMS\n");
    ui->labelNoteEtudiant->setText("NOTES\n");
    ui->labelAnnee->setText("ANNEE ACADEMIQUES\n");
    ui->labelMatiere->setText("MATIERES\n");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    if((ui->comboBoxMatriculeEtudiant->currentText() == "---")
            && (ui->comboBoxAnneeAcademique->currentText() == "---")
            && (ui->comboBoxNomMatiere->currentText() == "---"))
    {
        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE (etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat)");
    }

    else if((ui->comboBoxMatriculeEtudiant->currentText() != "---") &&
            (ui->comboBoxAnneeAcademique->currentText() == "---") &&
            (ui->comboBoxNomMatiere->currentText() == "---"))
    {
        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE (etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat) "
                        "AND "
                        "(etudiant.matricule = :matricule)");


        requete.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText());
    }

    else if((ui->comboBoxMatriculeEtudiant->currentText() == "---") &&
            (ui->comboBoxAnneeAcademique->currentText() != "---") &&
            (ui->comboBoxNomMatiere->currentText() == "---"))
    {
        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE (etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat) "
                        "AND "
                        "(annee_academique.an_academiq = :an_academiq)");


        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
    }

    else if((ui->comboBoxMatriculeEtudiant->currentText() == "---") &&
            (ui->comboBoxAnneeAcademique->currentText() == "---") &&
            (ui->comboBoxNomMatiere->currentText() != "---"))
    {
        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE "
                        "(etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat) "
                        "AND "
                        "(matiere.nom_mat = :nom_mat)");


        requete.bindValue(":nom_mat", ui->comboBoxNomMatiere->currentText());

    }

    else if((ui->comboBoxMatriculeEtudiant->currentText() != "---") &&
            (ui->comboBoxAnneeAcademique->currentText() != "---") &&
            (ui->comboBoxNomMatiere->currentText() == "---"))
    {
        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE (etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat) "
                        "AND "
                        "(etudiant.matricule = :matricule) "
                        "AND "
                        "(annee_academique.an_academiq = :an_academiq)");

        requete.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText());
        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
    }

    else if((ui->comboBoxMatriculeEtudiant->currentText() != "---") &&
            (ui->comboBoxAnneeAcademique->currentText() == "---") &&
            (ui->comboBoxNomMatiere->currentText() != "---"))
    {
        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE (etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat) "
                        "AND "
                        "(etudiant.matricule = :matricule ) "
                        "AND "
                        "(matiere.nom_mat = :nom_mat)");

        requete.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText());
        requete.bindValue(":nom_mat", ui->comboBoxNomMatiere->currentText());
    }

    else if((ui->comboBoxMatriculeEtudiant->currentText() == "---") &&
            (ui->comboBoxAnneeAcademique->currentText() != "---") &&
            (ui->comboBoxNomMatiere->currentText() != "---"))
    {
        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE (etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat) "
                        "AND "
                        "(matiere.nom_mat = :nom_mat) "
                        "AND "
                        "(annee_academique.an_academiq = :an_academiq)");
        requete.bindValue(":nom_mat", ui->comboBoxNomMatiere->currentText());
        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
    }


    else if((ui->comboBoxMatriculeEtudiant->currentText() != "---") &&
            (ui->comboBoxAnneeAcademique->currentText() != "---") &&
            (ui->comboBoxNomMatiere->currentText() != "---")){

        requete.prepare("SELECT * FROM etudiant INNER JOIN note INNER JOIN annee_academique INNER JOIN matiere "
                        "WHERE (etudiant.matricule = note.matricule) "
                        "AND "
                        "(annee_academique.an_academiq = note.an_academiq) "
                        "AND "
                        "(matiere.num_mat = note.num_mat) "
                        "AND "
                        "(etudiant.matricule = :matricule ) "
                        "AND "
                        "(matiere.nom_mat = :nom_mat) "
                        "AND "
                        "(annee_academique.an_academiq = :an_academiq)");

        requete.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText());
        requete.bindValue(":nom_mat", ui->comboBoxNomMatiere->currentText());
        requete.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());
    }

    requete.exec();

    while (requete.next()) {
        ui->labelMatricule->setText(ui->labelMatricule->text()+requete.value("matricule").toString()+"\n\n");
        ui->labelNomEtudiant->setText(ui->labelNomEtudiant->text()+requete.value("nom").toString()+"\n\n");
        ui->labelPrenomEtudiant->setText(ui->labelPrenomEtudiant->text()+requete.value("prenom").toString()+"\n\n");
        ui->labelAnnee->setText(ui->labelAnnee->text()+requete.value("an_academiq").toString()+"\n\n");
        ui->labelMatiere->setText(ui->labelMatiere->text()+requete.value("nom_mat").toString()+"\n\n");

        if(requete.value("note_etudiant").toInt() < 10){
            ui->labelNoteEtudiant->setText(ui->labelNoteEtudiant->text()+"0"+requete.value("note_etudiant").toString()+"\n\n");
        }
        else {
            ui->labelNoteEtudiant->setText(ui->labelNoteEtudiant->text()+requete.value("note_etudiant").toString()+"\n\n");
        }
    }

    deconnecterBaseDeDonnee();
}

void FenetreVoirNoteEtudiant::actualiserListeEtudiant()
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

void FenetreVoirNoteEtudiant::actualiserListeMatiere()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT COUNT(nom_mat) as nbr FROM matiere");
    requete.exec();
    requete.next();

    if(requete.value("nbr").toInt() > ui->comboBoxNomMatiere->count()-1)
    {
        while (ui->comboBoxNomMatiere->count() > 0) {
            ui->comboBoxNomMatiere->removeItem(ui->comboBoxNomMatiere->currentIndex());
        }

        ui->comboBoxNomMatiere->addItem("---");

        requete.prepare("SELECT nom_mat FROM matiere");
        requete.exec();

        while (requete.next()) {
            ui->comboBoxNomMatiere->addItem(requete.value("nom_mat").toString());
        }
    }

    deconnecterBaseDeDonnee();
}
