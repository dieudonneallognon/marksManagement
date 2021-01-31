#ifndef FENETRESUPPRIMERETUDIANT_H
#define FENETRESUPPRIMERETUDIANT_H

#include <QWidget>
#include "basededonnee.h"
#include <QTimer>

namespace Ui {
class FenetreSupprimerEtudiant;
}

class FenetreSupprimerEtudiant : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreSupprimerEtudiant(QWidget *parent = 0);
    ~FenetreSupprimerEtudiant();

private:
    Ui::FenetreSupprimerEtudiant *ui;

private slots:
    void enfoncerBoutonSupprimerEtudiant();
    void relacherBoutonSupprimerEtudiant();

    void supprimerEtudiant();
    void afficherInfoEtudiant(int i);
    void actualiserListeEtudiant();

    void proposerEtudiant();
};

#endif // FENETRESUPPRIMERETUDIANT_H
