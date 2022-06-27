#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int PAVADINIMO_ILGIS = 20;

struct PristatytosZuviesDuomenys {
    char Pavadinimas[PAVADINIMO_ILGIS + 1];
    int Svoris = 0;
};

struct VertinamosZuviesDuomenys {
    char Pavadinimas[PAVADINIMO_ILGIS + 1];
    int SkiriamiTaskai = 0;
    int BendrasSvoris = 0;
};

struct ZvejoDuomenys {
    char Vardas[PAVADINIMO_ILGIS + 1];
    int SurinktiTaskai = 0;

    int PristatytuZuvuKiekis = 0;
    PristatytosZuviesDuomenys* PristatytosZuvys;
};

void SkaitytiDuomenis(int &zveju_kiekis, ZvejoDuomenys zveju_duomenys[], int &vertinamu_zuvu_kiekis, VertinamosZuviesDuomenys vertinamu_zuvu_duomenys[]) {
    ifstream fin("./U2.txt");

    fin >> zveju_kiekis;

    for (int x = 0; x < zveju_kiekis; x++) {
        fin.ignore(32, '\n');
        fin.get(zveju_duomenys[x].Vardas, PAVADINIMO_ILGIS);

        fin >> zveju_duomenys[x].PristatytuZuvuKiekis;
        zveju_duomenys[x].PristatytosZuvys = new PristatytosZuviesDuomenys[zveju_duomenys[x].PristatytuZuvuKiekis];

        for (int y = 0; y < zveju_duomenys[x].PristatytuZuvuKiekis; y++) {
            fin.ignore(32, '\n');
            fin.get(zveju_duomenys[x].PristatytosZuvys[y].Pavadinimas, PAVADINIMO_ILGIS);
            fin >> zveju_duomenys[x].PristatytosZuvys[y].Svoris;
        }
    }

    fin >> vertinamu_zuvu_kiekis;

    for (int x = 0; x < vertinamu_zuvu_kiekis; x++) {
        fin.ignore(32, '\n');
        fin.get(vertinamu_zuvu_duomenys[x].Pavadinimas, PAVADINIMO_ILGIS);
        fin >> vertinamu_zuvu_duomenys[x].SkiriamiTaskai;
    }
    
    fin.close();
}

void RikiuotiDuomenis(int zveju_kiekis, ZvejoDuomenys zveju_duomenys[], int vertinamu_zuvu_kiekis, VertinamosZuviesDuomenys vertinamu_zuvu_duomenys[]) {
    for (int x = 0; x < zveju_kiekis; x++) {
        for (int y = 0; y < zveju_kiekis; y++) {
            if (zveju_duomenys[x].SurinktiTaskai < zveju_duomenys[y].SurinktiTaskai) continue;

            if (zveju_duomenys[x].SurinktiTaskai == zveju_duomenys[y].SurinktiTaskai) {
                if (strcmp(zveju_duomenys[x].Vardas, zveju_duomenys[y].Vardas) > 0) continue;
            }

            ZvejoDuomenys l = zveju_duomenys[x];
            zveju_duomenys[x] = zveju_duomenys[y];
            zveju_duomenys[y] = l;
        }
    }

    for (int x = 0; x < vertinamu_zuvu_kiekis; x++) {
        for (int y = 0; y < vertinamu_zuvu_kiekis; y++) {
            if (vertinamu_zuvu_duomenys[x].BendrasSvoris < vertinamu_zuvu_duomenys[y].BendrasSvoris) continue;

            if (vertinamu_zuvu_duomenys[x].BendrasSvoris == vertinamu_zuvu_duomenys[y].BendrasSvoris) {
                if (strcmp(vertinamu_zuvu_duomenys[x].Pavadinimas, vertinamu_zuvu_duomenys[y].Pavadinimas) > 0) continue;
            }

            VertinamosZuviesDuomenys l = vertinamu_zuvu_duomenys[x];
            vertinamu_zuvu_duomenys[x] = vertinamu_zuvu_duomenys[y];
            vertinamu_zuvu_duomenys[y] = l;
        }
    }
}

void SpausdintiDuomenis(int zveju_kiekis, ZvejoDuomenys zveju_duomenys[], int vertinamu_zuvu_kiekis, VertinamosZuviesDuomenys vertinamu_zuvu_duomenys[]) {
    ofstream fout("./U2rez.txt");

    fout << "Dalyviai" << endl;

    for (int x = 0; x < zveju_kiekis; x++) {
        fout << zveju_duomenys[x].Vardas << " " << zveju_duomenys[x].SurinktiTaskai << endl;
    }

    fout << "Laimikis" << endl;

    for (int x = 0; x < vertinamu_zuvu_kiekis; x++) {
        fout << vertinamu_zuvu_duomenys[x].Pavadinimas << " " << vertinamu_zuvu_duomenys[x].BendrasSvoris << endl;
    }

    fout.close();
}

int main() {
    int zveju_kiekis;
    ZvejoDuomenys zveju_duomenys[30];
    
    int vertinamu_zuvu_kiekis;
    VertinamosZuviesDuomenys vertinamu_zuvu_duomenys[30]; 

    SkaitytiDuomenis(zveju_kiekis, zveju_duomenys, vertinamu_zuvu_kiekis, vertinamu_zuvu_duomenys);

    for (int i = 0; i < zveju_kiekis; i++) {
        // cout << zveju_duomenys[i].Vardas << " " << zveju_duomenys[i].PristatytuZuvuKiekis << endl;

        for (int j = 0; j < zveju_duomenys[i].PristatytuZuvuKiekis; j++) {
            // int vert_zuv_ind = VertinamosZuviesIndeksasPagalPavadinima(vertinamu_zuvu_kiekis, vertinamu_zuvu_duomenys, zveju_duomenys[i].PristatytosZuvys[j].Pavadinimas);

            if (zveju_duomenys[i].PristatytosZuvys[j].Svoris < 200) {
                zveju_duomenys[i].SurinktiTaskai += 10;
            } else {
                zveju_duomenys[i].SurinktiTaskai += 30;
            }

            for (int k = 0; k < vertinamu_zuvu_kiekis; k++) {
                if (strcmp(zveju_duomenys[i].PristatytosZuvys[j].Pavadinimas, vertinamu_zuvu_duomenys[k].Pavadinimas) != 0) continue;

                zveju_duomenys[i].SurinktiTaskai += vertinamu_zuvu_duomenys[k].SkiriamiTaskai;
                vertinamu_zuvu_duomenys[k].BendrasSvoris += zveju_duomenys[i].PristatytosZuvys[j].Svoris;

                break;
            }

            //cout << zveju_duomenys[i].PristatytosZuvys[j].Pavadinimas << " "
            //    << zveju_duomenys[i].PristatytosZuvys[j].Svoris << endl;

            // mase >= 200 - 30 task, mase < 200 - 10 task. + vertnamu kk...
        }
    }

    RikiuotiDuomenis(zveju_kiekis, zveju_duomenys, vertinamu_zuvu_kiekis, vertinamu_zuvu_duomenys);
    SpausdintiDuomenis(zveju_kiekis, zveju_duomenys, vertinamu_zuvu_kiekis, vertinamu_zuvu_duomenys);


    return 0;
}