#include <iostream>
#include <fstream>

using namespace std;

const int VAL_MIN = 60;

struct DienosDuomenys {
    int diena = 0;
    int trukme = 0;
    int bego_abu_kartus = false;
    // int pirmo_begimo_trukme;
    // int antro_begimo_trukme;
};

void SkaitytiDuomenis(int &dienu_skaicius, DienosDuomenys dienu_duomenys[]) {
    ifstream fin("./U1.txt");

    fin >> dienu_skaicius;

    int pirm_prad_val, pirm_prad_min,
        pirm_pab_val, pirm_pab_min;

    int antr_prad_val, antr_prad_min,
        antr_pab_val, antr_pab_min;

    for (int x = 0; x < dienu_skaicius; x++) {
        fin >> dienu_duomenys[x].diena;

        fin >> pirm_prad_val
            >> pirm_prad_min
            >> pirm_pab_val
            >> pirm_pab_min;

        fin >> antr_prad_val
            >> antr_prad_min
            >> antr_pab_val 
            >> antr_pab_min;

        if (pirm_prad_val == 0 && pirm_prad_min == 0) continue;
        if (pirm_pab_val == 0 && pirm_pab_min == 0) continue;

        if (antr_prad_val == 0 && antr_prad_min == 0) continue;
        if (antr_pab_val == 0 && antr_pab_min == 0) continue;

        int pirm_prad = pirm_prad_val * VAL_MIN + pirm_prad_min;
        int pirm_pab = pirm_pab_val * VAL_MIN + pirm_pab_min;
        int pirm = pirm_pab - pirm_prad;

        int antr_prad = antr_prad_val * VAL_MIN + antr_prad_min;
        int antr_pab = antr_pab_val * VAL_MIN + antr_pab_min;
        int antr = antr_pab - antr_prad;

        dienu_duomenys[x].bego_abu_kartus = true;
        dienu_duomenys[x].trukme = pirm + antr;
    }

    fin.close();
}

int RastiMaziausiaReiksme(int dienu_skaicius, DienosDuomenys dienu_duomenys[]) {
    int maziausia = 0;

    for (int x = 0; x < dienu_skaicius; x++) {
        if (dienu_duomenys[x].bego_abu_kartus) {
            maziausia = x;
            break;
        }
    }

    for (int x = 0; x < dienu_skaicius; x++) {
        if (dienu_duomenys[x].bego_abu_kartus && dienu_duomenys[x].trukme < dienu_duomenys[maziausia].trukme)
            maziausia = x;
    }

    return dienu_duomenys[maziausia].trukme;
}

void SaugotiRezultatus(int dienu_skaicius, DienosDuomenys dienu_duomenys[]) {
    ofstream fout("./U1rez.txt");

    int maziausia_reiksme = RastiMaziausiaReiksme(dienu_skaicius, dienu_duomenys);

    fout << "Minimalus laikas" << endl;
    fout << maziausia_reiksme << endl;
    fout << "Dienos" << endl;

    for (int x = 0; x < dienu_skaicius; x++) {
        if (dienu_duomenys[x].trukme == maziausia_reiksme) {
            fout << dienu_duomenys[x].diena << " ";
        }
    }

    fout << endl;

    fout.close();
}

int main() {
    int dienu_skaicius;
    DienosDuomenys dienu_duomenys[31];

    SkaitytiDuomenis(dienu_skaicius, dienu_duomenys);
    SaugotiRezultatus(dienu_skaicius, dienu_duomenys);

    return 0;
}