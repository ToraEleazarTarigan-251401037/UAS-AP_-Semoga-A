#ifndef TEBAK_KATA_H
#define TEBAK_KATA_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

//  KONSTANTA & BANK KATA

const int JUMLAH_KATA      = 15;
const int MAX_LEADERBOARD  = 5;

const string bankKata[JUMLAH_KATA] = {
    "programming", "komputer", "logika", "variabel",
    "fungsi", "pointer", "program", "server",
    "compiler", "database", "jaringan", "latihan",
    "keyboard", "monitor", "laptop"
};


//  STRUCT

// Menyimpan state permainan yang sedang berjalan
struct KataGame {
    string kataAsli;          
    string statusTebakan;   
    int sisaNyawa;        
};

// Menyimpan satu entri skor di leaderboard
struct Skor {
    string namaPemain;
    int    nilai;
    string tingkatKesulitan;
};


//  VARIABEL GLOBAL  -  Leaderboard

Skor  leaderboard[MAX_LEADERBOARD];
int   jumlahSkorTersimpan = 0;


//  UTILITAS TAMPILAN


// Bersihkan layar (cross-platform)
void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void cetakGaris(char karakter = '=', int panjang = 50) {
    for (int i = 0; i < panjang; i++) cout << karakter;
    cout << "\n";
}


void tampilkanBanner() {
    cetakGaris('=');
    cout << "       GAME TEBAK KATA - by Nisa\n";
    cetakGaris('=');
}


//  INISIALISASI & PILIH KESULITAN

// Pilih kata acak dari bank kata
string pilihKataAcak() {
    return bankKata[rand() % JUMLAH_KATA];
}

// Inisialisasi struct KataGame via pointer
void inisialisasiGame(KataGame* game, const string& kata, int nyawa) {
    game->kataAsli      = kata;
    game->sisaNyawa     = nyawa;
    game->statusTebakan = string(kata.length(), '_');  // semua underscore
}

// Tampilkan menu kesulitan dan kembalikan jumlah max kesalahan
int pilihKesulitan() {
    int pilihan;
    cout << "\nPilih Tingkat Kesulitan:\n";
    cout << "  1. Easy   (8 nyawa)\n";
    cout << "  2. Medium (6 nyawa)\n";
    cout << "  3. Hard   (4 nyawa)\n";
    cout << "Pilihan (1/2/3): ";

    while (true) {
        cin >> pilihan;
        if (pilihan == 1) { cout << "\n[Mode: EASY]\n";   return 8; }
        if (pilihan == 2) { cout << "\n[Mode: MEDIUM]\n"; return 6; }
        if (pilihan == 3) { cout << "\n[Mode: HARD]\n";   return 4; }
        cout << "Pilihan tidak valid. Masukkan 1, 2, atau 3: ";
    }
}

// Kembalikan string nama kesulitan berdasarkan nyawa awal
string namaKesulitan(int nyawaAwal) {
    if (nyawaAwal == 8) return "Easy";
    if (nyawaAwal == 6) return "Medium";
    return "Hard";
}

//  VALIDASI & PROSES TEBAKAN

// Cek apakah huruf sudah pernah ditebak (benar atau salah)
bool sudahDitebak(char huruf,
                  const string& statusTebakan,
                  const char tebakanSalah[],
                  int jumlahSalah)
{
    // Cek di status tebakan (huruf benar yang sudah terbuka)
    for (char c : statusTebakan)
        if (tolower(c) == tolower(huruf)) return true;

    // Cek di array tebakan salah
    for (int i = 0; i < jumlahSalah; i++)
        if (tolower(tebakanSalah[i]) == tolower(huruf)) return true;

    return false;
}

