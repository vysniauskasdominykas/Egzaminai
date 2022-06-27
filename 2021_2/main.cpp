#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct MokinioDuomenys {
    string vardas;
    string dalykas;
    int vidurkis;
};

struct DalykoDuomenys {
    string dalykas;
    int megstanciu_mokiniu_skaicius = 0;
    int megstanciu_mokiniu_indeksai[50];
};

void SkaitytiDuomenis(int &mokiniu_skaicius, MokinioDuomenys mokiniu_duomenys[]) {
    ifstream fin("./U2.txt");

    fin >> mokiniu_skaicius;

    for (int x = 0; x < mokiniu_skaicius; x++) {
        int pazymiu_skaicius, pazymys, pazymiu_suma = 0;

        fin >> mokiniu_duomenys[x].vardas
            >> mokiniu_duomenys[x].dalykas
            >> pazymiu_skaicius;

        for (int y = 0; y < pazymiu_skaicius; y++) {
            fin >> pazymys;
            pazymiu_suma += pazymys;
        }

        mokiniu_duomenys[x].vidurkis = pazymiu_suma / pazymiu_skaicius;
    }

    fin.close();
}

void SkaiciuotiRezultatus(int mokiniu_skaicius, MokinioDuomenys mokiniu_duomenys[],
    int &dalyku_skaicius, DalykoDuomenys dalyku_duomenys[]) {

    for (int x = 0; x < mokiniu_skaicius; x++) {
        if (mokiniu_duomenys[x].vidurkis < 9) continue;

        bool dalykas_iterptas = false;

        for (int y = 0; y < dalyku_skaicius; y++) {
            if (dalyku_duomenys[y].dalykas == mokiniu_duomenys[x].dalykas) {
                dalyku_duomenys[y].megstanciu_mokiniu_skaicius++;
                dalyku_duomenys[y].megstanciu_mokiniu_indeksai[dalyku_duomenys[y].megstanciu_mokiniu_skaicius - 1] = x;
                dalykas_iterptas = true;
                break;
            }
        }

        if (!dalykas_iterptas) {
            dalyku_skaicius++;
            dalyku_duomenys[dalyku_skaicius - 1].dalykas = mokiniu_duomenys[x].dalykas;
            dalyku_duomenys[dalyku_skaicius - 1].megstanciu_mokiniu_skaicius++;
            dalyku_duomenys[dalyku_skaicius - 1].megstanciu_mokiniu_indeksai[0] = x;
        }
    }
}

void RikiuotiRezultatus(int &dalyku_skaicius, DalykoDuomenys dalyku_duomenys[])  {

    for (int x = 0; x < dalyku_skaicius; x++) {
        for (int y = 0; y < dalyku_skaicius; y++) {
            if (dalyku_duomenys[x].megstanciu_mokiniu_skaicius < dalyku_duomenys[y].megstanciu_mokiniu_skaicius) continue;

            if (dalyku_duomenys[x].megstanciu_mokiniu_skaicius == dalyku_duomenys[y].megstanciu_mokiniu_skaicius) {
                if (strcmp(dalyku_duomenys[x].dalykas.c_str(), dalyku_duomenys[y].dalykas.c_str()) > 0) continue;
            }

            DalykoDuomenys laikina = dalyku_duomenys[x];
            dalyku_duomenys[x] = dalyku_duomenys[y];
            dalyku_duomenys[y] = laikina;
        }
    }
    // pagal pop, pagal abc
}

void SpausdintiRezultatus(int mokiniu_skaicius, MokinioDuomenys mokiniu_duomenys[],
    int &dalyku_skaicius, DalykoDuomenys dalyku_duomenys[]) {
    
    ofstream fout("./U2rez.txt");

    if (dalyku_skaicius == 0)
        fout << "Neatitinka vidurkis" << endl;

    for (int x = 0; x < dalyku_skaicius; x++) {
        fout << dalyku_duomenys[x].dalykas << " " << dalyku_duomenys[x].megstanciu_mokiniu_skaicius << endl;

        for (int y = 0; y < dalyku_duomenys[x].megstanciu_mokiniu_skaicius; y++) {
            fout << mokiniu_duomenys[dalyku_duomenys[x].megstanciu_mokiniu_indeksai[y]].vardas << endl;
        }
    }

    fout.close();
}

int main() {
    int mokiniu_skaicius, dalyku_skaicius = 0;
    MokinioDuomenys mokiniu_duomenys[50];
    DalykoDuomenys dalyku_duomenys[50];

    SkaitytiDuomenis(mokiniu_skaicius, mokiniu_duomenys);

    SkaiciuotiRezultatus(mokiniu_skaicius, mokiniu_duomenys, dalyku_skaicius, dalyku_duomenys);

    RikiuotiRezultatus(dalyku_skaicius, dalyku_duomenys);

    SpausdintiRezultatus(mokiniu_skaicius, mokiniu_duomenys, dalyku_skaicius, dalyku_duomenys);

    return 0;
}