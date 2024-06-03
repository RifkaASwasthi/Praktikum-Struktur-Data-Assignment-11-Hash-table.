# <h1 align="center">Laporan Praktikum 11 Modul Heap</h1>
<p align="center">Rifka Annisa Swasthi</p>

## Dasar Teori

Hash table adalah struktur data yang digunakan untuk menyimpan data dalam format array dimana setiap nilai data memiliki nilai indeks uniknya tersendiri. Fungsi utama hash table adalah mempercepat proses akses data karena data dalam bentuk array menawarkan kelebihan dalam efisiensi waktu operasi.

Teknik hash table[1]

1. Hashing
proses mengganti kunci yang diberikan atau string karakter menjadi nilai lain

2. Linear Probing
setiap sel dari hash table menyimpan satu pasangan kunci nilai. saat fungsi hash menyebabkan collison dengan memetakan kunci baru ke sel hash table yang sudah ditempati oleh kunci laim, maka linear probing akan mencari tabel untuk lokasi bebas terdekat dan menyisipkan kunci baru.

Operasi struktur data [2]

1. Pencarian (Search)
untuk mencari elemen atau data dalam hash tabel berdasarkan kunci atau indeksnya

2. Penyisipan (insertion)
untuk menyisipkan elemen atau data kedalam hash table.

3. Penghapusan (Deletion)
untuk menghapus elemen atau data dari hash table

4. update
untuk mengubah nilai elemen data yang sudah ada di hash table

5. Collision Handling
collision adalah ketika dua data atau lebih elemen memiliki indeks yang sama setelah fungsi hash, operasi ini digunakan untuk menangani collison dan memastikan bahwa elemen dalam indeks dapat disimpan dan diakses dengan benar.

6. Resize
untuk mengubah ukuran hash table jika jumlah elemen atau data yang disimpan melebihi kapasitas yang dutentukan

7. iterasi
operasi yang digunakan untuk mengakses dan memproses semua data atau elemen data yang ada didalam hash table secara berurutan. 




## Guided 

### 1. 

```C++
#include <iostream>
using namespace std;
const int MAX_SIZE = 10;

// Fungsi hash sederhana
int hash_func(int key) {
    return key % MAX_SIZE;
}

// Struktur data untuk setiap node
struct Node {
    int key;
    int value;
    Node* next;
    Node(int key, int value) : key(key), value(value), next(nullptr) {}
};

// Class hash table
class HashTable {
private:
    Node** table;
public:
    HashTable() {
        table = new Node*[MAX_SIZE]();
    }
    ~HashTable() {
        for (int i = 0; i < MAX_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Insertion
    void insert(int key, int value) {
        int index = hash_func(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        Node* node = new Node(key, value);
        node->next = table[index];
        table[index] = node;
    }

    // Searching
    int get(int key) {
        int index = hash_func(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return -1;
    }

    // Deletion
    void remove(int key) {
        int index = hash_func(key);
        Node* current = table[index];
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Traversal
    void traverse() {
        for (int i = 0; i < MAX_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                cout << current->key << ": " << current->value << endl;
                current = current->next;
            }
        }
    }
};

int main() {
    HashTable ht;
    // Insertion
    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(3, 30);

    // Searching
    cout << "Get key 1: " << ht.get(1) << endl;
    cout << "Get key 4: " << ht.get(4) << endl;
   
    // Deletion
    ht.remove(4);
   
    // Traversal
    ht.traverse();
   
    return 0;
}

```
Kode di atas adalah contoh dari hash table yang menggunakan chaining array pointer ke struktur node yang berisis pasangan kunci ke pointer selanjutnya. pertama kita mendeklarasikan konstanta dan fungsi hash. node untuk mendefinisikan node dalam linked list ke pointer selanjutnya. insert untuk menambahkan atau memperbarui pasangan kunci ke tabel hash. fungsi get untuk mengembalikan nilai yang terkait dengna kunci tertentu. remove untuk menghapus dan traverse untuk menampilkan semua pasangan kunci nilai dalam hash table. yang terakhir fungsi diinisasi dan memberikan operasi penyisipan, pencarian, penghapusan dan penelusuran.

### 2. 

