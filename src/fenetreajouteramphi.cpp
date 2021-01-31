#include "fenetreajouteramphi.h"
#include "ui_fenetreajouteramphi.h"

FenetreAjouterAmphi::FenetreAjouterAmphi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreAjouterAmphi)
{
    ui->setupUi(this);

    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonAjouterAmphi, SIGNAL(pressed()), this, SLOT(enfoncerBoutonAjouterAmphi()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonAjouterAmphi, SIGNAL(released()), this, SLOT(relacherBoutonAjouterAmphi()));

    /*-----------------------------------Autres connect----------------------------*/

    connect(ui->boutonAjouterAmphi, SIGNAL(clicked()), this, SLOT(ajouterAmphi()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------*/

void FenetreAjouterAmphi::enfoncerBoutonAjouterAmphi(){
    ui->boutonAjouterAmphi->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreAjouterAmphi::relacherBoutonAjouterAmphi(){
    ui->boutonAjouterAmphi->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonAjouterAmphi->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

FenetreAjouterAmphi::~FenetreAjouterAmphi()
{
    delete ui;
}

/*----------------------------------------Définition du slot ajouterAmphi------------------------------------------*/

bool FenetreAjouterAmphi::nomAmphiCorrect(QString nomAmphi)
{
    QRegExp regexNomAmphi ("^[0-9A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ- ]{2,}$");
    QRegExpValidator vldtr (regexNomAmphi, this);

    int pos = 0;
    if (vldtr.validate(nomAmphi, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}

void FenetreAjouterAmphi::ajouterAmphi()
{

    if (ui->lineEditNomAmphi->text() == "" ){
        QMessageBox::critical(this, "Champs manquants", "Veuillez remplir tous les champs !");
    }
    else if (!nomAmphiCorrect(ui->lineEditNomAmphi->text())) {
        QMessageBox::critical(this, "Nom incorrect", "Le nom de l'amphi ne doit contenir que des lettres, un tiret "
                                                     "ou un espace et doit être long d'au moins 2 caractères!");
    }
    else if (!amphiExiste(ui->lineEditNomAmphi->text())){
        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("INSERT INTO amphi (nom_amphi, nb_place) VALUES(:nom_amphi, :nb_place)");
        requete.bindValue(":nom_amphi", ui->lineEditNomAmphi->text());
        requete.bindValue(":nb_place", ui->spinBoxNombrePlaceAmphi->value());

        requete.exec();

        deconnecterBaseDeDonnee();

        QMessageBox::information(this, "Amphi ajouté", "L' amphi "+ui->lineEditNomAmphi->text()+" a été bien ajouté");
    }
}

bool FenetreAjouterAmphi::amphiExiste(QString amphi)
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT nom_amphi FROM amphi");

    requete.exec();


    while (requete.next()) {
        if (requete.value("nom_amphi").toString() == amphi){
            QMessageBox::warning(this, "Ajout impossible","L'amphi "+requete.value("nom_amphi").toString()+" exite déjà");
            deconnecterBaseDeDonnee();
            return true;
        }
    }
    deconnecterBaseDeDonnee();
    return false;
}
