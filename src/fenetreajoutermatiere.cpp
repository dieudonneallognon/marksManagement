#include "fenetreajoutermatiere.h"
#include "ui_fenetreajoutermatiere.h"

FenetreAjouterMatiere::FenetreAjouterMatiere(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreAjouterMatiere)
{
    ui->setupUi(this);
    /*---------------------------------connect enfoncerBouton----------------------------*/

    connect(ui->boutonAjouterMatiere, SIGNAL(pressed()), this, SLOT(enfoncerBoutonAjouterMatiere()));

    /*--------------------------------connect relacherBouton-----------------------------*/

    connect(ui->boutonAjouterMatiere, SIGNAL(released()), this, SLOT(relacherBoutonAjouterMatiere()));

    connect(ui->boutonAjouterMatiere, SIGNAL(clicked()), this, SLOT(ajouterMatiere()));
}


/*-------------------------------------------Définition des slots enfoncerBouton --------------------------------------*/

void FenetreAjouterMatiere::enfoncerBoutonAjouterMatiere(){
    ui->boutonAjouterMatiere->setStyleSheet("QPushButton { background-color: #254076; }");
}


/*----------------------------------------Définition des slots relacherBouton------------------------------------*/

void FenetreAjouterMatiere::relacherBoutonAjouterMatiere(){
    ui->boutonAjouterMatiere->setStyleSheet("QPushButton { background-color: rgb(55, 94, 173); }");
    ui->boutonAjouterMatiere->setStyleSheet("QPushButton:hover { background-color: rgb(47, 80, 147); }");
}

FenetreAjouterMatiere::~FenetreAjouterMatiere()
{
    delete ui;
}

/*----------------------------------------Définition du slot AjouterMatiere-------------------------------------*/

bool FenetreAjouterMatiere::nomMatiereCorrect(QString nomMatiere)
{
    QRegExp regexNomMatiere ("^[0-9A-Za-z ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØŒÙÚÛÜÝŸÞßàáâãäåæçèéêëìíîïðñòóôõöøœùúûüýþÿ-+#]{2,}$");
    QRegExpValidator vldtr (regexNomMatiere, this);

    int pos = 0;
    if (vldtr.validate(nomMatiere, pos) != QValidator::Acceptable) {
        return false;
    }
    else {
        return  true;
    }
}

void FenetreAjouterMatiere::ajouterMatiere()
{

    if (ui->lineEditNomMatiere->text() == "" ){
        QMessageBox::information(this, "Champs manquants", "Veuillez remplir tous les champs !");
    }
    else if (!nomMatiereCorrect(ui->lineEditNomMatiere->text())) {
        QMessageBox::critical(this, "Nom incorrect", "Le nom de la matière ne doit contenir que des lettres, "
                                                     "des chiffres, un tiret des caracteres (+ ou #) "
                                                     "ou un espace et doit être long d'au moins 2 caractères!");
    }
    else if (!matiereExiste(ui->lineEditNomMatiere->text())){

        connecterBaseDeDonnee();

        QSqlQuery requete;

        requete.prepare("INSERT INTO matiere (nom_mat) VALUES( :nom_mat)");
        requete.bindValue(":nom_mat", ui->lineEditNomMatiere->text());

        requete.exec();

        deconnecterBaseDeDonnee();


        QMessageBox::information(this, "Matiere ajoutée", "La matiere "+ui->lineEditNomMatiere->text()+" a été bien ajouté");
    }
}


bool FenetreAjouterMatiere::matiereExiste(QString matiere)
{
    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT nom_mat FROM matiere");
    requete.exec();

    while (requete.next()) {
        if (requete.value("nom_mat").toString() == matiere){
            QMessageBox::warning(this, "Ajout impossible", "La matière "+requete.value("nom_mat").toString()+" exite déjà");
            deconnecterBaseDeDonnee();
            return true;
        }
    }
    deconnecterBaseDeDonnee();
    return false;
}
