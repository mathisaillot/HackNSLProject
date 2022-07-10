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

    int move_id = 0;

    cout << "Test codage move : id = " << move_id << " no bonus" << endl;

    int move_number = 0;

    state[move_number] = getCodeFromID(move_id);

    cout << " codage " << state[move_number] << endl;
    cout << "check move : " << checkMove(state, move_number) << endl;
    cout << "check bonus : " << checkBonus(state, move_number) << endl;
    cout << "get move id : " << getIDmove(state, move_number) << endl << endl;

    int bonus_id = 112;
    move_id = 152;

    cout << "Test codage move : id = " << move_id << " bonus : " << bonus_id << endl;

    move_number += MAXTURNPERROUND;

    state[move_number] = getCodeFromID(move_id, bonus_id);

    cout << " codage " << state[move_number] << endl;
    cout << "check move : " << checkMove(state, move_number) << endl;
    cout << "check bonus : " << checkBonus(state, move_number) << endl;
    cout << "get move id : " << getIDmove(state, move_number) << endl;
    cout << "get bonus id : " << getIDbonus(state, move_number) << endl;

    move_id = IDMOVEPASS;

    cout << "Test codage PASS : id = " << move_id << " no bonus" << endl;

    move_number ++;

    state[move_number] = getCodeFromID(move_id);

    cout << " codage " << state[move_number] << endl;
    cout << "check move : " << checkMove(state, move_number) << endl;
    cout << "check bonus : " << checkBonus(state, move_number) << endl;
    cout << "check pass : " << checkPass(state, move_number) << endl;
    cout << "get move id : " << getIDmove(state, move_number) << endl << endl;



    string file = getCheminDossierFils(getCheminDossierData(),{"gameinstance", "exemple_instance.json"});

    JsonLoader loader(file);

    auto & json = loader.getData();

    GameInstance instance(json);

    cout << instance << endl;

    Monde monde;
    monde.setInstance(&instance);

    auto & liste_stations = monde.getListeStations();

    auto fenetre = lanceApplicationParDefaut();

    auto factory = VisitorDessinateurFactory(fenetre);

    delete state;
    state = newGameState();

    PenColor pen = (PenColor)0;

    int coup_manche = 0, coup_state = 0;

    fenetre->addBouton(0, "Coup aléatoire");
    fenetre->addBouton(1, "Fermer");

    vector<Move> list_moves;

    VisitorDessinateurCard dessinateurCard(fenetre);

    while (true) {

        cout << "Debut" << endl;

        list_moves.clear();

        for (int i = 0; i < PENCOLORNUMBER; ++i) {
            for (int j = 0; j < MAXTURNPERROUND; ++j) {
                cout << " " << state[i*MAXTURNPERROUND + j];
            }
            cout << endl;
        }

        int moves = monde.calculateAllPossibleMoves(state, pen, list_moves);

        cout << "calculate moves " << moves << endl;

        fenetre->effaceTout();

        cout << "Efface" << endl;


        if (-1 == moves) {
            cout << "no more moves" << endl;

            VisitorDessinateurMonde dessinateurMonde(fenetre,
                                                     factory.getVisitorStationDepart(monde),
                                                     factory.getVisitorConnexionChemin(monde, state));

            cout << "dessinateur" << endl;


            monde.visit(&dessinateurMonde);

            pen = PenColor(pen + 1);

            if (pen == PENCOLORNUMBER) break;

            coup_manche = 0;
            coup_state =  pen * MAXTURNPERROUND;

            continue;
        }

        VisitorDessinateurMonde dessinateurMonde(fenetre,
                                                 factory.getVisitorStationDepart(monde),
                                                 factory.getVisitorConnexionChoixMoves(monde, state, list_moves, pen));

        cout << "dessinateur" << endl;


        monde.visit(&dessinateurMonde);

        cout << "dessinateur monde" << endl;


        fenetre->setGroupeDessin("Carte");

        monde.getGameInstance()->getDeck(pen)[coup_manche].visit(&dessinateurCard);

        cout << "dessinateur  carte" << endl;

        fenetre->ping();

        int code = stoi(fenetre->listen());

        cout << "code " << code << endl;


        if (code == 0) {

            int coup = 0;

            if (list_moves.size() > 1) {
                coup = rand() % (list_moves.size() - 1);
            }

            cout << "coup n° " << coup << endl;

            state[coup_state] = list_moves[coup];

            coup_manche ++;
            coup_state ++;

        } else {
            break;
        }
    }

    cout << "Break" << endl;

    //fenetre->listen();
    delete fenetre;
    delete state;
    return 0;
}
