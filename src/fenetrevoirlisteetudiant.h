#ifndef FENETREVOIRLISTEETUDIANT_H
#define FENETREVOIRLISTEETUDIANT_H

#include <QWidget>
#include <QDate>
#include <QTableWidget>
#include <QMessageBox>
#include <QTimer>

#include <basededonnee.h>


namespace Ui {
class FenetreVoirListeEtudiant;
}

class FenetreVoirListeEtudiant : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreVoirListeEtudiant(QWidget *parent = 0);
    ~FenetreVoirListeEtudiant();

private:
    Ui::FenetreVoirListeEtudiant *ui;

    void proposerAmphi();
    void proposerAnneeAcademique();


private slots:

    void enfoncerBoutonVoirListeEtudiant();
    void relacherBoutonVoirListeEtudiant();
    void afficherListeEtudiant();
    void actualiserListeAmphi();
};

#endif // FENETREVOIRLISTEETUDIANT_H
