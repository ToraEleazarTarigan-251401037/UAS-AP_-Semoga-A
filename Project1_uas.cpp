#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;


struct Kendaraan {
    string plat;
    string merk;
    string warna;
    time_t waktu_masuk;
};

class SistemParkir {
private:
    vector<Kendaraan> daftarParkir;
    const int KAPASITAS_MAKS = 20;

    string namaPetugas;
    string idPetugas;

public:

    SistemParkir(string nama, string id) {
        namaPetugas = nama;
        idPetugas = id;
    }

    
    void tampilkanHeader() {

        cout << "\n===============================================================\n";
        cout << "Nama Petugas : " << namaPetugas << endl;
        cout << "ID Petugas   : " << idPetugas << endl;

        cout << "\n";
        cout << "                    TERIMA KASIH ATAS KERJASAMANYA !\n";
        cout << "---------------------- S E L A M A T  B E R T U G A S ----------------------\n";
        cout << "===============================================================\n";

        cout << "\nKapasitas Parkir : "
             << daftarParkir.size()
             << "/"
             << KAPASITAS_MAKS
             << "\n\n";
    }


    void tambahKendaraan() {

        if (daftarParkir.size() >= KAPASITAS_MAKS) {
            cout << "\nMAAF, PARKIRAN SUDAH PENUH!\n";
            return;
        }

        int jumlah;

        cout << "\nMasukkan jumlah mobil yang akan diparkirkan : ";
        cin >> jumlah;

        if (daftarParkir.size() + jumlah > KAPASITAS_MAKS) {
            cout << "\nParkiran hanya dapat menampung "
                 << KAPASITAS_MAKS
                 << " mobil!\n";
            return;
        }

        cin.ignore();

        for (int i = 0; i < jumlah; i++) {

            Kendaraan k;

            cout << "\n=================================\n";
            cout << "DATA MOBIL KE-" << daftarParkir.size() + 1 << endl;
            cout << "=================================\n";

            cout << "Masukkan Plat Mobil  : ";
            getline(cin, k.plat);

            cout << "Masukkan Merk Mobil  : ";
            getline(cin, k.merk);

            cout << "Masukkan Warna Mobil : ";
            getline(cin, k.warna);

            k.waktu_masuk = time(0);

            daftarParkir.push_back(k);

            cout << "\nKendaraan berhasil diparkirkan!\n";
        }
    }

  
    void tampilkanDaftar() {

        if (daftarParkir.empty()) {
            cout << "\nTidak ada kendaraan yang sedang parkir.\n";
            return;
        }

        cout << "\n===============================================================\n";
        cout << "              DAFTAR KENDARAAN YANG SEDANG PARKIR\n";
        cout << "===============================================================\n";

        for (size_t i = 0; i < daftarParkir.size(); i++) {

            time_t sekarang = time(0);

            double durasi =
                difftime(sekarang,
                         daftarParkir[i].waktu_masuk) / 60.0;

            cout << "\nMobil Ke-" << i + 1 << endl;
            cout << "Plat Mobil   : " << daftarParkir[i].plat << endl;
            cout << "Merk Mobil   : " << daftarParkir[i].merk << endl;
            cout << "Warna Mobil  : " << daftarParkir[i].warna << endl;
            cout << "Lama Parkir  : " << (int)durasi << " menit" << endl;

            cout << "---------------------------------------------------------------\n";
        }
    }

   
    double hitungBiaya(time_t masuk) {

        time_t sekarang = time(0);

        double menit = difftime(sekarang, masuk) / 60.0;
        double jam = menit / 60.0;

        if (jam <= 1)
            return 5000;

        return 5000 + ((jam - 1) * 3000);
    }

  
    void pembayaran() {

        if (daftarParkir.empty()) {
            cout << "\nTidak ada kendaraan yang sedang parkir.\n";
            return;
        }

        string platCari;

        cin.ignore();

        cout << "\nMasukkan plat mobil yang ingin dibayar : ";
        getline(cin, platCari);

        auto it = find_if(
            daftarParkir.begin(),
            daftarParkir.end(),
            [&](const Kendaraan& k) {
                return k.plat == platCari;
            });

        if (it == daftarParkir.end()) {
            cout << "\nPLAT MOBIL TIDAK DITEMUKAN!\n";
            return;
        }

        double biaya = hitungBiaya(it->waktu_masuk);

        cout << "\n================================================\n";
        cout << "               DETAIL PEMBAYARAN\n";
        cout << "================================================\n";

        cout << "Plat Mobil : " << it->plat << endl;
        cout << "Merk Mobil : " << it->merk << endl;
        cout << "Warna      : " << it->warna << endl;

        cout << "Biaya      : Rp "
             << fixed
             << setprecision(0)
             << biaya << endl;

        cout << "================================================\n";

        char konfirmasi;

        cout << "\nApakah pembayaran sudah dilakukan? (Y/N) : ";
        cin >> konfirmasi;

        if (konfirmasi == 'Y' || konfirmasi == 'y') {

            daftarParkir.erase(it);

            cout << "\nKendaraan berhasil keluar dari parkiran.\n";
            cout << "Terima kasih.\n";
        }
    }

    
    void jalankan() {

        int pilihan;

        do {

            tampilkanHeader();

            cout << "Silahkan input opsi berikut dalam bentuk angka.\n\n";

            cout << "1. Tambahkan Daftar Kendaraan\n";
            cout << "2. Tampilkan Daftar Kendaraan\n";
            cout << "3. Pembayaran\n";
            cout << "4. Keluar Program\n";

            cout << "\nMasukkan opsi : ";
            cin >> pilihan;

            switch (pilihan) {

            case 1:
                tambahKendaraan();
                break;

            case 2:
                tampilkanDaftar();
                break;

            case 3:
                pembayaran();
                break;

            case 4:
                cout << "\n================================================\n";
                cout << "      TERIMA KASIH ATAS KERJASAMANYA !\n";
                cout << "            SELAMAT BERTUGAS\n";
                cout << "================================================\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
            }

            if (pilihan != 4) {
                cout << "\nTekan ENTER untuk melanjutkan...";
                cin.ignore();
                cin.get();
            }

        } while (pilihan != 4);
    }
};

int main() {

    string nama;
    string id;

    cout << "=====================================================================\n";
    cout << "---------------------- S E L A M A T  D A T A N G -------------------\n";
    cout << "                     DI PORTAL PARKIR KHUSUS MOBIL\n";
    cout << "                             MALL PRIENAL\n";
    cout << "=====================================================================\n\n";

    cout << "Kami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan\n";
    cout << "bertugas hari ini.\n\n";

    cout << "Masukkan nama : ";
    getline(cin, nama);

    cout << "Masukkan ID   : ";
    getline(cin, id);

    SistemParkir parkir(nama, id);

    parkir.jalankan();

    return 0;
}