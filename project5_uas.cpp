#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// Daftar negara yang tersedia
vector<string> daftarNegara = {
    "indonesia", "nigeria", "australia", "kolombia", "venezuela",
    "albania", "laos", "rusia", "uganda", "prancis", "monako"
};

// Menyembunyikan sebagian huruf dari nama negara
string buatHasil(const string& negara) {
    string tersamar = negara;
    int targetSembunyi = negara.length() * (40 + rand() % 21) / 100;
    if (targetSembunyi < 1) targetSembunyi = 1;

    int progres = 0;
    do {
        int posAcak = rand() % negara.length();
        if (tersamar[posAcak] != ' ' && tersamar[posAcak] != '_') {
            tersamar[posAcak] = '_';
            progres++;
        }
    } while (progres < targetSembunyi);

    return tersamar;
}

// Main loop game
int main() {
    srand(time(0));

    cout << "==============================\n";
    cout << "      GAME TEBAK NEGARA       \n";
    cout << "==============================\n";

    int skor = 0;
    char ulang = 'y';

    while (tolower(ulang) == 'y') {
        string negara = daftarNegara[rand() % daftarNegara.size()];
        string tampilan = buatHasil(negara);

        cout << "\nTebak negara: " << tampilan << "\n";
        cout << "Negara apakah yang dimaksud? ";

        if (skor > 0) cin.ignore();

        string jawaban;
        getline(cin, jawaban);

        for (char& huruf : jawaban)
            huruf = tolower(huruf);

        if (jawaban == negara) {
            skor++;
            cout << "Selamat! Anda benar.\n";
        } else {
            cout << "Maaf, jawaban anda salah. Coba lagi.\n";
        }

        cout << "Skor Anda: " << skor << "\n";
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> ulang;
    }

    cout << "\nGame Selesai :D\n";
    return 0;
}