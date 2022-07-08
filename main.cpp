#include <iostream>

#include <Monde.h>
#include <VisitorDessinateurFactory.h>
#include <JsonLoader.hpp>
#include <OutilsFichiers.h>
#include <GameInstance.h>
#include <DessinateurMondeAWTJAVA.h>
#include <GameState.h>

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

    GameState state = newGameState();

    int move_id = 24;

    cout << "Test codage move : id = " << move_id << " no bonus" << endl;

    int move_number = 0;

    state[move_number] = getCodeFromID(move_id);

    cout << " codage " << state[move_number] << endl;
    cout << "check move : " << checkMove(state, move_number) << endl;
    cout << "check bonus : " << checkBonus(state, move_number) << endl;
    cout << "get move id : " << getIDmove(state, move_number) << endl << endl;

    int bonus_id = 112;

    cout << "Test codage move : id = " << move_id << " bonus : " << bonus_id << endl;

    move_number ++;

    state[move_number] = getCodeFromID(move_id, bonus_id);

    cout << " codage " << state[move_number] << endl;
    cout << "check move : " << checkMove(state, move_number) << endl;
    cout << "check bonus : " << checkBonus(state, move_number) << endl;
    cout << "get move id : " << getIDmove(state, move_number) << endl;
    cout << "get bonus id : " << getIDbonus(state, move_number) << endl;

    delete state;

    string file = getCheminDossierFils(getCheminDossierData(),{"gameinstance", "exemple_instance.json"});

    JsonLoader loader(file);

    auto & json = loader.getData();

    GameInstance instance(json);

    cout << instance << endl;

    Monde monde;
    auto & liste_stations = monde.getListeStations();

    auto fenetre = lanceApplicationParDefaut();

    auto factory = VisitorDessinateurFactory(fenetre);

    VisitorDessinateurMonde dessinateurMonde(fenetre,
                                             factory.getVisitorStationDepart(monde),
                                             factory.getVisitorConnexionTamise());

    monde.visit(&dessinateurMonde);

    fenetre->listen();
    delete fenetre;
    return 0;
}
