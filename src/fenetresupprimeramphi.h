#ifndef FENETRESUPPRIMERAMPHI_H
#define FENETRESUPPRIMERAMPHI_H

#include <QWidget>
#include "basededonnee.h"
#include <QTimer>

namespace Ui {
class FenetreSupprimerAmphi;
}

class FenetreSupprimerAmphi : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreSupprimerAmphi(QWidget *parent = 0);
    ~FenetreSupprimerAmphi();

private:
    Ui::FenetreSupprimerAmphi *ui;

private slots:
    void enfoncerBoutonSupprimerAmphi();
    void relacherBoutonSupprimerAmphi();

    void supprimerAmphi();
    void AfficherInfoAmphi(int i);
    void actualiserListeAmphi();

    void proposerAmphi();
};

#endif // FENETRESUPPRIMERAMPHI_H
