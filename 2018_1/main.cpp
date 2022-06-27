#include <iostream>
#include <fstream>

using namespace std;

struct Duomenys {
    int kruveliu_skaicius = 0;
    int viso_g = 0;
    int viso_z = 0;
    int viso_r = 0;
};

struct Rezultatai {
    int veleveliu_skaicius = 0;
    int liko_g = 0;
    int liko_z = 0;
    int liko_r = 0;
};

void SkaitytiDuomenis(Duomenys &duomenys) {
    ifstream fin("./U1.txt");

    fin >> duomenys.kruveliu_skaicius;

    for (int x = 0; x < duomenys.kruveliu_skaicius; x++) {
        char spalva;
        fin >> spalva;
        int kiekis;
        fin >> kiekis;

        switch (spalva) {
            case 'G': duomenys.viso_g += kiekis; break;
            case 'Z': duomenys.viso_z += kiekis; break;
            case 'R': duomenys.viso_r += kiekis; break;
        }
    }

    fin.close();
}

void SkaiciuotiRezultatus(Duomenys &duomenys, Rezultatai &rezultatai) {
    rezultatai.liko_g = duomenys.viso_g;
    rezultatai.liko_z = duomenys.viso_z;
    rezultatai.liko_r = duomenys.viso_r;

    while (rezultatai.liko_g > 1 &&  rezultatai.liko_z > 1 && rezultatai.liko_r > 1) {
        rezultatai.veleveliu_skaicius++;
        rezultatai.liko_g -= 2;
        rezultatai.liko_z -= 2;
        rezultatai.liko_r -= 2;
    }
}

void SpausdintiRezultatus(Rezultatai &rezultatai) {
    ofstream fout("./U1rez.txt");

    fout
        << rezultatai.veleveliu_skaicius << endl
        << "G = " << rezultatai.liko_g << endl
        << "Z = " << rezultatai.liko_z << endl
        << "R = " << rezultatai.liko_r << endl;

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