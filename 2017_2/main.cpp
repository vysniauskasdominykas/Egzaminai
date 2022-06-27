#include <iostream>
#include <fstream>

using namespace std;

const int PLOTIS = 100;
const int AUKSTIS = 100;

struct LangelioDuomenys {
    int X = 0;
    int Y = 0;
    int R = 255;
    int G = 255;
    int B = 255;
};

struct StaciakampioDuomenys {
    int X = 0;
    int Y = 0;
    int Plotis = 1;
    int Aukstis = 1;
    int R = 255;
    int G = 255;
    int B = 255;
};

void SkaitytiDuomenis(int &staciakampiu_kiekis, StaciakampioDuomenys staciakampiu_duomenys[]) {
    ifstream fin("./U2.txt");

    fin >> staciakampiu_kiekis;

    for (int i = 0; i < staciakampiu_kiekis; i++) {
        fin >> staciakampiu_duomenys[i].X
            >> staciakampiu_duomenys[i].Y
            >> staciakampiu_duomenys[i].Plotis
            >> staciakampiu_duomenys[i].Aukstis
            >> staciakampiu_duomenys[i].R
            >> staciakampiu_duomenys[i].G
            >> staciakampiu_duomenys[i].B;
    }

    fin.close();
}

void UzdetiStaciakampi(StaciakampioDuomenys staciakampio_duomenys, LangelioDuomenys langeliu_duomenys[]) {
    for (int x = staciakampio_duomenys.X; x < staciakampio_duomenys.X + staciakampio_duomenys.Plotis; x++) {
        for (int y = staciakampio_duomenys.Y; y < staciakampio_duomenys.Y + staciakampio_duomenys.Aukstis; y++) {
            langeliu_duomenys[x + PLOTIS * y].R = staciakampio_duomenys.R;
            langeliu_duomenys[x + PLOTIS * y].G = staciakampio_duomenys.G;
            langeliu_duomenys[x + PLOTIS * y].B = staciakampio_duomenys.B;
        }
    }
}

void SkaiciuotiRezultatus(int staciakampiu_kiekis, StaciakampioDuomenys staciakampiu_duomenys[], LangelioDuomenys langeliu_duomenys[]) {
    for (int i = 0; i < staciakampiu_kiekis; i++) {
        UzdetiStaciakampi(staciakampiu_duomenys[i], langeliu_duomenys);
    }
}

int HorizontaliPradzia(LangelioDuomenys langeliu_duomenys[]) {
    for (int x = 0; x < PLOTIS; x++) {
        for (int y = 0; y < AUKSTIS; y++) {
            if (langeliu_duomenys[x + PLOTIS * y].R == 255 && langeliu_duomenys[x + PLOTIS * y].G == 255 && langeliu_duomenys[x + PLOTIS * y].B == 255) continue;

            return x;
        }
    }

    return 0;
}

int HorizontaliPabaiga(LangelioDuomenys langeliu_duomenys[]) {
    for (int x = PLOTIS - 1; x >= 0; x--) {
        for (int y = 0; y < AUKSTIS; y++) {
            if (langeliu_duomenys[x + PLOTIS * y].R == 255 && langeliu_duomenys[x + PLOTIS * y].G == 255 && langeliu_duomenys[x + PLOTIS * y].B == 255) continue;

            return x;
        }
    }

    return 0;
}

int VertikaliPradzia(LangelioDuomenys langeliu_duomenys[]) {
    for (int y = 0; y < AUKSTIS; y++) {
        for (int x = 0; x < PLOTIS; x++) {
            if (langeliu_duomenys[x + PLOTIS * y].R == 255 && langeliu_duomenys[x + PLOTIS * y].G == 255 && langeliu_duomenys[x + PLOTIS * y].B == 255) continue;

            return y;
        }
    }

    return 0;
}

int VertikaliPabaiga(LangelioDuomenys langeliu_duomenys[]) {
    for (int y = AUKSTIS - 1; y >= 0; y--) {
        for (int x = 0; x < PLOTIS; x++) {
            if (langeliu_duomenys[x + PLOTIS * y].R == 255 && langeliu_duomenys[x + PLOTIS * y].G == 255 && langeliu_duomenys[x + PLOTIS * y].B == 255) continue;

            return y;
        }
    }

    return 0;
}

void SpausdintiRezultatus(LangelioDuomenys langeliu_duomenys[]) {
    ofstream fout("./U2rez.txt");

    int x1 = HorizontaliPradzia(langeliu_duomenys);
    int x2 = HorizontaliPabaiga(langeliu_duomenys);
    int y1 = VertikaliPradzia(langeliu_duomenys);
    int y2 = VertikaliPabaiga(langeliu_duomenys);

    fout << x2 - x1 << " " << y2 - y2 << endl;

    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            fout
                << langeliu_duomenys[x + PLOTIS * y].R << " "
                << langeliu_duomenys[x + PLOTIS * y].G << " "
                << langeliu_duomenys[x + PLOTIS * y].B << endl;
        }
    }

    fout.close();
}

int main() {
    int staciakampiu_kiekis;
    LangelioDuomenys langeliu_duomenys[PLOTIS * AUKSTIS];
    StaciakampioDuomenys staciakampiu_duomenys[100];

    SkaitytiDuomenis(staciakampiu_kiekis, staciakampiu_duomenys);
    SkaiciuotiRezultatus(staciakampiu_kiekis, staciakampiu_duomenys, langeliu_duomenys);
    SpausdintiRezultatus(langeliu_duomenys);

    // for (int x = 0; x < PLOTIS; x++) {
    //     for (int y = 0; y < AUKSTIS; y++) {
    //         duomenys[x + PLOTIS * y].X = x; 
    //         duomenys[x + PLOTIS * y].Y = y; 
    //         duomenys[x + PLOTIS * y].R = 255; 
    //         duomenys[x + PLOTIS * y].G = 255; 
    //         duomenys[x + PLOTIS * y].B = 255; 
    //     }
    // }

    return 0;
}