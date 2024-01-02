#include<iostream>
#include<algorithm>
#include <stack>
using namespace std;

const int MAX_MOBIL = 100;

struct Mobil {
    string platNomor;
    int biayaParkir;
};

struct Antrian {
    Mobil mobil[MAX_MOBIL];
    int jumlahMobil;
    int totalPendapatan;
};

// Fungsi pembanding untuk sorting berdasarkan platNomor
bool compareByPlatNomor(const Mobil& a, const Mobil& b) {
    return a.platNomor < b.platNomor;
}

//dengan pointer ke struct 'antrian'
void tambahAntrian(Antrian* antrian, const Mobil& mobil) {
    if (antrian->jumlahMobil < MAX_MOBIL) {
        // Gunakan stack untuk menyimpan sementara mobil yang baru ditambahkan
        //membuat stack dengan tipe data 'Mobil' yang akan digunakan untuk menyimpan data sementara mobil2 sebelum masuk didalam antrian
        stack<Mobil> mobilStack;

        // Pindahkan mobil yang ada dalam antrian ke dalam stack yang akan terus berjalan selama stack mobil belum kosong
        while (!mobilStack.empty()) {
            mobilStack.push(antrian->mobil[antrian->jumlahMobil - 1]); // Menambahkan mobil dari antrian ke dalam stack.
            antrian->jumlahMobil--;
        }
        // Tambahkan mobil baru ke dalam stack
        mobilStack.push(mobil);

        // Pindahkan kembali mobil dari stack ke dalam antrian
        while (!mobilStack.empty()) {
            antrian->mobil[antrian->jumlahMobil] = mobilStack.top();
            antrian->jumlahMobil++; //menambah jumlah mobil didal satck
            mobilStack.pop(); //menghapus data mobil didalam stack
        }

        cout << "Mobil berhasil ditambahkan ke antrian parkir." << endl;
    } else {
        cout << "Antrian parkir penuh, tidak dapat menambahkan mobil." << endl;
    }
}

//program secara umum menggunakan antrian queue untuk mengelola mobil yang parkir
//Fungsi ini menggambarkan konsep dasar dari antrian, di mana mobil yang keluar adalah mobil yang pertama kali masuk
void keluarkanMobil(Antrian* antrian, const string& platNomor) {
    for (int i = 0; i < antrian->jumlahMobil; ++i) {
        if (antrian->mobil[i].platNomor == platNomor) {
            antrian->totalPendapatan += antrian->mobil[i].biayaParkir;
            for (int j = i; j < antrian->jumlahMobil - 1; ++j) {
                antrian->mobil[j] = antrian->mobil[j + 1];
            }
            antrian->jumlahMobil--;
            cout << "Mobil dengan plat nomor " << platNomor << " berhasil dikeluarkan." << endl;
            return;
        }
    }
    cout << "Mobil dengan plat nomor " << platNomor << " tidak ditemukan dalam antrian." << endl;
}

void tampilkanAntrian(const Antrian* antrian) {
    cout << "Antrian Parkir Mobil:" << endl;
    for (int i = 0; i < antrian->jumlahMobil; ++i) {
        cout << "Plat Nomor: " << antrian->mobil[i].platNomor << ", Biaya Parkir: " << antrian->mobil[i].biayaParkir << endl;
    }

}

void hitungTotalPendapatan(const Antrian* antrian) {
    cout << "Total Pendapatan: " << antrian->totalPendapatan << endl;
}

//pointer ke strust 'antrian dan menggunakan array
//sorthing
void sortAntrian(Antrian* antrian) {
    sort(antrian->mobil, antrian->mobil + antrian->jumlahMobil, compareByPlatNomor);
    cout << "Antrian Parkir Mobil berhasil diurutkan berdasarkan plat nomor." << endl;
}

//pointer ke struct 'Antrian' dan menggunakan array
//seraching
int cariMobil(const Antrian* antrian, const string& platNomor) {
    for (int i = 0; i < antrian->jumlahMobil; ++i) {
        if (antrian->mobil[i].platNomor == platNomor) {
            return i; // Mengembalikan indeks mobil yang ditemukan
        }
    }
    return -1; // Mengembalikan -1 jika mobil tidak ditemukan
}

int main() {
    Antrian antrian;
    antrian.jumlahMobil = 0;
    antrian.totalPendapatan = 0;

    int pilihan;
    do {
        cout << "\nMenu Utama :\n1. Antrian Parkir Mobil\n2. Keluarkan Mobil\n3. Tampilkan Antrian Mobil\n4. Hitung Total Pendapatan\n5. Urutkan Antrian Mobil\n6. Cari Mobil\n7. Exit\n";
        cout << "Masukkan Pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                Mobil mobil;
                cout << "Masukkan plat nomor mobil: ";
                cin >> mobil.platNomor;
                cout << "Masukkan biaya parkir mobil: ";
                cin >> mobil.biayaParkir;
                tambahAntrian(&antrian, mobil);
                break;
            }
            case 2: {
                string platNomor;
                cout << "Masukkan plat nomor mobil yang akan dikeluarkan: ";
                cin >> platNomor;
                keluarkanMobil(&antrian, platNomor);
                break;
            }
            case 3: {
                tampilkanAntrian(&antrian);
                break;
            }
            case 4: {
                hitungTotalPendapatan(&antrian);
                break;
            }
            case 5: {
                sortAntrian(&antrian);
                break;
            }
            case 6: {
                string platNomor;
                cout << "Masukkan plat nomor mobil yang akan dicari: ";
                cin >> platNomor;
                int indeks = cariMobil(&antrian, platNomor);
                if (indeks != -1) {
                    cout << "Mobil dengan plat nomor " << platNomor << " ditemukan pada indeks " << indeks << endl;
                } else {
                    cout << "Mobil dengan plat nomor " << platNomor << " tidak ditemukan dalam antrian." << endl;
                }
                break;
            }
            case 7: {
                cout << "Program selesai. Terima kasih!";
                break;
            }
            default: {
                cout << "Pilihan tidak valid. Silakan pilih kembali.";
                break;
            }
        }
    } while (pilihan != 7);

    return 0;
}