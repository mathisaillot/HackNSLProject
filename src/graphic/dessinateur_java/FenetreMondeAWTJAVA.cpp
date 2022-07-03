/*
 *      Author: Dominique Michel
 */
#include <sstream>
#include "Erreur.h"
#include "FenetreMondeAWTJAVA.h"

using namespace std;

/**
 * DONNEES : s, espace
 * RESULTAT : trimmed, la copie partielle de s dans laquelle on a supprimé les éventuels espaces de début et de fin,
 * TACHE : fait la même chose que la fct trim de JAVA
 *
 * HYPOTHESE : on suppose que trimmed est assez grande pour contenir le résultat
 * */
void trim( const char * s, char * trimmed, const char espace)
{
    const char * d, * f;
    int l = strlen(s);

    for (     d = s; *d == espace; ++d);

    for ( f = s+l-1; f >= s && *f == espace; --f);

    if (f < d) trimmed[0]  = '\0';
    else
    {
        int n = f-d+1;
        strncpy(trimmed,d,n);
        trimmed[n] = '\0';
    }
}
/**
 * DONNEES : s, espace
 * RESULTAT : la copie partielle de s dans laquelle on a supprimé les éventuels espaces de début et de fin,
 * TACHE : fait la même chose que la fct trim de JAVA
 *
 * */
inline const string trim( const char * s, const char espace = ' ')
{
    int l = strlen(s);
    char * trimmed = new char [l+1];
    trim(s,trimmed,espace);
    string resultat = (string)trimmed;
    delete [] trimmed;
    return resultat;
}

/**
 * DONNEES : s, espace
 * RESULTAT : la copie partielle de s dans laquelle on a supprimé les éventuels espaces de début et de fin,
 * TACHE : fait la même chose que la fct trim de JAVA
 *
 * */
inline const string trim( const string & s, const char espace = ' ') { return trim(s.c_str(),espace);}


/* petite méthode utile pour factoriser du code dans les méthode suivantes */

void executeRequete(const ostringstream &os, ClientTCPString &client, const string &messageErreur) {
    string requete = os.str();
    bool ok = client.envoie(requete);

    if (!ok) throw Erreur(messageErreur);
}

//class FenetreMondeAWTJAVA : Fenetre

FenetreMondeAWTJAVA::
FenetreMondeAWTJAVA(const string &adresseServeur, const int portServeur,
                    const Vecteur2D<double> &coinBG, const Vecteur2D<double> &coinHD,
                    const int gauche, const int haut, const int largeur, const int hauteur,
                    const string &titre, const string &legende) : client(adresseServeur, portServeur), parseurint() {
    ostringstream os;

    os << "fenetre " << coinBG << " " << coinHD << " " << gauche << " " << haut << " " << largeur << " " << hauteur;

    executeRequete(os, client,
                   "Dans FenetreMondeAWTJAVA::FenetreMondeAWTJAVA(...) : échec d'envoi de la requête des coordonnées des fenêtres monde-écran");

    bool ok = client.envoie(titre);

    if (!ok) throw Erreur("Dans FenetreMondeAWTJAVA::FenetreMondeAWTJAVA(...) : échec d'envoi du titre de la fenêtre");

    ok = client.envoie(legende);

    if (!ok)
        throw Erreur("Dans FenetreMondeAWTJAVA::FenetreMondeAWTJAVA(...) : échec d'envoi de la légende de la fenêtre");
}

///*virtual*/ void FenetreMondeAWTJAVA::dessineSegment( const int x1, const int y1, const int x2, const int y2, const Couleur & couleur, const int epaisseur)

/*virtual*/ void FenetreMondeAWTJAVA::dessineSegment(const Vecteur2D<double> &A1, const Vecteur2D<double> &A2, const Couleur &couleur,
                                                     const int epaisseurTraitEnPixel) {
    ostringstream os;

    os << "segment " << A1 << " " << A2 << " " << couleur << " " << epaisseurTraitEnPixel;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::dessineSegment(...)");

}

///*virtual*/ void FenetreMondeAWTJAVA::dessineMessage( const string & message, const int x, const int y, const Couleur & couleur)

/*virtual*/ void
FenetreMondeAWTJAVA::dessineMessage(const string &message, const Vecteur2D<double> &A, const Couleur &couleur) {
    ostringstream os;

    os << "message " << A << " " << couleur << " " << message;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::dessineMessage(...)");
}


///*virtual*/ void FenetreMondeAWTJAVA::dessineCercle( const Vecteur2D<double>&  centre, const double & rayon, const Couleur & couleur, const int epaisseur)
/*virtual*/ void
FenetreMondeAWTJAVA::dessineCercle(const Vecteur2D<double> &centre, const double &rayon, const Couleur &couleur,
                                   const int epaisseurTraitEnPixel) {
    ostringstream os;

    os << "cercle " << centre << " " << rayon << " " << couleur << " " << epaisseurTraitEnPixel;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::dessineCercle(...)");

}