```C++
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int TABLE_SIZE = 11;

string name;
string phone_number;

class HashNode {
public:
    string name;
    string phone_number;

    HashNode(string name, string phone_number) {
        this->name = name;
        this->phone_number = phone_number;
    }
};

class HashMap {
private:
    vector<HashNode*> table[TABLE_SIZE];
public:
    int hashFunc(string key) {
        int hash_val = 0;
        for (char c : key) {
            hash_val += c;
        }
        return hash_val % TABLE_SIZE;
    }

    void insert(string name, string phone_number) {
        int hash_val = hashFunc(name);

        for (auto node : table[hash_val]) {
            if (node->name == name) {
                node->phone_number = phone_number;
                return;
            }
        }
        table[hash_val].push_back(new HashNode(name, phone_number));
    }

    void remove(string name) {
        int hash_val = hashFunc(name);

        for (auto it = table[hash_val].begin(); it != table[hash_val].end(); it++) {
            if ((*it)->name == name) {
                table[hash_val].erase(it);
                return;
            }
        }
    }

    string searchByName(string name) {
        int hash_val = hashFunc(name);
        for (auto node : table[hash_val]) {
            if (node->name == name) {
                return node->phone_number;
            }
        }
        return "";
    }

    void print() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            for (auto pair : table[i]) {
                if (pair != nullptr) {
                    cout << "[" << pair->name << ", " << pair->phone_number << "]";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    HashMap employee_map;

    employee_map.insert("Mistah", "1234");
    employee_map.insert("Pastah", "5678");
    employee_map.insert("Ghana", "91011");

    cout << "Nomer Hp Mistah : " << employee_map.searchByName("Mistah") << endl;
    cout << "Phone Hp Pastah : " << employee_map.searchByName("Pastah") << endl;

    employee_map.remove("Mistah");

    cout << "Nomer Hp Mistah setelah dihapus : " << employee_map.searchByName("Mistah") << endl << endl;

    cout << "Hash Table : " << endl;

    employee_map.print();

    return 0;
}

```
Kode di atas adalah contoh dari hash map yang digunakan ntuk menyimpan dan mengelola informasi nomor telepon menggunakan chaining. pertama mendeklarasikan konstanta dan variabel. kelas hashnode untuk merepresentasikan sebuah node dalam hash tabel. hashmap untuk menghitung nilai hash dari sebuah string dengan menjumlahkan nilai dan setiap karakter string dan mengambil modulud table size. insert utnuk menambahkan, jika nama sudah ada di tabel nomor telepon diperbarui kalau tidak node baru ditambahkan, remove untuk menghapus node dengn nama tertentu. search by name untuk mencari berdasarkan nama, print untuk menampilkan selurus isi hash dan terakhir main hash map diinisasi dan beberapa operasi dilakukan penyisipan, penghapusan dan pencetakan.

## Unguided 

### 1. 
Implementasikan hash table untuk menyimpan data mahasiswa. Setiap mahasiswa memiliki NIM dan nilai. Implementasikan fungsi untuk menambahkan data baru, menghapus data, mencari data berdasarkan NIM, dan mencari data berdasarkan nilai. Dengan ketentuan :
a.	Setiap mahasiswa memiliki NIM dan nilai.
b.	Program memiliki tampilan pilihan menu berisi poin C.
c.	Implementasikan fungsi untuk menambahkan data baru, menghapus data, mencari data berdasarkan NIM, dan mencari data berdasarkan rentang nilai (80 – 90).
c++

```C++
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

```
#### Output:
![Screenshot 2024-06-03 071311](https://github.com/RifkaASwasthi/Praktikum-Struktur-Data-Assignment-11-Hash-table./assets/162097297/46e99a04-12f4-4b19-8a26-dc54e29160f1)

Kode di atas digunakan untuk mengelola data mahasiswa menggunakan hash tablw, pertama mendeklarasikan struktur mahasiswa dengan nim dan nilai. unordered untuk menyimpan data mahasiswa, void tambahdata untuk menambahkan data dengan ditimpa apabila data sebelumnya sudah ada, void menghapus untuk menghapus data berdasarkan nim, void cari data utnuk mencari data, voidcaridata nilai mencaru data berdasarkan nilai cout mahasiswa dengan nilai antara jika data ada atau tidak ada mahasiswa dengan nilai antara jika tidak ada. main untuk memberikan menu menambahkan, menghapus, mencari data atau keluar dari program. 

#### Full code Screenshot:
![Screenshot 2024-06-03 071409](https://github.com/RifkaASwasthi/Praktikum-Struktur-Data-Assignment-11-Hash-table./assets/162097297/dcb13a38-395a-4867-aec5-4910addc7e2e)


## Kesimpulan
Hash table adalah struktur data yang digunakan untuk menyimpan data dalam format array dimana setiap nilai data memiliki nilai indeks uniknya tersendiri. 

Teknik hash table ada dua yaitu hashing dan linear probing


Operasi struktur data pada hash table ada,Pencarian (Search), Penyisipan (insertion)
,Penghapusan (Deletion),update,Collision Handling,Resize,iterasi. 






## Referensi
[1] 2022. Apa itu hash table dan bagaimana penggunaanya[Artikel], algorit.ma.

[2] Annisa. 2023, Struktur Data Hash Table:Pengertian, Cara Kerja dan Operasi Hash Table, Fakultas Ilmu Komputer dan Teknologi Informasi[Artikel], fikti.umsu.ac.id.

