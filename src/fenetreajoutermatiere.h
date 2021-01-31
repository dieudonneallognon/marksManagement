#ifndef FENETREAJOUTERMATIERE_H
#define FENETREAJOUTERMATIERE_H

#include <QWidget>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>

#include "basededonnee.h"

namespace Ui {
class FenetreAjouterMatiere;
}

class FenetreAjouterMatiere : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreAjouterMatiere(QWidget *parent = 0);
    ~FenetreAjouterMatiere();

private:
    Ui::FenetreAjouterMatiere *ui;

    bool matiereExiste(QString matiere);
    bool nomMatiereCorrect(QString nomMatiere);

private slots:
    void enfoncerBoutonAjouterMatiere();
    void relacherBoutonAjouterMatiere();

    void ajouterMatiere();
};

#endif // FENETREAJOUTERMATIERE_H
