#ifndef FENETREMODIFIERNOTE_H
#define FENETREMODIFIERNOTE_H

#include <QWidget>
#include <QDate>
#include <QMessageBox>
#include <QTimer>

#include <basededonnee.h>

namespace Ui {
class FenetreModifierNote;
}

class FenetreModifierNote : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreModifierNote(QWidget *parent = 0);
    ~FenetreModifierNote();

private:
    Ui::FenetreModifierNote *ui;
    void proposerMatricule();
    void proposerMatiere();
    void proposerAnneeAcademique();
    int recupererNumeroMatiere();

private slots:
    void enfoncerBoutonModifierNote();
    void relacherBoutonModifierNote();
    void modifierNoteEtudiant();
    void actualiserListeMatiere();
    void actualiserListeEtudiant();

};

#endif // FENETREMODIFIERNOTE_H