/*
 * Pour factoriser le code des 2 méthodes suivantes
 *
 * */
template<class T>
void executeRequeteDisqueOuPoint(ClientTCPString &client,
                                 const string &typeForme, const Vecteur2D<double> &centre, const T &rayon,
                                 const Couleur &couleur, const string &messageErreur) {
    ostringstream os;

    os << typeForme << " " << centre << " " << rayon << " " << couleur;

    executeRequete(os, client, messageErreur);

}

//virtual void                         dessineDisque( const Vecteur2D<double>&  centre, const double & rayon, const Couleur & couleur = (Couleur)"black");
/*virtual*/ void
FenetreMondeAWTJAVA::dessineDisque(const Vecteur2D<double> &centre, const double &rayon, const Couleur &couleur) {
    executeRequeteDisqueOuPoint(client, "disque", centre, rayon, couleur,
                                "Dans FenetreMondeAWTJAVA::dessineDisque(...)");
}
/*{
ostringstream os;

os << "disque " << centre << " "  << rayon << " " << couleur;

executeRequete( os, client, "Dans FenetreMondeAWTJAVA::dessineDisque(...)");
}*/


/*virtual*/ void
FenetreMondeAWTJAVA::dessinePoint(const Vecteur2D<double> &centre, const int &rayonEnPixel, const Couleur &couleur) {
    executeRequeteDisqueOuPoint(client, "point", centre, rayonEnPixel, couleur,
                                "Dans FenetreMondeAWTJAVA::dessinePoint(...)");
}

/*{
ostringstream os;

os << "point " << centre << " " << rayonEnPixel << " " << couleur;

executeRequete(os, client, "Dans FenetreMondeAWTJAVA::dessinePoint(...)");
}*/


/**
 * pour le contrat : cf. classe FenetreMonde
 *
 * Format de la requête envoyée au serveur :
 * Exemple : on veut colorier en rouge le triangle de coordonnées monde : A(2,1), B(5,2), C(4,4)
 *
 * alors on envoie la requête :
 *
 *              "polygone 2 (2,1) (5,2) (4,4) rouge"
 *
 *  Notez bien que le 2ème paramètre est l'indice du dernier sommet du tableau sommets
 * */
/*virtual*/ void
FenetreMondeAWTJAVA::dessinePolygonePlein(const Vecteur2D<double> sommets[], const int m, const Couleur &couleurInterieur) {
    ostringstream os;

    os << "polygone " << m << " ";

    int i;

    for (i = 0; i <= m; ++i, ++sommets) {
        os << *sommets << " ";
    }

    os << couleurInterieur;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::dessinePolygonePlein(...)");

}


/**
 * TACHE : efface tous les dessins éventuellement visibles dans la fenêtre
 * */
/*virtual*/ void FenetreMondeAWTJAVA::effaceTout() {
    ostringstream os;

    os << "efface";

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::effaceTout()");
}


/*virtual*/ void FenetreMondeAWTJAVA::ferme() {
    client.envoie("close");
    client.ferme();
}

FenetreMondeAWTJAVA::~FenetreMondeAWTJAVA() {
    client.ferme();
}

void FenetreMondeAWTJAVA::setGroupeDessin(string nom) {
    ostringstream os;

    os << "groupe " << nom;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::setGroupeDessin()");
}

int FenetreMondeAWTJAVA::creerMenu(int n, string *labels) {
    ostringstream os;

    os << "menu " << n;

    for (int i = 0; i < n; ++i) {
        os << " \"" << labels[i] << "\"";
    }

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::setGroupeDessin()");

    return parseurint(client.recoit());
}

bool FenetreMondeAWTJAVA::ping() {
    bool ok = client.envoie("ping");
    if  (!ok) return false;
    string reponse = trim(client.recoit());
    return reponse == "pong";
}

void FenetreMondeAWTJAVA::addBouton(int code, string label) {
    ostringstream os;

    os << "bouton " << code << " " << label;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::addBouton()");
}

void FenetreMondeAWTJAVA::removeBouton(int code) {
    string label;
    addBouton(code, label);
}

string FenetreMondeAWTJAVA::listen() {
    bool ok = client.envoie("listen");
    if  (!ok) return "-1";
    return trim(client.recoit());
}

bool FenetreMondeAWTJAVA::questionUtilisateurBinaire(string &question) {
    string reponse = questionUtilisateur(question, 0);
    return parseurint(reponse);
}

string FenetreMondeAWTJAVA::questionUtilisateurTexte(string &question) {
    return questionUtilisateur(question, 1);
}

string FenetreMondeAWTJAVA::questionUtilisateur(string &question, int code) {
    ostringstream os;

    os << "userinput " << code << " " << question;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::questionUtilisateur()");
    return trim(client.recoit());
}

void FenetreMondeAWTJAVA::removeGroupe(string nom) {
    ostringstream os;

    os << "efface " << nom;

    executeRequete(os, client, "Dans FenetreMondeAWTJAVA::removeGroupe)");
}







