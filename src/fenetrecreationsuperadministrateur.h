#ifndef FENETRECREATIONSUPERADMINISTRATEUR_H
#define FENETRECREATIONSUPERADMINISTRATEUR_H

#include <QWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <QRegExp>
#include <QValidator>
#include <QVector>

#include "basededonnee.h"

#define CREATION_SUPER_ADMINISTRATEUR 0

namespace Ui {
class FenetreCreationSuperAdministrateur;
}

class FenetreCreationSuperAdministrateur : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreCreationSuperAdministrateur(QWidget *parent = nullptr);
    ~FenetreCreationSuperAdministrateur();

    QString getNom() const;
    QString getPrenom() const;
    QString getLogin() const;
    QString getMotDePasse() const;

protected:
    void closeEvent(QCloseEvent* event);

private:
    Ui::FenetreCreationSuperAdministrateur *ui;

    bool nomCorrect(QString nom);
    bool prenomCorrect(QString prenom);
    bool loginCorrect(QString login);

signals:
    void envoyerInfosCompte(int);

private slots:
    void enfoncerBoutonValider();
    void enfoncerBoutonVoirMotDePasse();

    void relacherBoutonValider();
    void relacherBoutonVoirMotDePasse();

    void creerSuperAdministrateur();
};

#endif // FENETRECREATIONSUPERADMINISTRATEUR_H
