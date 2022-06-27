#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

const int MAX_SLIDININKU = 30;
const int VARDO_ILGIS = 20;
const int SEK_VAL = 3600;
const int SEK_MIN = 60;

struct Slidininkas {
    char Vardas[VARDO_ILGIS + 1];
    int Starto_Laikas;
    int Finiso_Laikas;
    int Trukme;
};

void SkaitytiDuomenis(Slidininkas slidininkai[], int &slidininku_kiekis) {
    ifstream file_input("./U2.txt");

    file_input >> slidininku_kiekis;

    for (int i = 0; i < slidininku_kiekis; i++) {
        file_input.ignore(512, '\n');
        file_input.get(slidininkai[i].Vardas, VARDO_ILGIS);

        int val, min, sek;
        file_input >> val >> min >> sek;

        slidininkai[i].Starto_Laikas = val * SEK_VAL + min * SEK_MIN + sek;
        slidininkai[i].Finiso_Laikas = 0;
        slidininkai[i].Trukme = 0;
    }

    int finisavusiu_kiekis;

    file_input >> finisavusiu_kiekis;

    for (int i = 0; i < finisavusiu_kiekis; i++) {
        char vardas[VARDO_ILGIS + 1];

        file_input.ignore(512, '\n');
        file_input.get(vardas, VARDO_ILGIS);

        int val, min, sek;
        file_input >> val >> min >> sek;

        for (int j = 0; j < slidininku_kiekis; j++) {
            if (strcmp(vardas, slidininkai[j].Vardas) != 0) continue;

            slidininkai[j].Finiso_Laikas = val * SEK_VAL + min * SEK_MIN + sek;

            slidininkai[j].Trukme = slidininkai[j].Finiso_Laikas - slidininkai[j].Starto_Laikas;


            // 23:59:00 = 86 340
            // 00:01:00 = 60

            // 60 - 86 340 = -86 280
            // if (t < 0) { += 86400 } = 120s.

            // jeigu pvz. pradzia 23:30:00, pabaiga 01:00:00 (kita diena)
            
            if (slidininkai[j].Trukme < 0)
                slidininkai[j].Trukme += SEK_VAL * 24;

            break;
        }
    }

    file_input.close();
}

void SaugotiDuomenis(Slidininkas slidininkai[], int slidininku_kiekis) {
    ofstream file_output("./U2rez.txt");

    for (int i = 0; i < slidininku_kiekis; i++) {
        if (slidininkai[i].Finiso_Laikas == 0) continue;

        int sek = slidininkai[i].Trukme;
        int min = sek / SEK_MIN;
        sek -= min * SEK_MIN;

        file_output << slidininkai[i].Vardas << " " << min << " " << sek << endl;
    }

    file_output.close();
}

void RikiuotiDuomenis(Slidininkas slidininkai[], int slidininku_kiekis) {
    for (int i = 0; i < slidininku_kiekis; i++) {
        for (int j = 0; j < slidininku_kiekis; j++) {
            if (i == j) continue;

            if (slidininkai[i].Trukme > slidininkai[j].Trukme) {
                continue;
            }
            
            if (slidininkai[i].Trukme == slidininkai[j].Trukme && strcmp(slidininkai[i].Vardas, slidininkai[j].Vardas) > 0) {
                continue;
            }

            Slidininkas t = slidininkai[i];
            slidininkai[i] = slidininkai[j];
            slidininkai[j] = t;
        }
    }
}

int main() {
    int slidininku_kiekis;
    Slidininkas slidininkai[MAX_SLIDININKU];

    SkaitytiDuomenis(slidininkai, slidininku_kiekis);

    RikiuotiDuomenis(slidininkai, slidininku_kiekis);

    SaugotiDuomenis(slidininkai, slidininku_kiekis);

    return 0;
}