#include <iostream>
#include <fstream>

using namespace std;

struct Spalva {
    int R;
    int G;
    int B;
    char Kodas[6];
};

struct Piesinys {
    int plotis;
    int aukstis;
    Spalva* spalvos;
};

void SkaitytiDuomenis(Piesinys &piesinio_duomenys) {
    ifstream fin("./U1.txt");
    
    fin >> piesinio_duomenys.aukstis
        >> piesinio_duomenys.plotis;

    piesinio_duomenys.spalvos = new Spalva[piesinio_duomenys.plotis * piesinio_duomenys.aukstis];

    for (int i = 0; i < piesinio_duomenys.plotis * piesinio_duomenys.aukstis; i++) {
        fin >> piesinio_duomenys.spalvos[i].R
            >> piesinio_duomenys.spalvos[i].G
            >> piesinio_duomenys.spalvos[i].B;
    }

    fin.close();
}

char SkaiciausSimbolis(int skaicius) {
    switch (skaicius) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
    }

    return '-';
}

void SkaiciuotiRezultatus(Piesinys &piesinio_duomenys) {
    for (int i = 0; i < piesinio_duomenys.plotis * piesinio_duomenys.aukstis; i++) {
        piesinio_duomenys.spalvos[i].Kodas[0] = SkaiciausSimbolis(piesinio_duomenys.spalvos[i].R / 16);
        piesinio_duomenys.spalvos[i].Kodas[1] = SkaiciausSimbolis(piesinio_duomenys.spalvos[i].R % 16);
        piesinio_duomenys.spalvos[i].Kodas[2] = SkaiciausSimbolis(piesinio_duomenys.spalvos[i].G / 16);
        piesinio_duomenys.spalvos[i].Kodas[3] = SkaiciausSimbolis(piesinio_duomenys.spalvos[i].G % 16);
        piesinio_duomenys.spalvos[i].Kodas[4] = SkaiciausSimbolis(piesinio_duomenys.spalvos[i].B / 16);
        piesinio_duomenys.spalvos[i].Kodas[5] = SkaiciausSimbolis(piesinio_duomenys.spalvos[i].B % 16);
    }
}

void SpausdintiRezultatus(Piesinys &piesinio_duomenys) {
    ofstream fout("./U1rez.txt");

    for (int y = 0; y < piesinio_duomenys.aukstis; y++) {
        for (int x = 0; x < piesinio_duomenys.plotis; x++) {
            if (x != 0) fout << ";";
            fout << piesinio_duomenys.spalvos[x + y * piesinio_duomenys.plotis].Kodas;
        }

        fout << endl;
    }

    fout.close();
}

int main() {
    Piesinys piesinio_duomenys;

    SkaitytiDuomenis(piesinio_duomenys);
    SkaiciuotiRezultatus(piesinio_duomenys);
    SpausdintiRezultatus(piesinio_duomenys);

    return 0;
}