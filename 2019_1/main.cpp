#include <iostream>
#include <fstream>

using namespace std;

struct Duomenys {
    int turimi_indai_1l = 0;
    int turimi_indai_3l = 0;
    int turimi_indai_5l = 0;
    int isspausta_aliejaus = 0;

    int spaudimo_islaidos = 0;
    int indo_kaina_1l = 0;
    int indo_kaina_3l = 0;
    int indo_kaina_5l = 0;
};

struct Rezultatai {
    int pripilta_indu_1l = 0;
    int pripilta_indu_3l = 0;
    int pripilta_indu_5l = 0;
    int aliejaus_likutis = 0;

    int indu_nepanaudota_1l = 0;
    int indu_nepanaudota_3l = 0;
    int indu_nepanaudota_5l = 0;
    
    int indu_truksta_1l = 0;
    int indu_truksta_3l = 0;
    int indu_truksta_5l = 0;

    int pelnas = 0;
};

void SkaitytiDuomenis(Duomenys &duomenys) {
    ifstream fin("./U1.txt");

    fin >> duomenys.turimi_indai_1l;
    fin >> duomenys.turimi_indai_3l;
    fin >> duomenys.turimi_indai_5l;
    fin >> duomenys.isspausta_aliejaus;

    fin >> duomenys.spaudimo_islaidos;
    fin >> duomenys.indo_kaina_1l;
    fin >> duomenys.indo_kaina_3l;
    fin >> duomenys.indo_kaina_5l;

    fin.close();
}

void SkaiciuotiRezultatus(Duomenys &duomenys, Rezultatai &rezultatai) {
    rezultatai.aliejaus_likutis = duomenys.isspausta_aliejaus;
    rezultatai.indu_nepanaudota_1l = duomenys.turimi_indai_1l;
    rezultatai.indu_nepanaudota_3l = duomenys.turimi_indai_3l;
    rezultatai.indu_nepanaudota_5l = duomenys.turimi_indai_5l;

    while (rezultatai.aliejaus_likutis >= 5 && rezultatai.indu_nepanaudota_5l > 0) {
        rezultatai.aliejaus_likutis -= 5;
        rezultatai.indu_nepanaudota_5l--;
        rezultatai.pripilta_indu_5l++;
    }

    while (rezultatai.aliejaus_likutis >= 3 && rezultatai.indu_nepanaudota_3l > 0) {
        rezultatai.aliejaus_likutis -= 3;
        rezultatai.indu_nepanaudota_3l--;
        rezultatai.pripilta_indu_3l++;
    }

    while (rezultatai.aliejaus_likutis >= 1 && rezultatai.indu_nepanaudota_1l > 0) {
        rezultatai.aliejaus_likutis--;
        rezultatai.indu_nepanaudota_1l--;
        rezultatai.pripilta_indu_1l++;
    }

    int t_aliejaus_likutis = rezultatai.aliejaus_likutis;

    while (t_aliejaus_likutis >= 5) {
        t_aliejaus_likutis -= 5;
        rezultatai.indu_truksta_5l++;
    }

    while (t_aliejaus_likutis >= 3) {
        t_aliejaus_likutis -= 3;
        rezultatai.indu_truksta_3l++;
    }

    while (t_aliejaus_likutis >= 1) {
        t_aliejaus_likutis -= 1;
        rezultatai.indu_truksta_1l++;
    }

    // if (rezultatai.indu_nepanaudota_1l < 0) {
    //     rezultatai.indu_truksta_1l = -rezultatai.indu_nepanaudota_1l;
    //     rezultatai.indu_nepanaudota_1l = 0;
    // }

    // if (rezultatai.indu_nepanaudota_3l < 0) {
    //     rezultatai.indu_truksta_3l = -rezultatai.indu_nepanaudota_3l;
    //     rezultatai.indu_nepanaudota_3l = 0;
    // }

    // if (rezultatai.indu_nepanaudota_5l < 0) {
    //     rezultatai.indu_truksta_1l = -rezultatai.indu_nepanaudota_1l;
    //     rezultatai.indu_nepanaudota_1l = 0;
    // }

    rezultatai.pelnas += rezultatai.pripilta_indu_1l * duomenys.indo_kaina_1l;
    rezultatai.pelnas += rezultatai.pripilta_indu_3l * duomenys.indo_kaina_3l;
    rezultatai.pelnas += rezultatai.pripilta_indu_5l * duomenys.indo_kaina_5l;
    rezultatai.pelnas += rezultatai.indu_truksta_1l * duomenys.indo_kaina_1l;
    rezultatai.pelnas += rezultatai.indu_truksta_3l * duomenys.indo_kaina_3l;
    rezultatai.pelnas += rezultatai.indu_truksta_5l * duomenys.indo_kaina_5l;
    rezultatai.pelnas -= duomenys.spaudimo_islaidos;
}

void SpausdintiRezultatus(Rezultatai &rezultatai) {
    ofstream fout("./U1rez.txt");

    fout
        << rezultatai.pripilta_indu_1l << " "
        << rezultatai.pripilta_indu_3l << " "
        << rezultatai.pripilta_indu_5l << " "
        << rezultatai.aliejaus_likutis << endl

        << rezultatai.indu_nepanaudota_1l << " "
        << rezultatai.indu_nepanaudota_3l << " "
        << rezultatai.indu_nepanaudota_5l << endl

        << rezultatai.indu_truksta_1l << " "
        << rezultatai.indu_truksta_3l << " "
        << rezultatai.indu_truksta_5l << endl

        << rezultatai.pelnas << endl;

    fout.close();
}

int main() {
    Duomenys duomenys;
    Rezultatai rezultatai;

    SkaitytiDuomenis(duomenys);
    SkaiciuotiRezultatus(duomenys, rezultatai);
    SpausdintiRezultatus(rezultatai);
    

    return 0;
}