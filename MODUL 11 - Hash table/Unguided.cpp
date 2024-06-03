#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Struktur data Mahasiswa
struct Mahasiswa {
    string NIM;
    int nilai;
};

// Hash table untuk menyimpan data mahasiswa
unordered_map<string, Mahasiswa> hashTable;

// Fungsi untuk menambahkan data mahasiswa baru
void tambahData(const string& NIM, int nilai) {
    Mahasiswa mhs = {NIM, nilai};
    hashTable[NIM] = mhs;
    cout << "Data mahasiswa dengan NIM " << NIM << " berhasil ditambahkan." << endl;
}

// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void hapusData(const string& NIM) {
    if (hashTable.erase(NIM)) {
        cout << "Data mahasiswa dengan NIM " << NIM << " berhasil dihapus." << endl;
    } else {
        cout << "Data mahasiswa dengan NIM " << NIM << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk mencari data mahasiswa berdasarkan NIM
void cariDataNIM(const string& NIM) {
    auto it = hashTable.find(NIM);
    if (it != hashTable.end()) {
        cout << "Mahasiswa ditemukan: NIM = " << it->second.NIM << ", Nilai = " << it->second.nilai << endl;
    } else {
        cout << "Mahasiswa dengan NIM " << NIM << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk mencari data mahasiswa berdasarkan rentang nilai
void cariDataNilai(int minNilai, int maxNilai) {
    vector<Mahasiswa> hasil;
    for (const auto& kv : hashTable) {
        if (kv.second.nilai >= minNilai && kv.second.nilai <= maxNilai) {
            hasil.push_back(kv.second);
        }
    }
    if (!hasil.empty()) {
        cout << "Mahasiswa dengan nilai antara " << minNilai << " dan " << maxNilai << " :" << endl;
        for (const auto& mhs : hasil) {
            cout << "NIM = " << mhs.NIM << ", Nilai = " << mhs.nilai << endl;
        }
    } else {
        cout << "Tidak ada mahasiswa dengan nilai antara " << minNilai << " dan " << maxNilai << "." << endl;
    }
}

int main() {
    int pilihan;
    string NIM;
    int nilai;

    do {
        cout << "\nMenu: " << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Hapus Data" << endl;
        cout << "3. Cari Data Berdasarkan NIM" << endl;
        cout << "4. Cari Data Berdasarkan Rentang Nilai (80-90)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> NIM;
                cout << "Masukkan Nilai: ";
                cin >> nilai;
                tambahData(NIM, nilai);
                break;
            case 2:
                cout << "Masukkan NIM: ";
                cin >> NIM;
                hapusData(NIM);
                break;
            case 3:
                cout << "Masukkan NIM: ";
                cin >> NIM;
                cariDataNIM(NIM);
                break;
            case 4:
                cariDataNilai(80, 90);
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 5);

    return 0;
}

