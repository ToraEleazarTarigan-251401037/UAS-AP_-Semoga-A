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
    SistemParkir(string nama, string id) : namaPetugas(nama), idPetugas(id) {}
    
 
    void tampilkanHeader() {
        cout << "\n========================================\n";
        cout << "     SISTEM PARKIR MALL PRIENAL\n";
        cout << "========================================\n";
        cout << "Petugas : " << namaPetugas << " | ID: " << idPetugas << endl;
        cout << "Kapasitas: " << daftarParkir.size() << "/" << KAPASITAS_MAKS << endl;
        cout << "========================================\n\n";
    }
    

    void tambahKendaraan() {
        if (daftarParkir.size() >= KAPASITAS_MAKS) {
            cout << "MAAF, PARKIRAN SUDAH PENUH! (Maksimal 20 mobil)\n";
            return;
        }
        
        int jumlah;
        cout << "Masukkan jumlah mobil yang akan diparkirkan: ";
        cin >> jumlah;
        
        if (daftarParkir.size() + jumlah > KAPASITAS_MAKS) {
            cout << "MAAF, parkiran hanya dapat memuat " << KAPASITAS_MAKS << " mobil!\n";
            return;
        }
        
        for (int i = 0; i < jumlah; i++) {
            if (daftarParkir.size() >= KAPASITAS_MAKS) break;
            
            Kendaraan k;
            cout << "\n--- Mobil ke-" << (daftarParkir.size() + 1) << " ---\n";
            cout << "Masukkan plat mobil     : "; cin.ignore(); getline(cin, k.plat);
            cout << "Masukkan merk mobil     : "; getline(cin, k.merk);
            cout << "Masukkan warna mobil    : "; getline(cin, k.warna);
            
            k.waktu_masuk = time(0);
            daftarParkir.push_back(k);
            
            cout << "Kendaraan berhasil diparkirkan!\n";
        }
    }
    
  
    void tampilkanDaftar() {
        if (daftarParkir.empty()) {
            cout << "Tidak ada kendaraan yang sedang parkir.\n";
            return;
        }
        
        cout << "DAFTAR MOBIL YANG SEDANG TERPARKIR :\n";
        cout << "==================================\n";
        
        for (size_t i = 0; i < daftarParkir.size(); i++) {
            time_t sekarang = time(0);
            double durasi = difftime(sekarang, daftarParkir[i].waktu_masuk) / 60.0; // dalam menit
            
            cout << "Mobil ke-" << (i+1) << endl;
            cout << "Plat mobil   : " << daftarParkir[i].plat << endl;
            cout << "Merk mobil   : " << daftarParkir[i].merk << endl;
            cout << "Warna mobil  : " << daftarParkir[i].warna << endl;
            cout << "Waktu parkir : " << (int)durasi << " menit" << endl;
            cout << "----------------------------------\n";
        }
    }
    
 
    double hitungBiaya(time_t masuk) {
        time_t sekarang = time(0);
        double menit = difftime(sekarang, masuk) / 60.0;
        double jam = menit / 60.0;
        
    
        if (jam <= 1) return 5000;
        return 5000 + (jam - 1) * 3000;
    }
    
 
    void pembayaran() {
        if (daftarParkir.empty()) {
            cout << "Tidak ada kendaraan yang parkir.\n";
            return;
        }
        
        string platCari;
        cout << "Masukkan plat mobil yang ingin dibayar: ";
        cin.ignore();
        getline(cin, platCari);
        
        auto it = find_if(daftarParkir.begin(), daftarParkir.end(),
            [&](const Kendaraan& k) { return k.plat == platCari; });
        
        if (it == daftarParkir.end()) {
            cout << "PLAT MOBIL TIDAK DITEMUKAN!\n";
            return;
        }
        
        double biaya = hitungBiaya(it->waktu_masuk);
        
        cout << "\n=== DETAIL PEMBAYARAN ===\n";
        cout << "Plat     : " << it->plat << endl;
        cout << "Merk     : " << it->merk << endl;
        cout << "Warna    : " << it->warna << endl;
        cout << "Biaya    : Rp" << fixed << setprecision(0) << biaya << endl;
        cout << "========================\n";
        
        char konfirmasi;
        cout << "Apakah pembayaran sudah dilakukan? (y/n): ";
        cin >> konfirmasi;
        
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            daftarParkir.erase(it);
            cout << "Kendaraan berhasil keluar. Terima kasih!\n";
        }
    }
    

    void jalankan() {
        int pilihan;
        do {
            tampilkanHeader();
            cout << "Silahkan input opsi berikut dalam bentuk angka:\n";
            cout << "1. Tambahkan Daftar Kendaraan\n";
            cout << "2. Tampilkan Daftar Kendaraan\n";
            cout << "3. Pembayaran\n";
            cout << "4. Keluar Program\n";
            cout << "Masukkan opsi : ";
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
                    cout << "\nTERIMA KASIH ATAS KERJASAMANYA!\n";
                    cout << "SELAMAT BERTUGAS!\n";
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
            }
            
            if (pilihan != 4) {
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
            }
        } while (pilihan != 4);
    }
};

int main() {


    string nama = "Endriano Kitswanto";
    string id = "231401073";
    
    SistemParkir parkir(nama, id);
    
    cout << "\nSELAMAT DATANG DI PORTAL PARKIR KHUSUS MOBIL MALL PRIENAL\n";
    cout << "Kami senang Anda telah hadir.\n\n";
    
    parkir.jalankan();
    
    return 0;
}