// Proses tebakan pemain; modifikasi KataGame via pointer
// Kembalikan: true jika tebakan benar, false jika salah
bool prosesTebakan(KataGame* game,
                   char huruf,
                   char tebakanSalah[],
                   int* jumlahSalah)
{
    bool ada = false;

    // cek seluruh huruf dalam kata
    for (size_t i = 0; i < game->kataAsli.length(); i++) {

        // bandingkan tanpa membedakan huruf besar/kecil
        if (tolower(game->kataAsli[i]) ==
            tolower(huruf))
        {
            // buka semua posisi huruf yang sama
            game->statusTebakan[i] =
                game->kataAsli[i];

            ada = true;
        }
    }

    // jika huruf tidak ditemukan
    if (!ada) {

        tebakanSalah[*jumlahSalah] =
            tolower(huruf);

        (*jumlahSalah)++;

        game->sisaNyawa--;
    }

    return ada;
}

//  CEK KONDISI MENANG / KALAH

bool cekMenang(const KataGame* game) {
    return game->statusTebakan == game->kataAsli;
}

bool cekKalah(const KataGame* game) {
    return game->sisaNyawa <= 0;
}


//  TAMPILAN GAME


void tampilkanHUD(const KataGame* game,
                  const char tebakanSalah[],
                  int jumlahSalah)
{
    // Gambar nyawa sebagai v
    cout << "\nNyawa: ";
    for (int i = 0; i < game->sisaNyawa; i++) cout << "[v] ";
    cout << "\n";

    // Kata yang sebagian terbuka
    cout << "\nKata  : ";
    for (char c : game->statusTebakan) cout << c << " ";
    cout << "\n";

    // Daftar huruf salah
    cout << "\nHuruf salah: ";
    if (jumlahSalah == 0) {
        cout << "(belum ada)";
    } else {
        for (int i = 0; i < jumlahSalah; i++) {
            cout << tebakanSalah[i];
            if (i < jumlahSalah - 1) cout << ", ";
        }
    }
    cout << "\n\n";
    cetakGaris('-');
}


//  FITUR HINT

// Buka huruf pertama kata rahasia; kurangi 1 nyawa via pointer
void gunakanHint(KataGame* game) {
    if (game->sisaNyawa <= 1) {
        cout << ">> Nyawa tidak cukup untuk menggunakan hint!\n";
        return;
    }
    // Buka huruf pertama
    game->statusTebakan[0] = game->kataAsli[0];
    game->sisaNyawa--;    // biaya 1 nyawa
    cout << ">> Hint: huruf pertama adalah '" << game->kataAsli[0] << "' (-1 nyawa)\n";
}

//  SISTEM SKOR

// Hitung skor berdasarkan sisa nyawa dan kesulitan
int hitungSkor(int sisaNyawa, int nyawaAwal) {
    int multiplier = 1;
    if (nyawaAwal == 6) multiplier = 2;   // Medium
    if (nyawaAwal == 4) multiplier = 3;   // Hard
    return sisaNyawa * 100 * multiplier;
}

// Simpan skor ke leaderboard (insertion sort sederhana, descending)
void simpanSkor(const string& nama, int nilai, const string& kesulitan) {
    if (jumlahSkorTersimpan < MAX_LEADERBOARD) {
        leaderboard[jumlahSkorTersimpan] = {nama, nilai, kesulitan};
        jumlahSkorTersimpan++;
    } else {
        // Ganti skor terkecil jika skor baru lebih besar
        int idxMin = 0;
        for (int i = 1; i < MAX_LEADERBOARD; i++)
            if (leaderboard[i].nilai < leaderboard[idxMin].nilai)
                idxMin = i;
        if (nilai > leaderboard[idxMin].nilai)
            leaderboard[idxMin] = {nama, nilai, kesulitan};
    }

    // Urutkan descending (bubble sort)
    for (int i = 0; i < jumlahSkorTersimpan - 1; i++)
        for (int j = 0; j < jumlahSkorTersimpan - 1 - i; j++)
            if (leaderboard[j].nilai < leaderboard[j + 1].nilai)
                swap(leaderboard[j], leaderboard[j + 1]);
}

