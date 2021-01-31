#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QCloseEvent>

#include "basededonnee.h"

#define AUTHENTIFICATION 1
#define AUTHENTIFICATION_PRINCIPALE 5
#define AUTHENTIFICATION_ESPACE_MEMBRE 6

namespace Ui {
class Authentification;
}

class Authentification : public QWidget
{
    Q_OBJECT

public:
    explicit Authentification(QWidget *parent = nullptr);
    ~Authentification();

    QString getNom() const;
    QString getPrenom() const;
    QString getPrivilege() const;
    QString getLogin() const;
    QString getMotDePasse() const;

    void setTypeAuthentification (int type);

protected:
    void closeEvent(QCloseEvent* event);

private:
    Ui::Authentification *ui;

    QString nomUtilisateur;
    QString prenomUtilisateur;
    QString motDePasseUtilisateur;
    QString privilegeUtilisateur;

    int typeAuthentification;

    bool utilisateurExiste();

signals:
    void envoyerInfosCompte(int);
    void rediriger();
    void demandefermeturePageSuperAdministrateur();

private slots:
    void enfoncerBoutonValider();
    void enfoncerBoutonVoirMotDePasse();

    void relacherBoutonValider();
    void relacherBoutonVoirMotDePasse();

    void authentifier();
};

#endif // AUTHENTIFICATION_H
