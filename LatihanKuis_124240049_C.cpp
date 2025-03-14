#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

struct Penduduk {
    char nik[20];
    char nama[50];
    char alamat[100];
    char jenis_kelamin[2];
};
Penduduk p;
FILE *file;
int tambah;

void inputdata() {
    file = fopen("DataKependudukan.txt", "a");
    if (!file) {
        cout << "Error!\n";
        return;
    }
    cout << "Masukkan jumlah data penduduk yang ingin ditambahkan: "; 
    cin >> tambah;
   for(int i=0; i<tambah; i++){
    cout << "Masukkan data penduduk ke-" << i +1 << endl;
    cout << "Masukkan NIK: "; cin >> p.nik;
    cout << "Masukkan Nama: "; cin.ignore(); cin.getline(p.nama, 50);
    cout << "Masukkan Alamat: "; cin.getline(p.alamat, 100);
    cout << "Masukkan Jenis Kelamin (L/P): "; cin >> p.jenis_kelamin;
    
    fwrite(&p, sizeof(Penduduk), 1, file);
    
    cout << "Data berhasil ditambahkan!\n";
    cout << "====================================================\n";
}
    fclose(file);
}

void outputdata() {
    file = fopen("DataKependudukan.txt", "r");
    if (!file) {
        cout << "Error!\n";
        return;  
    }

    int n =0;
    Penduduk data[100];

    while (fread(&data[n], sizeof(Penduduk), 1, file)) {
        n++;
    }
    
    fclose(file);
    
     //sorting secara ascending menggunakan bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int k = 0;
            while (data[j].nik[k] && data[j + 1].nik[k] && data[j].nik[k] == data[j + 1].nik[k]) {
                k++;
            }
            if (data[j].nik[k] > data[j + 1].nik[k]) {
                Penduduk temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    cout << "==================================================================================================\n";
    cout << "| " << setw(20) << left << "NIK"
         << "| " << setw(25) << left << "Nama"
         << "| " << setw(30) << left << "Alamat"
         << "| " << setw(15) << left << "Jenis Kelamin" << "|\n";
    cout << "==================================================================================================\n";
    
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(20) << left << data[i].nik
             << "| " << setw(25) << left << data[i].nama
             << "| " << setw(30) << left << data[i].alamat
             << "| " << setw(15) << left << data[i].jenis_kelamin << "|\n";
    }
    cout << "===================================================================================================\n";
}

void searchingdata() {
    file = fopen("DataKependudukan.txt", "r");
    if (!file) {
        cout << "Tidak ada data\n";
        return;
    }
    char nik[20];
    cout << "Masukkan NIK yang dicari: "; cin >> nik;
    Penduduk p;
    bool found = false;
    //searching menggunakan sequential search
    while (fread(&p, sizeof(Penduduk), 1, file)) {
        bool cocok = true;
        for (int i = 0; nik[i] && p.nik[i] ; i++) {
            if (nik[i] != p.nik[i]) {
                cocok = false;
                break;
            }
        }
        if (cocok) {
            found = true;
            cout << "====================================================\n";
            cout << "NIK            | Nama            | Alamat         | Jenis Kelamin\n";
            cout << "====================================================\n";
            cout << setw(20) << left << p.nik << " | "
            << setw(25) << left << p.nama << " | "
            << setw(30) << left << p.alamat << " | "
            << setw(15) << left << p.jenis_kelamin << "\n";
            cout << "====================================================\n";
            break;
        }
    }
    fclose(file);
    if (!found) cout << "Data tidak ditemukan!\n";
}

void editData() {
    file = fopen("DataKependudukan.txt", "r");
    if (!file) {
        cout << "Tidak ada data yang tersimpan\n";
        return;
    }
    Penduduk data[100];
    int n = 0;
    while (fread(&data[n], sizeof(Penduduk), 1, file)) {
        n++;
    }
    fclose(file);
    
    char nik[20];
    cout << "Masukkan NIK yang ingin diedit: "; cin >> nik;
    bool found = false;

    //searching menggunakan sequential search
    for (int i = 0; i < n; i++) {
        bool cocok = true;
        for (int j = 0; nik[j] && data[i].nik[j] ; j++) {
            if (nik[j] != data[i].nik[j]) {
                cocok = false;
                break;
            }
        }
        if (cocok) {
            found = true;
            cout << "Data ditemukan!\nMasukkan alamat baru: ";
            cin.ignore();
            cin.getline(data[i].alamat, 100);
            break;
        }
    }
    
    if (found) {
        file = fopen("DataKependudukan.txt", "w");
        for (int i = 0; i < n; i++) {
            fwrite(&data[i], sizeof(Penduduk), 1, file);
        }
        fclose(file);
        cout << "Data berhasil diperbarui!\n";
    } else {
        cout << "error!\n";
    }
}

void hapusdata() {
    file = fopen("DataKependudukan.txt", "r");
    if (!file) {
        cout << "Tidak ada data tersimpan.\n";
        return;
    }
    Penduduk data[100];
    int n = 0;
    while (fread(&data[n], sizeof(Penduduk), 1, file)) {
        n++;
    }
    fclose(file);
    
    char nik[20];
    cout << "Masukkan NIK yang ingin dihapus: "; cin >> nik;
    bool found = false;
    int h = 0;
    //searching menggunakan sequential search
    for (int i = 0; i < n; i++) {
        bool cocok = true;
        for (int j = 0; nik[j] && data[i].nik[j] ; j++) {
            if (nik[j] != data[i].nik[j]) {
                cocok = false;
                break;
            }
        }
        if (!cocok) {
            data[h++] = data[i];
        } else {
            found = true;
        }
    }
    
    if (found) {
        file = fopen("DataKependudukan.txt", "w");
        for (int i = 0; i < h; i++) {
            fwrite(&data[i], sizeof(Penduduk), 1, file);
        }
        fclose(file);
        cout << "Data berhasil dihapus!\n";
    } else {
        cout << "Data tidak ditemukan!\n";
    }
}


int main() {
    int pilihan;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Input Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Data\n";
        cout << "4. Edit Data\n";
        cout << "5. Hapus Data\n";
        cout << "6. Exit\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: inputdata(); break;
            case 2: outputdata(); break;
            case 3: searchingdata(); break;
            case 4: editData(); break;
            case 5: hapusdata(); break;
            case 6: cout << "Terima kasih!\n"; break;
            default: cout << "Error!\n";
        }
    } while (pilihan != 6);
    
    return 0;
}
