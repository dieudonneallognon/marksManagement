#ifndef BASEDEDONNEE_H
#define BASEDEDONNEE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

bool creerBaseDeDonne();
bool connecterBaseDeDonnee();
void deconnecterBaseDeDonnee();

bool superAdminExiste();

#endif // BASEDEDONNEE_H
