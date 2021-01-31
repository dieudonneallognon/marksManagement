#ifndef FENETREVOIRNOTEETUDIANT_H
#define FENETREVOIRNOTEETUDIANT_H

#include <QWidget>
#include <QDate>
#include <QTableWidget>
#include <QMessageBox>
#include <QTimer>

#include <basededonnee.h>

namespace Ui {
class FenetreVoirNoteEtudiant;
}

class FenetreVoirNoteEtudiant : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreVoirNoteEtudiant(QWidget *parent = 0);
    ~FenetreVoirNoteEtudiant();

private:
    Ui::FenetreVoirNoteEtudiant *ui;

    void proposerMatricule();
    void proposerMatiere();
    void proposerAnneeAcademique();

private slots:
    void enfoncerBoutonVoirNote();
    void relacherBoutonVoirNote();

    void afficherNoteEtudiant();

    void actualiserListeEtudiant();
    void actualiserListeMatiere();
};

#endif // FENETREVOIRNOTEETUDIANT_H
