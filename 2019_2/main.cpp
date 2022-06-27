#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int VARDO_ILGIS = 20;

const int SEK_MIN = 60;
const int SEK_VAL = 3600;

// merginos - 1, vaikinai - 2

struct StartavusioDuomenys {
    char vardas[VARDO_ILGIS + 1];
    int starto_numeris = 0;
    int starto_laikas = 0;
};

struct FinisavusioDuomenys {
    char vardas[VARDO_ILGIS + 1];

    int starto_numeris = 0;
    int starto_laikas = 0;
    int finiso_laikas = 0;

    int taiklus_suviai_a = 0;
    int taiklus_suviai_b = 0;
    int taiklus_suviai_c = 0;
    int taiklus_suviai_d = 0;

    int rezultatas = 0;
};

void SkaitytiDuomenis(
    int &startavusiu_skaicius, StartavusioDuomenys startavusiu_duomenys[],
    int &finisavusiu_skaicius, FinisavusioDuomenys finisavusiu_duomenys[]) {
    
    ifstream fin("./U2.txt");

    fin >> startavusiu_skaicius;

    int val, min, sek;

    // cout << "Startavusiu: " << startavusiu_skaicius << endl; 

    for (int x = 0; x < startavusiu_skaicius; x++) {
        fin.ignore(64, '\n');
        fin.get(startavusiu_duomenys[x].vardas, VARDO_ILGIS);

        fin >> startavusiu_duomenys[x].starto_numeris >> val >> min >> sek;
        startavusiu_duomenys[x].starto_laikas = val * SEK_VAL + min * SEK_MIN + sek;
    }

    fin >> finisavusiu_skaicius;

    // cout << "Finisavusiu: " << finisavusiu_skaicius << endl;

    for (int x = 0; x < finisavusiu_skaicius; x++) {
        fin >> finisavusiu_duomenys[x].starto_numeris >> val >> min >> sek;
        finisavusiu_duomenys[x].finiso_laikas = val * SEK_VAL + min * SEK_MIN + sek;

        fin >> finisavusiu_duomenys[x].taiklus_suviai_a
            >> finisavusiu_duomenys[x].taiklus_suviai_b;

        if (finisavusiu_duomenys[x].starto_numeris / 100 == 2) {
            fin >> finisavusiu_duomenys[x].taiklus_suviai_c
                >> finisavusiu_duomenys[x].taiklus_suviai_d;
        }
    }

    fin.close();
}

void SkaiciuotiRezultatus(
    int startavusiu_skaicius, StartavusioDuomenys startavusiu_duomenys[],
    int finisavusiu_skaicius, FinisavusioDuomenys finisavusiu_duomenys[]) {

    for (int x = 0; x < finisavusiu_skaicius; x++) {
        int baudos_minutes = 0;

        for (int y = 0; y < startavusiu_skaicius; y++) {
            if (finisavusiu_duomenys[x].starto_numeris != startavusiu_duomenys[y].starto_numeris) continue;

            finisavusiu_duomenys[x].starto_laikas = startavusiu_duomenys[y].starto_laikas;

            baudos_minutes += 5 - finisavusiu_duomenys[x].taiklus_suviai_a;
            baudos_minutes += 5 - finisavusiu_duomenys[x].taiklus_suviai_b;

            if (finisavusiu_duomenys[x].starto_numeris / 100 == 2) {
                baudos_minutes += 5 - finisavusiu_duomenys[x].taiklus_suviai_c;
                baudos_minutes += 5 - finisavusiu_duomenys[x].taiklus_suviai_d;
            }

            for (int z = 0; z < VARDO_ILGIS; z++) {
                finisavusiu_duomenys[x].vardas[z] = startavusiu_duomenys[y].vardas[z];
            }

            finisavusiu_duomenys[x].rezultatas = (finisavusiu_duomenys[x].finiso_laikas - finisavusiu_duomenys[x].starto_laikas) + baudos_minutes * SEK_MIN;

            break;
        }

    }
}

void RikiuotiRezultatus(
    int finisavusiu_skaicius, FinisavusioDuomenys finisavusiu_duomenys[]) {

    for (int x = 0; x < finisavusiu_skaicius; x++) {
        for (int y = 0; y < finisavusiu_skaicius; y++) {
            if (finisavusiu_duomenys[x].starto_numeris / 100 > finisavusiu_duomenys[y].starto_numeris / 100) continue;

            if (finisavusiu_duomenys[x].rezultatas > finisavusiu_duomenys[y].rezultatas) continue;

            if (finisavusiu_duomenys[x].rezultatas == finisavusiu_duomenys[y].rezultatas
                && strcmp(finisavusiu_duomenys[x].vardas, finisavusiu_duomenys[y].vardas) > 0) continue;


            FinisavusioDuomenys laikinas = finisavusiu_duomenys[x];
            finisavusiu_duomenys[x] = finisavusiu_duomenys[y];
            finisavusiu_duomenys[y] = laikinas;
        }
    }
}

void SpausdintiRezultatus(
    int finisavusiu_skaicius, FinisavusioDuomenys finisavusiu_duomenys[]) {

    ofstream fout("./U2rez.txt");

    fout << "Merginos" << endl;

    for (int x = 0; x < finisavusiu_skaicius; x++) {
        if (finisavusiu_duomenys[x].starto_numeris / 100 != 1) continue;

        int val = finisavusiu_duomenys[x].rezultatas / SEK_VAL;
        int min = (finisavusiu_duomenys[x].rezultatas - val * SEK_VAL) / SEK_MIN;
        int sek = finisavusiu_duomenys[x].rezultatas % 60;

        fout
            << finisavusiu_duomenys[x].starto_numeris << " "
            << finisavusiu_duomenys[x].vardas << "  "
            << val << " " << min << " " << sek << endl;
    }

    fout << "Vaikinai" << endl;

    for (int x = 0; x < finisavusiu_skaicius; x++) {
        if (finisavusiu_duomenys[x].starto_numeris / 100 != 2) continue;

        int val = finisavusiu_duomenys[x].rezultatas / SEK_VAL;
        int min = (finisavusiu_duomenys[x].rezultatas - val * SEK_VAL) / SEK_MIN;
        int sek = finisavusiu_duomenys[x].rezultatas % 60;

        fout
            << finisavusiu_duomenys[x].starto_numeris << " "
            << finisavusiu_duomenys[x].vardas << "  "
            << val << " " << min << " " << sek << endl;
    }


    fout.close();
}

int main() {
    int startavusiu_skaicius, finisavusiu_skaicius;

    StartavusioDuomenys startavusiu_duomenys[30];
    FinisavusioDuomenys finisavusiu_duomenys[30];

    SkaitytiDuomenis(startavusiu_skaicius, startavusiu_duomenys, finisavusiu_skaicius, finisavusiu_duomenys);
    SkaiciuotiRezultatus(startavusiu_skaicius, startavusiu_duomenys, finisavusiu_skaicius, finisavusiu_duomenys);
    RikiuotiRezultatus(finisavusiu_skaicius, finisavusiu_duomenys);
    SpausdintiRezultatus(finisavusiu_skaicius, finisavusiu_duomenys);


    return 0;
}