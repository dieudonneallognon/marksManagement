#include "fenetremodifiernote.h"
#include "ui_fenetremodifiernote.h"

FenetreModifierNote::FenetreModifierNote(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreModifierNote)
{
    ui->setupUi(this);

    proposerMatricule();
    proposerMatiere();
    proposerAnneeAcademique();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeMatiere()));
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeEtudiant()));
    timer->start(500);

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonModifierNoteEtudiant, SIGNAL(pressed()), this, SLOT(enfoncerBoutonModifierNote()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonModifierNoteEtudiant, SIGNAL(released()), this, SLOT(relacherBoutonModifierNote()));

    connect(ui->boutonModifierNoteEtudiant, SIGNAL(clicked()), this, SLOT(modifierNoteEtudiant()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreModifierNote::enfoncerBoutonModifierNote(){
    ui->boutonModifierNoteEtudiant->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreModifierNote::relacherBoutonModifierNote(){
    ui->boutonModifierNoteEtudiant->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonModifierNoteEtudiant->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

void FenetreModifierNote::proposerMatricule()
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

void FenetreModifierNote::proposerMatiere()
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

void FenetreModifierNote::proposerAnneeAcademique()
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

int FenetreModifierNote::recupererNumeroMatiere()
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT num_mat FROM matiere WHERE nom_mat = :nom_mat");
    requete.bindValue(":nom_mat", ui->comboBoxNomMatiere->currentText());
    requete.exec();

    requete.next();

    int num_mat = requete.value("num_mat").toInt();

    deconnecterBaseDeDonnee();

    return num_mat;
}

void FenetreModifierNote::modifierNoteEtudiant()
{
    if (ui->comboBoxNomMatiere->currentText() != "---" &&
            ui->comboBoxAnneeAcademique->currentText() != "---" &&
            ui->comboBoxMatriculeEtudiant->currentText() != "---"){

        int num_mat = recupererNumeroMatiere();

        connecterBaseDeDonnee();

        QSqlQuery requeteRecherche;

        requeteRecherche.prepare("SELECT COUNT() AS nbr FROM note "
                                 "WHERE (matricule = :matricule) "
                                 "AND "
                                 "(num_mat = :num_mat) "
                                 "AND "
                                 "(an_academiq = :an_academiq)");

        requeteRecherche.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText().toInt());
        requeteRecherche.bindValue(":num_mat", num_mat);
        requeteRecherche.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());

        requeteRecherche.exec();

        requeteRecherche.next();

        if (requeteRecherche.value("nbr").toInt() == 0){

            QSqlQuery requeteInsertion;

            requeteInsertion.prepare("INSERT INTO note (note_etudiant, matricule, num_mat, an_academiq) "
                                     "VALUES(:note_etudiant, :matricule, :num_mat, :an_academiq)");

            requeteInsertion.bindValue(":note_etudiant", ui->spinBoxNouvelleNote->value());
            requeteInsertion.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText().toInt());
            requeteInsertion.bindValue(":num_mat", num_mat);
            requeteInsertion.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());

            requeteInsertion.exec();

            if (ui->spinBoxNouvelleNote->value() < 10){
                QMessageBox::information(this, "Note ajoutée",
                                         "La note 0"+QString::number(ui->spinBoxNouvelleNote->value())+
                                         " en "+ui->comboBoxNomMatiere->currentText()+
                                         " pour l'étudiant ayant le matricule "+
                                         ui->comboBoxMatriculeEtudiant->currentText()+
                                         " a été bien ajouté");
            }
            else {
                QMessageBox::information(this, "Note ajoutée",
                                         "La note "+QString::number(ui->spinBoxNouvelleNote->value())+
                                         " en "+ui->comboBoxNomMatiere->currentText()+
                                         " pour l'étudiant ayant le matricule "+
                                         ui->comboBoxMatriculeEtudiant->currentText()+
                                         " a été bien ajouté");
            }
        }
        else {

            int reponse = QMessageBox::question(this, "Note existante", "L'étudiant choisi possède déjà une note dans la matière sélectionnée.\n"
                                                                        "Êtes-vous sûr de modifier la note ?");
            if(reponse == QMessageBox::Yes) {

                QSqlQuery requeteModification;

                requeteModification.prepare("UPDATE note SET note_etudiant = :note_etudiant "
                                            "WHERE "
                                            "(matricule = :matricule) "
                                            "AND "
                                            "(num_mat = :num_mat) "
                                            "AND "
                                            "(an_academiq = :an_academiq)");

                requeteModification.bindValue(":note_etudiant", ui->spinBoxNouvelleNote->value());
                requeteModification.bindValue(":matricule", ui->comboBoxMatriculeEtudiant->currentText().toInt());
                requeteModification.bindValue(":num_mat", num_mat);
                requeteModification.bindValue(":an_academiq", ui->comboBoxAnneeAcademique->currentText());

                requeteModification.exec();

                QMessageBox::information(this, "Note modifiée",
                                         "La note de l'étudiant ayant le matricule "+
                                         ui->comboBoxMatriculeEtudiant->currentText()+
                                         " a été bien modifiée");
            }
        }

        deconnecterBaseDeDonnee();
    }
}

void FenetreModifierNote::actualiserListeMatiere()
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

void FenetreModifierNote::actualiserListeEtudiant()
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

FenetreModifierNote::~FenetreModifierNote()
{
    delete ui;
}
