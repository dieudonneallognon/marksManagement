#ifndef FENETREMONPROFIL_H
#define FENETREMONPROFIL_H

#include <QWidget>
#include <QValidator>
#include <QVector>
#include <QMessageBox>

#include "basededonnee.h"

namespace Ui {
class FenetreMonProfil;
}

class FenetreMonProfil : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreMonProfil(QWidget *parent = 0);
    ~FenetreMonProfil();

private:
    Ui::FenetreMonProfil *ui;

    QString loginUtilisateur;
    QString nomUtilisateur;
    QString prenomUtilisateur;
    QString motDePasseUtilisateur;

    void afficherProfilUtilistaur();

private slots:
    void enfoncerBoutonChangerMotDePasse();
    void relacherBoutonChangerMotDePasse();

    void modifiermotdepasse();
    void recevoirInfoCompte(QString nom, QString prenom, QString login, QString motDePasse);
};

#endif // FENETREMONPROFIL_H
