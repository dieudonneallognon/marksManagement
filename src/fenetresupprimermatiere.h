#ifndef FENETRESUPPRIMERMATIERE_H
#define FENETRESUPPRIMERMATIERE_H

#include <QWidget>
#include <QTimer>

#include "basededonnee.h"

namespace Ui {
class FenetreSupprimerMatiere;
}

class FenetreSupprimerMatiere : public QWidget
{
    Q_OBJECT

public:
    explicit FenetreSupprimerMatiere(QWidget *parent = 0);
    ~FenetreSupprimerMatiere();

private:
    Ui::FenetreSupprimerMatiere *ui;

private slots:
    void enfoncerBoutonSupprimerMatiere();
    void relacherBoutonSupprimerMatiere();

    void supprimerMatiere();
    void actualiserListeMatiere();

};

#endif // FENETRESUPPRIMERMATIERE_H
