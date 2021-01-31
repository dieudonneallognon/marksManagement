#ifndef FENETREAJOUTERMEMBREADMINISTRATION_H
#define FENETREAJOUTERMEMBREADMINISTRATION_H

#include <QWidget>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>

#include "authentification.h"
#include "basededonnee.h"

namespace Ui {
class FenetreAjouterMembreAdministration;
}

class FenetreAjouterMembreAdministration : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreAjouterMembreAdministration(QWidget *parent = 0);
    ~FenetreAjouterMembreAdministration();

protected:
    void mousePressEvent(QMouseEvent* mouseEvent);

private:
    Ui::FenetreAjouterMembreAdministration *ui;
    Authentification* fenetreAuthentification;

    int idUtilisateur;

    bool nomMembreCorrect(QString nomMembre);
    bool prenomMembreCorrect(QString prenomMembre);

signals:
    void clicked_left();

private slots:
    void enfoncerBoutonAjouterMembreAdministration();
    void relacherBoutonAjouterMembreAdministration();
    void afficherFenetreAuthentification(int f);

    void ajouterMembreAdministration();
    bool MbreAdministrationExiste(QString MbreAdministration);
};

#endif // FENETREAJOUTERMEMBREADMINISTRATION_H
