
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "project2.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    bersihkanLayar();
    tampilkanBanner();

    cout << "\nSelamat datang di Game Tebak Kata!\n";
    cout << "Masukkan nama kamu : ";
    string namaPemain;
    getline(cin, namaPemain);

  
    char ulang = 'Y';
    while (toupper(ulang) == 'Y') {
        bersihkanLayar();
        tampilkanBanner();
        cout << "\nHalo, " << namaPemain << "! Mari bermain.\n";

       
        mainkanRonde(namaPemain);

     
        cout << "Apakah Anda ingin bermain lagi? (Y/N): ";
        cin >> ulang;
    }


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
