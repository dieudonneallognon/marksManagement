#include "fenetrelistemembreadministration.h"
#include "ui_fenetrelistemembreadministration.h"

#include <QMessageBox>

FenetreListeMembreAdministration::FenetreListeMembreAdministration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenetreListeMembreAdministration)
{
    ui->setupUi(this);

    afficherListeMembreAdministration();

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualiserListeMembreAdminitration()));
    timer->start();
}

void FenetreListeMembreAdministration::afficherListeMembreAdministration()
{
    ui->labelNomMembreAdministration->setText("NOMS\n\n");
    ui->labelPrenomMembreAdministration->setText("PRENOMS\n\n");
    ui->labelPrivilegeMembreAdministration->setText("PRIVILEGES\n\n");

    connecterBaseDeDonnee();

    QSqlQuery requete;

    requete.prepare("SELECT * FROM mbreadministration");
    requete.exec();

    while (requete.next()) {
        ui->labelNomMembreAdministration->setText(ui->labelNomMembreAdministration->text()+
                                                  requete.value("nom").toString()+"\n");

        ui->labelPrenomMembreAdministration->setText(ui->labelPrenomMembreAdministration->text()+
                                                     requete.value("prenom").toString()+"\n");

        if(requete.value("id").toInt() == 1){
            ui->labelPrivilegeMembreAdministration->setText(ui->labelPrivilegeMembreAdministration->text()+
                                                            "Super-Administrateur\n");
        }
        else {
            ui->labelPrivilegeMembreAdministration->setText(ui->labelPrivilegeMembreAdministration->text()+
                                                            "Membre de l'Administration\n");
        }
    }

    deconnecterBaseDeDonnee();
}

void FenetreListeMembreAdministration::actualiserListeMembreAdminitration()
{
    afficherListeMembreAdministration();
}

FenetreListeMembreAdministration::~FenetreListeMembreAdministration()
{
    delete ui;
}
