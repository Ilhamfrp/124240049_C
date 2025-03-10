#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Roti {
    string nama;
    string kode;
    int harga;
};

Roti daftarRoti[] = {
    {"Roti Tawar", "001", 15000},
    {"Roti Cokelat", "002", 18000},
    {"Roti Keju", "003", 20000},
    {"Roti Gandum", "004", 22000},
    {"Roti Pisang", "005", 17000}
};

int jumlah = 5;


void Tampilan() {
    cout << "====================================\n";
    cout << "|          Daftar Roti             |\n";
    cout << "====================================\n";
    cout << "| Nama          | Kode |   Harga    |\n";
    cout << "------------------------------------\n";
    Roti* ptr = daftarRoti;  
    for (int i = 0; i < jumlah; i++) {
        cout << left << setw(15) << (*(ptr + i)).nama << " " << setw(8)
             << (*(ptr + i)).kode << " "  << "Rp " << setw(10)
             << (*(ptr + i)).harga << endl;
    }
    cout << "====================================\n";
}
//Ascending
void quickSort(Roti arr[], int awal, int akhir) {
    int low = awal, high = akhir;
    int pivot = arr[(awal + akhir) / 2].harga;
    do {
        while (arr[low].harga < pivot) low++;
        while (arr[high].harga > pivot) high--;
        if (low <= high) {
            swap(arr[low], arr[high]);
            low++;
            high--;
        }
    } while (low <= high);

    if (awal < high) quickSort(arr, awal, high);
    if (low < akhir) quickSort(arr, low, akhir);

    Tampilan();

}

//Descending
void bubbleSort() {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - 1 - i; j++) {
            if (daftarRoti[j].harga < daftarRoti[j + 1].harga) {
                swap(daftarRoti[j], daftarRoti[j + 1]);
            }
        }
    }
    Tampilan();
}


void Sequiential(string kode) {
    bool found = false;
    for (int i = 0; i < jumlah; i++) {
        if (daftarRoti[i].kode == kode) {
            cout << "Nama: " << daftarRoti[i].nama << ", Kode: " << daftarRoti[i].kode << ", Harga: " << " Rp."<< daftarRoti[i].harga << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Roti tidak ditemukan!" << endl;
}


void Binary(string nama) {
    int awal = 0, akhir = jumlah - 1, tengah;
    bool found = false;
    while (awal <= akhir && !found) {
        tengah = (awal + akhir) / 2;
        if (daftarRoti[tengah].nama == nama) {
            found = true;
        } else if (daftarRoti[tengah].nama < nama) {
            awal = tengah + 1;
        } else {
            akhir = tengah - 1;
        }
    }
    if (found) {
        cout << "Nama: " << daftarRoti[tengah].nama << ", Kode: " << daftarRoti[tengah].kode << ", Harga: " << " Rp." << daftarRoti[tengah].harga << endl;
    } else {
        cout << "Roti tidak ditemukan!" << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "========== Toko Roti AK ==========" << endl;
        cout << "1. Tampilkan Roti" << endl;
        cout << "2. Cari berdasarkan kode" << endl;
        cout << "3. Cari berdasarkan nama" << endl;
        cout << "4. Sort Harga Roti (ascending)" << endl;
        cout << "5. Sort Harga Roti (descending)" << endl;
        cout << "6. Exit" << endl;
        cout << "==================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan) {
            case 1:
                Tampilan();
                break;
            case 2: {
                string kode;
                cout << "Masukkan kode roti: ";
                cin >> kode;
                Sequiential(kode);
                break;
            }
            case 3: {
                string nama;
                cout << "Masukkan nama roti: ";
                getline(cin, nama);
                Binary(nama);
                break;
            }
            case 4:
                quickSort(daftarRoti, 0, jumlah - 1);
                cout << "Data berhasil diurutkan secara ascending!" << endl;
                break;
            case 5:
                bubbleSort();
                cout << "Data berhasil diurutkan secara descending!" << endl;
                break;
            case 6:
                cout << "Terima kasih" << endl;
                break;
            default:
                cout << " Error! " << endl;
        }
    } while (pilihan != 6);
    return 0;
}
