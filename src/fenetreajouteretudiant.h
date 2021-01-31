#ifndef FENETREAJOUTERETUDIANT_H
#define FENETREAJOUTERETUDIANT_H

#include <QWidget>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <QDate>
#include <QTimer>

#include "basededonnee.h"

namespace Ui {
class FenetreAjouterEtudiant;
}

class FenetreAjouterEtudiant : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreAjouterEtudiant(QWidget *parent = 0);
    ~FenetreAjouterEtudiant();

private:
    Ui::FenetreAjouterEtudiant *ui;

    bool nomEtudiantCorrect(QString nomEtudiant);
    bool prenomEtudiantCorrect(QString prenomEtudiant);

    bool etudiantExiste(int matricule);
    bool anneeAcademiqueExiste(QString);
    bool inscriptionExiste(int matricule, QString anneeAcademique);

    void proposerAnneeAcademique();
    void proposerAmphi();

    void ajouterInscription();
    void ajouterAnneeAcademique();
    bool anneeAcademiqueCorrect(QString anneeAcademique) ;

private slots:
    void enfoncerBoutonAjouterEtudiant();
    void relacherBoutonAjouterEtudiant();

    void ajouterEtudiant();
    void actualiserListeAmphi();
};

#endif // FENETREAJOUTERETUDIANT_H
