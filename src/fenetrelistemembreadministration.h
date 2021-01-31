#ifndef FENETRELISTEMEMBREADMINISTRATION_H
#define FENETRELISTEMEMBREADMINISTRATION_H

#include <QWidget>
#include "basededonnee.h"
#include <QTimer>

namespace Ui {
class FenetreListeMembreAdministration;
}

class FenetreListeMembreAdministration : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreListeMembreAdministration(QWidget *parent = 0);
    ~FenetreListeMembreAdministration();

private:
    Ui::FenetreListeMembreAdministration *ui;

    void afficherListeMembreAdministration();

private slots:
    void actualiserListeMembreAdminitration();
};

#endif // FENETRELISTEMEMBREADMINISTRATION_H
