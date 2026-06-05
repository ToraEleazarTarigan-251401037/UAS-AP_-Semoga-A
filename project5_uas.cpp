#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// Daftar negara
vector<string> daftarNegara = {
    "indonesia", "nigeria", "australia", "kolombia", "venezuela", "albania", "laos", "rusia", "uganda", "prancis", "monako"
};

// Fungsi untuk membuat tampilan negara dengan huruf yang dihilangkan secara random
string buatTebakan(const string& negara) {
    string tebakan = negara;
    int panjang = negara.length();

    // Tentukan jumlah huruf yang dihilangkan (sekitar 40-60% dari panjang)
    int jumlahHilang = panjang * (40 + rand() % 21) / 100;
    if (jumlahHilang < 1) jumlahHilang = 1;

    // Buat indeks posisi yang akan dihilangkan (jangan hilangkan spasi)
    vector<int> posisi;
    for (int i = 0; i < panjang; i++) {
        if (negara[i] != ' ') {
            posisi.push_back(i);
        }
    }

    // Acak posisi
    for (int i = posisi.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(posisi[i], posisi[j]);
    }

    // Hilangkan huruf sesuai jumlah
    for (int i = 0; i < jumlahHilang && i < (int)posisi.size(); i++) {
        tebakan[posisi[i]] = '_';
    }

    return tebakan;
}

int main() {
    srand(time(0));

    cout << "==============================" << endl;
    cout << "   GAME TEBAK NEGARA  :D      " << endl;
    cout << "==============================" << endl;

    int skor = 0;
    char lagi;

    do {
        // Pilih negara secara random
        int indeks = rand() % daftarNegara.size();
        string negara = daftarNegara[indeks];
        string tebakan = buatTebakan(negara);

        cout << "\nTebak negara: " << tebakan << endl;
        cout << "Negara apakah yang dimaksud? ";

        string jawaban;
        cin >> jawaban;

        // Ubah jawaban ke huruf kecil untuk perbandingan
        transform(jawaban.begin(), jawaban.end(), jawaban.begin(), ::tolower);

        if (jawaban == negara) {
            skor++;
            cout << "Selamat! Anda benar." << endl;
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi." << endl;
            cout << "Jawaban yang benar adalah: " << negara << endl;
        }

        cout << "Skor Anda: " << skor << endl;
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> lagi;
        lagi = tolower(lagi);

    } while (lagi == 'y');

    cout << "\nGame Selesai :D" << endl;
    cout << "Skor akhir Anda: " << skor << endl;
    cout << "Terima kasih sudah bermain!" << endl;

    return 0;
}