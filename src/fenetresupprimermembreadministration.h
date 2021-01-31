#ifndef FENETRESUPPRIMERMEMBREADMINISTRATION_H
#define FENETRESUPPRIMERMEMBREADMINISTRATION_H

#include <QWidget>
#include <QTimer>

#include "authentification.h"

namespace Ui {
class FenetreSupprimerMembreAdministration;
}

class FenetreSupprimerMembreAdministration : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreSupprimerMembreAdministration(QWidget *parent = 0);
    ~FenetreSupprimerMembreAdministration();

private:
    Ui::FenetreSupprimerMembreAdministration *ui;
    Authentification* fenetreAuthentification;
    void proposerMembreAdministration();

private slots:
    void enfoncerBoutonSupprimerMembreAdministration();
    void relacherBoutonSupprimerMembreAdministration();
    void afficherFenetreAuthentification(int f);
    void supprimerMembreAdministration();

    void afficherInfoMembreAdministration(int i);
    void actualiserListeMembreAdministration();
};

#endif // FENETRESUPPRIMERMEMBREADMINISTRATION_H
