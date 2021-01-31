#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QIcon>
#include <QFile>

#include "fenetrecreationsuperadministrateur.h"
#include "authentification.h"
#include "fenetreajouteramphi.h"
#include "fenetresupprimeramphi.h"
#include "fenetreajouteretudiant.h"
#include "fenetresupprimeretudiant.h"
#include "fenetrevoirnoteetudiant.h"
#include "fenetrevoirlisteetudiant.h"
#include "fenetreajoutermatiere.h"
#include "fenetresupprimermatiere.h"
#include "fenetremodifiernote.h"
#include "fenetremonprofil.h"
#include "fenetreajoutermembreadministration.h"
#include "fenetrelistemembreadministration.h"
#include "fenetresupprimermembreadministration.h"
#include "basededonnee.h"

#define BOUTON_GERER_AMPHI 0
#define BOUTON_GERER_ETUDIANT 1
#define BOUTON_GERER_MATIERE 2
#define BOUTON_GERER_NOTE 3
#define BOUTON_ESPACE_MEMBRE_ADMINISTRATION 4
#define BOUTON_DECONNEXION 5

namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QWidget
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = nullptr);
    ~FenetrePrincipale();

protected:
    void closeEvent(QCloseEvent* event);
    //    void resizeEvent(QResizeEvent* event);

private:
    Ui::FenetrePrincipale *ui;
    FenetreCreationSuperAdministrateur* fenetreCreationSuperAdministrateur;
    Authentification* fenetreAuthentification;
    FenetreAjouterAmphi* fenetreAjouterAmphi;
    FenetreSupprimerAmphi* fenetreSupprimerAmphi;
    FenetreAjouterEtudiant* fenetreAjouterEtudiant;
    FenetreVoirListeEtudiant* fenetreVoirListeEtudiant;
    FenetreSupprimerEtudiant* fenetreSupprimerEtudiant;
    FenetreAjouterMatiere* fenetreAjouterMatiere;
    FenetreSupprimerMatiere* fenetreSupprimerMatiere;
    FenetreVoirNoteEtudiant* fenetreVoirNoteEtudiant;
    FenetreModifierNote* fenetreModifierNote;
    FenetreMonProfil* fenetreMonProfil;
    FenetreAjouterMembreAdministration* fenetreAjouterMembreAdministration;
    FenetreListeMembreAdministration* fenetreListeMembreAdministration;
    FenetreSupprimerMembreAdministration* fenetreSupprimerMembreAdministration;

    QString nomUtilisateur;
    QString prenomUtilisateur;
    QString loginUtilisateur;
    QString motDePasse;
    QString privilegeUtilisateur;

    bool premiereUtilisation();

signals:
    void envoyerInfoCompte(QString nom, QString prenom, QString login, QString motDePasse);

private slots:

    void enfoncerBoutonGererAmphi();
    void enfoncerBoutonGererEtudiant();
    void enfoncerBoutonGererMatiere();
    void enfoncerBoutonGererNote();
    void enfoncerBoutonEspaceMembreAdministration();
    void enfoncerBoutonDeconnexion();

    void relacherBoutonGererAmphi();
    void relacherBoutonGererEtudiant();
    void relacherBoutonGererMatiere();
    void relacherBoutonGererNote();
    void relacherBoutonEspaceMembreAdministration();
    void relacherBoutonDeconnexion();

    void afficherTabGererAmphi();
    void afficherTabGererEtudiant();
    void afficherTabGererMatiere();
    void afficherTabGererNote();
    void afficherTabEspaceMembreAdministration();
    void deconnexion();

    void afficherInfosCompte(int typeInfo);
    void aZero();
};

#endif // FENETREPRINCIPALE_H