void tampilkanLeaderboard() {
    cetakGaris('*');
    cout << "           == LEADERBOARD ==\n";
    cetakGaris('*');
    if (jumlahSkorTersimpan == 0) {
        cout << "  (Belum ada skor tersimpan)\n";
    } else {
        cout << "  Rank  Nama              Skor    Kesulitan\n";
        cetakGaris('-');
        for (int i = 0; i < jumlahSkorTersimpan; i++) {
            cout << "   " << (i + 1) << ".   ";
            // Padding nama
            string nama = leaderboard[i].namaPemain;
            cout << nama;
            for (int p = nama.length(); p < 18; p++) cout << ' ';
            cout << leaderboard[i].nilai << "    "
                 << leaderboard[i].tingkatKesulitan << "\n";
        }
    }
    cetakGaris('*');
}


void mainkanRonde(const string& namaPemain) {
    //Pilih kesulitan
    int nyawaAwal = pilihKesulitan();
    string kata   = pilihKataAcak();

    //Inisialisasi state via pointer
    KataGame game;
    inisialisasiGame(&game, kata, nyawaAwal);

    // --- Data tebakan salah ---
    char tebakanSalah[26];
    int  jumlahSalah = 0;

    bool selesai = false;

    //LOOP UTAMA PERMAINAN 
    while (!selesai) {
        bersihkanLayar();
        tampilkanBanner();
        tampilkanHUD(&game, tebakanSalah, jumlahSalah);

        // Tawaran hint
        cout << "Masukkan satu huruf untuk menebak kata, atau ketik '?' untuk bantuan (mengurangi 1 nyawa):";
        char input;
        cin >> input;

        //Proses hint
        if (input == '?') {
            gunakanHint(&game);
        }
        //Proses huruf biasa
        else if (isalpha(input)) {
            input = tolower(input);

            // Cek duplikasi
            if (sudahDitebak(input, game.statusTebakan,
                             tebakanSalah, jumlahSalah)) {
                cout << "\n>> Huruf '" << input
                     << "' sudah pernah ditebak! Coba huruf lain.\n";
                cout << "   (Tekan Enter untuk lanjut...)\n";
                cin.ignore(); cin.get();
                continue;   // tidak kurangi nyawa
            }

            bool benar = prosesTebakan(&game, input,
                                       tebakanSalah, &jumlahSalah);
            if (benar)
                cout << "\n>> ? Huruf '" << input << "' ada dalam kata!\n";
            else
                cout << "\n>> [x] Huruf '" << input << "' tidak ada. Nyawa berkurang!\n";

            cout << "   (Tekan Enter untuk lanjut...)\n";
            cin.ignore(); cin.get();
        } else {
            cout << "\n>> Input tidak valid! Masukkan satu huruf.\n";
            cout << "   (Tekan Enter untuk lanjut...)\n";
            cin.ignore(); cin.get();
            continue;
        }

        // Cek kondisi akhir 
        if (cekMenang(&game)) {
            bersihkanLayar();
            tampilkanBanner();
            cout << endl;
            cout << "  *** SELAMAT, " << namaPemain << "! KAMU MENANG!!!!! ***\n";
            cout << "  Kata rahasia : " << game.kataAsli << "\n";
            int skor = hitungSkor(game.sisaNyawa, nyawaAwal);
            cout << "  Skor kamu    : " << skor << "\n";
            
            simpanSkor(namaPemain, skor, namaKesulitan(nyawaAwal));
            selesai = true;
        } else if (cekKalah(&game)) {
            bersihkanLayar();
            tampilkanBanner();
            cetakGaris('*');
            cout << "  xxx GAME OVER, " << namaPemain << "! NYAWA HABIS.\n";
            cout << "  Kata rahasia : " << game.kataAsli << "\n";
            cetakGaris('*');
            selesai = true;
        }
    }

    // Tampilkan leaderboard setelah setiap ronde
    cout << "\n";
    tampilkanLeaderboard();
}

#endif
