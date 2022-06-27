#include <iostream>
#include <fstream>

using namespace std;

struct GelesDuomenys {
    int numeris;
    int pradzios_menesis;
    int pradzios_diena;
    int pabaigos_menesis;
    int pabaigos_diena;
};

struct DienosDuomenys {
    int numeris;
    int menesis;
    int diena;
    int geliu_skaicius;
};

const int VASAROS_DIENU_KIEKIS = 92;
const int BIRZELIO_DIENU_KIEKIS = 30;
const int LIEPOS_DIENU_KIEKIS = 31;
const int RUGPJUCIO_DIENU_KIEKIS = 31;

// 06-01 = 0

int Dienos_Indeksas(int menesis, int diena) {
    if (menesis == 6) return diena - 1;
    if (menesis == 7) return BIRZELIO_DIENU_KIEKIS + diena - 1;
    if (menesis == 8) return BIRZELIO_DIENU_KIEKIS + LIEPOS_DIENU_KIEKIS + diena - 1;

    return -1;
}

// 92 dienos apparently.

GelesDuomenys* SkaitytiDuomenis(int &geliu_kiekis) {
    ifstream fin("./U1.txt");

    fin >> geliu_kiekis;
    GelesDuomenys* geliu_duomenys = new GelesDuomenys[geliu_kiekis];

    for (int i = 0; i < geliu_kiekis; i++) {
        fin >> geliu_duomenys[i].numeris
            >> geliu_duomenys[i].pradzios_menesis
            >> geliu_duomenys[i].pradzios_diena
            >> geliu_duomenys[i].pabaigos_menesis
            >> geliu_duomenys[i].pabaigos_diena;
    }

    fin.close();
    return geliu_duomenys;
}


int main() {
    int geliu_kiekis;
    GelesDuomenys* geliu_duomenys = SkaitytiDuomenis(geliu_kiekis);
    DienosDuomenys* dienu_duomenys = new DienosDuomenys[VASAROS_DIENU_KIEKIS];

    for (int men = 6; men <= 8; men++) {
        int men_max_d = 0;

        if (men == 6) men_max_d = BIRZELIO_DIENU_KIEKIS;
        if (men == 7) men_max_d = LIEPOS_DIENU_KIEKIS;
        if (men == 8) men_max_d = RUGPJUCIO_DIENU_KIEKIS;

        for (int d = 1; d <= men_max_d; d++) {
            int ind = Dienos_Indeksas(men, d);

            dienu_duomenys[ind].numeris = ind;
            dienu_duomenys[ind].menesis = men;
            dienu_duomenys[ind].diena = d;
            dienu_duomenys[ind].geliu_skaicius = 0;

            for (int i = 0; i < geliu_kiekis; i++) {
                int prad_id = Dienos_Indeksas(geliu_duomenys[i].pradzios_menesis, geliu_duomenys[i].pradzios_diena);
                int pab_id = Dienos_Indeksas(geliu_duomenys[i].pabaigos_menesis, geliu_duomenys[i].pabaigos_diena);

                //cout << prad_id << " ir " << pab_id << endl;

                if (prad_id <= ind && ind <= pab_id) {
                    dienu_duomenys[ind].geliu_skaicius++;
                }
            }

            //cout << men << "-" << d << ":" << ind << " = " << dienu_duomenys[ind].geliu_skaicius << endl;
        }
    }

    int max_geliu = 0;
    for (int d = 1; d < VASAROS_DIENU_KIEKIS; d++) {
        if (dienu_duomenys[d].geliu_skaicius > dienu_duomenys[max_geliu].geliu_skaicius)
            max_geliu = d;
    }

    int intervalo_ilg = 0;
    for (int d = max_geliu + 1; d < VASAROS_DIENU_KIEKIS; d++) {
        if (dienu_duomenys[d].geliu_skaicius == dienu_duomenys[max_geliu].geliu_skaicius) intervalo_ilg++;
    }

    cout << dienu_duomenys[max_geliu].geliu_skaicius << endl;
    cout
        << dienu_duomenys[max_geliu].menesis << " "
        << dienu_duomenys[max_geliu].diena << endl;

    cout
        << dienu_duomenys[max_geliu + intervalo_ilg].menesis << " "
        << dienu_duomenys[max_geliu + intervalo_ilg].diena << endl;



   // SaugotiDuomenis(geliu_duomenys, geliu_kiekis);

    return 0;
}