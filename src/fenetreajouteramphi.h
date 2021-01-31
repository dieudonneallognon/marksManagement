#ifndef FENETREAJOUTERAMPHI_H
#define FENETREAJOUTERAMPHI_H

#include <QWidget>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>

#include "basededonnee.h"

#define AJOUTER_AMPHI 0

namespace Ui {
class FenetreAjouterAmphi;
}

class FenetreAjouterAmphi : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreAjouterAmphi(QWidget *parent = nullptr);
    ~FenetreAjouterAmphi();

private:
    Ui::FenetreAjouterAmphi *ui;
    bool nomAmphiCorrect(QString nomAmphi);

private slots:
    void enfoncerBoutonAjouterAmphi();
    void relacherBoutonAjouterAmphi();

    void ajouterAmphi();
    bool amphiExiste(QString amphi);
};

#endif // FENETREAJOUTERAMPHI_H
