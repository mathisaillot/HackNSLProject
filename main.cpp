#include <iostream>

#include <Monde.h>

using namespace std;

int main() {
    Monde monde;
    auto & liste_stations = monde.getListeStations();

    for (auto & station : liste_stations) {
        cout << station << endl;
    }
    return 0;
}
