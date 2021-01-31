#include "basededonnee.h"

static QSqlDatabase baseDeDonnee = QSqlDatabase::addDatabase("QSQLITE");

bool creerBaseDeDonne()
{
    baseDeDonnee.setDatabaseName("gestionNotes.sdb");
    if(!baseDeDonnee.open()){
        return false;
    }

    QSqlQuery requete;

    requete.prepare("CREATE TABLE `amphi` ("
                    "`nom_amphi` varchar(100) NOT NULL,"
                    "`nb_place` int(11) DEFAULT NULL,"
                    "PRIMARY KEY (`nom_amphi`)"
                    ");");

    requete.exec();

    requete.prepare("CREATE TABLE `etudiant` ("
                    "`matricule` int(11) NOT NULL,"
                    "`nom` varchar(50) DEFAULT NULL,"
                    "`prenom` varchar(50) DEFAULT NULL,"
                    "`date_naissance` date DEFAULT NULL,"
                    "PRIMARY KEY (`matricule`)"
                    ");");

    requete.exec();

    requete.prepare("CREATE TABLE `matiere` ("
                    "`num_mat` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "`nom_mat` varchar(50) DEFAULT NULL"
                    ");");

    requete.exec();

    requete.prepare("CREATE TABLE `annee_academique` ("
                    "`an_academiq` varchar(10) NOT NULL,"
                    "PRIMARY KEY (`an_academiq`)"
                    ");");

    requete.exec();

    requete.prepare("CREATE TABLE `note` ("
                    "`note_etudiant` int(5) NOT NULL,"
                    "`matricule` int(11) NOT NULL,"
                    "`num_mat` varchar(20) NOT NULL,"
                    "`an_academiq` varchar(10) NOT NULL,"
                    "PRIMARY KEY (`matricule`,`num_mat`,`an_academiq`),"
                    "FOREIGN KEY (`matricule`) REFERENCES etudiant(matricule),"
                    "FOREIGN KEY  (`num_mat`) REFERENCES matiere(num_mat),"
                    "FOREIGN KEY  (`an_academiq`) REFERENCES annee_academique(an_academiq)"
                    ");");

    requete.exec();

    requete.prepare("CREATE TABLE `inscrire` ("
                    "`nom_amphi` varchar(100) NOT NULL,"
                    "`an_academiq` varchar(10) NOT NULL,"
                    "`matricule` int(11) NOT NULL,"
                    "PRIMARY KEY (`an_academiq`,`matricule`),"
                    "FOREIGN  KEY  (`nom_amphi`) REFERENCES amphi(nom_amphi),"
                    "FOREIGN  KEY  (`an_academiq`) REFERENCES annee_academique(an_academiq),"
                    "FOREIGN  KEY  (`matricule`) REFERENCES etudiant(matricule)"
                    ");");

    requete.exec();

    requete.prepare("CREATE TABLE `mbreadministration` ("
                    "`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                    "`nom` varchar(50) DEFAULT NULL,"
                    "`prenom` varchar(50) DEFAULT NULL,"
                    "`login` varchar(100) NOT NULL,"
                    "`mot_de_passe` varchar(100) NOT NULL,"
                    "UNIQUE  (`login`)"
                    ");");

    requete.exec();

    return true;
}


bool connecterBaseDeDonnee()
{
    baseDeDonnee.setDatabaseName("gestionNotes.sdb");
    if(!baseDeDonnee.open()){
        return false;
    }
    return true;
}

void deconnecterBaseDeDonnee()
{
    QSqlDatabase::removeDatabase("gestionNotes.sdb");
}

bool superAdminExiste()
{
    baseDeDonnee.setDatabaseName("gestionNotes.sdb");

    QSqlQuery requete;

    requete.prepare("SELECT count(id) as nbr FROM mbreadministration");
    requete.exec();
    requete.next();
    if(requete.value("nbr").toInt() == 0){
        return false;
    }
    else {
        return true;
    }
}
