#include <iostream>

#include <Monde.h>
#include "Vecteur2D.h"
#include "dessinateur_java/DessinateurMondeAWTJAVA.h"
#include "visitor/VisitorDessinateur.h"
#include <VisitorDessinateurFactory.h>

#ifndef ADRESSESERVEURDEFAUT
#define ADRESSESERVEURDEFAUT "127.0.0.1"
#endif

#ifndef PORTSERVEURDEFAUT
#define PORTSERVEURDEFAUT 8091
#endif

#ifndef LARGEURDEFAUT
#define LARGEURDEFAUT 1920
#endif

#ifndef HAUTEURDEFAUT
#define HAUTEURDEFAUT 1080
#endif

using namespace std;

FenetreMonde * lanceApplicationParDefaut(const char *titre = "Application Graphique", const char * legende = "",
                                         const Vecteur2D<double> & coinBG = Vecteur2D<double>(-1,-10),
                                         const Vecteur2D<double> & coinHD = Vecteur2D<double>(10,1)) {
    DessinateurMondeAWTJAVA dessinateur(ADRESSESERVEURDEFAUT, PORTSERVEURDEFAUT);
    return dessinateur.ouvreFenetre(coinBG, coinHD, 0, 50,
                                    LARGEURDEFAUT, HAUTEURDEFAUT,
                                    titre, legende);
}

int main() {
    Monde monde;
    auto & liste_stations = monde.getListeStations();

    auto fenetre = lanceApplicationParDefaut();

    auto factory = VisitorDessinateurFactory(fenetre);

    VisitorDessinateurMonde dessinateurMonde(fenetre,
                                             factory.getVisitorStationDefault(),
                                             factory.getVisitorConnexionTamise());

    monde.visit(&dessinateurMonde);

    fenetre->listen();
    delete fenetre;
    return 0;
}
