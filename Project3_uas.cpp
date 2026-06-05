#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

vector<Barang> inventaris;

void tambahBarang() {
    Barang b;

    cout << "\n=== Tambah Barang ===\n";
    cout << "Kode Barang : ";
    cin >> b.kodeBarang;

    cin.ignore();
    cout << "Nama Barang : ";
    getline(cin, b.namaBarang);

    do {
        cout << "Harga       : ";
        cin >> b.harga;
        if (b.harga < 0) {
            cout << "Error! Harga tidak boleh negatif.\n";
        }
    } while (b.harga < 0);

    do {
        cout << "Stok        : ";
        cin >> b.stok;
        if (b.stok < 0) {
            cout << "Error! Stok tidak boleh negatif.\n";
        }
    } while (b.stok < 0);

    inventaris.push_back(b);
    cout << "Barang berhasil ditambahkan!\n";
}

void tampilkanBarang() {
    cout << "\n=== Daftar Inventaris ===\n";

    if (inventaris.empty()) {
        cout << "Belum ada data barang.\n";
        return;
    }
    
    cout << left
         << setw(15) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(15) << "Harga"
         << setw(10) << "Stok" << endl;

    cout << string(65, '-') << endl;

    for (const auto &b : inventaris) {
        cout << left
             << setw(15) << b.kodeBarang
             << setw(25) << b.namaBarang
             << setw(15) << b.harga
             << setw(10) << b.stok << endl;
    }
}

Barang cariBarangTermahal() {
    cout << "\n=== Barang Termahal ===\n";

    if (inventaris.empty()) {
        cout << "Belum ada data barang.\n";

        Barang kosong;
        return kosong;
    }

    Barang termahal = inventaris[0];

    for (const auto &b : inventaris) {
        if (b.harga > termahal.harga) {
            termahal = b;
        }
    }

    cout << "Kode  : " << termahal.kodeBarang << endl;
    cout << "Nama  : " << termahal.namaBarang << endl;
    cout << "Harga : " << termahal.harga << endl;
    cout << "Stok  : " << termahal.stok << endl;

    return termahal;
}

double hitungTotalInventaris() {
    double total = 0;

    for (const auto &b : inventaris) {
        total += b.harga * b.stok;
    }

    cout << "\nTotal Nilai Inventaris = Rp "
         << total << endl;

    return total;
}

void cekRestock() {
    cout << "\n=== Barang Perlu Restock (Stok < 5) ===\n";

    bool ditemukan = false;

    for (const auto &b : inventaris) {
        if (b.stok < 5) {
            cout << "Kode : " << b.kodeBarang
                 << " | Nama : " << b.namaBarang
                 << " | Stok : " << b.stok << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada barang yang perlu direstock.\n";
    }
}

void updateStok() {
    string kode;

    cout << "\nMasukkan kode barang: ";
    cin >> kode;

    bool ditemukan = false;

    for (auto &b : inventaris) {
        if (b.kodeBarang == kode) {

            int *ptrStok = &b.stok;

            int perubahan;

            cout << "Stok saat ini : " << *ptrStok << endl;
            cout << "Masukkan perubahan stok (+/-): ";
            cin >> perubahan;

            if ((*ptrStok + perubahan) < 0) {
                cout << "Error! Stok tidak boleh negatif.\n";
            } else {
                *ptrStok += perubahan;
                cout << "Stok berhasil diperbarui.\n";
                cout << "Stok baru : " << *ptrStok << endl;
            }

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Barang tidak ditemukan.\n";
    }
}

void menu() {
    int pilihan;

    do {
        cout << "\n==============================\n";
        cout << " SISTEM MANAJEMEN INVENTARIS\n";
        cout << "==============================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang Termahal\n";
        cout << "4. Hitung Total Nilai Inventaris\n";
        cout << "5. Cek Restock (Stok < 5)\n";
        cout << "6. Update Stok\n";
        cout << "7. Keluar\n";
        cout << "Pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilkanBarang();
                break;
            case 3:
                cariBarangTermahal();
                break;
            case 4:
                hitungTotalInventaris();
                break;
            case 5:
                cekRestock();
                break;
            case 6:
                updateStok();
                break;
            case 7:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 7);
}

int main() {
    menu();
    return 0;
}