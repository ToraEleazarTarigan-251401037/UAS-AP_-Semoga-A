// =============================================================
//  main.cpp  -  Game Tebak Kata
//  Dibuat untuk  : Nisa (Mahasiswa Semester 2)
//  Deskripsi     : Game tebak kata berbasis CLI dengan fitur
//                  tingkat kesulitan, hint, skor, & leaderboard.
// =============================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TebakKata.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    bersihkanLayar();
    tampilkanBanner();

    cout << "\nSelamat datang di Game Tebak Kata!\n";
    cout << "Masukkan nama kamu : ";
    string namaPemain;
    getline(cin, namaPemain);

    // Loop
    char ulang = 'Y';
    while (toupper(ulang) == 'Y') {
        bersihkanLayar();
        tampilkanBanner();
        cout << "\nHalo, " << namaPemain << "! Mari bermain.\n";

        // Jalankan satu ronde penuh
        mainkanRonde(namaPemain);

        // Tanya apakah ingin bermain lagi
        cout << "Apakah Anda ingin bermain lagi? (Y/N): ";
        cin >> ulang;
    }

    // Pesan penutup
bersihkanLayar();
tampilkanBanner();

cout << "\nTerima kasih sudah bermain, "
     << namaPemain << "!\n";

tampilkanLeaderboard();

cout << "\nSampai jumpa! ";

cout << "\n\nTekan Enter untuk keluar...";
cin.ignore();
cin.get();

return 0;
}