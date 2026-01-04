#include <iostream>
#include <fstream>
#include <map>

#include "ktp.h"   // <-- TAMBAHAN
#include "barang.h"
#include "queue.h"
#include "stack.h"
#include "riwayat.h"
#include "statistik.h"
#include "transaksi.h"
#include "huffman.h"
#include "avl.h"

using namespace std;

// ===== GLOBAL OBJECT =====
BarangList barang;
QueuePembatalan queueBatal;
StackLog logAktivitas;
RiwayatList riwayat;
Statistik statistik;
TransaksiList transaksi;

// =======================
// ANALISIS HUFFMAN
// =======================
void analisisHuffmanLog() {
    ifstream f("log.txt");
    if (!f) {
        cout << "Log kosong.\n";
        return;
    }

    map<char,int> freq;
    char c;
    while (f.get(c)) freq[c]++;
    f.close();

    HuffmanTree h;
    HuffNode* root = h.build(freq);

    map<char,string> code;
    h.generate(root, "", code);

    int bitAwal = 0, bitHuffman = 0;
    for (auto p : freq) {
        bitAwal += p.second * 8;
        bitHuffman += p.second * code[p.first].length();
    }

    cout << "\n===== ANALISIS HUFFMAN =====\n";
    cout << "Ukuran Awal    : " << bitAwal << " bit\n";
    cout << "Ukuran Huffman : " << bitHuffman << " bit\n";
    cout << "Efisiensi      : "
         << (float)(bitAwal - bitHuffman) / bitAwal * 100
         << "%\n";
}

// =======================
// LOGIN ADMIN
// =======================
bool loginAdmin() {
    string u, p;
    cout << "\n===== LOGIN ADMIN =====\n"; 
	cout << "Username : "; cin >> u; 
	cout << "Password : "; cin >> p;
    return (u == "admin" && p == "123");
}

// =======================
// MENU ADMIN
// =======================
void menuAdmin() {
    int pilih;
    do {
    	cout << "\n------------------------------\n";
        cout << "\tMENU ADMIN\t";
        cout << "\n------------------------------\n";
        cout << "1. Lihat Barang (Linked List)\n";
        cout << "2. Lihat Barang (AVL)\n";
        cout << "3. Approve Pembatalan\n";
        cout << "4. Lihat Log Aktivitas\n";
        cout << "5. Riwayat Transaksi\n";
        cout << "6. Statistik Sistem\n";
        cout << "7. Analisis Huffman\n";
        cout << "8. Cari Barang (AVL Search)\n";
        cout << "9. Laporan Keputusan\n";
        cout << "10. Tambah Barang\n";
        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) barang.tampil();

        else if (pilih == 2) {
            AVLTree avl;
            barang.masukkanKeAVL(avl);
            avl.tampil();
        }

        else if (pilih == 3) {
            string user; int id;
            if (queueBatal.approve(user, id)) {
                NodeBarang* b = barang.cari(id);
                if (b) b->stok++;
                riwayat.tambah(user, "Batal", id, 0);
                logAktivitas.push("Admin approve pembatalan");
                barang.save();
                queueBatal.save();
                logAktivitas.save();
            }
        }

        else if (pilih == 4) logAktivitas.tampil();

        else if (pilih == 5) riwayat.tampil();

        else if (pilih == 6) {
            statistik = Statistik();
            statistik.proses(riwayat, barang);
            statistik.tampilDetail();
        }

        else if (pilih == 7) analisisHuffmanLog();

        else if (pilih == 8) {
            int id;
            cout << "ID Barang: "; cin >> id;
            AVLTree avl;
            barang.masukkanKeAVL(avl);
            AVLNode* h = avl.cari(id);
            if (h)
                cout << h->nama << " | Harga: " << h->harga << " | Stok: " << h->stok << endl;
            else
                cout << "Barang tidak ditemukan.\n";
        }

        else if (pilih == 9) {
            statistik = Statistik();
            statistik.proses(riwayat, barang);
            statistik.tampilLaporanKeputusan(barang);
        }else if (pilih == 10) {
    		barang.tambahAdmin();
    		logAktivitas.push("Admin menambahkan barang");
    		logAktivitas.save();
		}
    } while (pilih != 0);
}

// =======================
// MENU USER
// =======================
void menuUser(string user) {
    int pilih, id, durasi;
    do {
        cout << "\n------------------------------\n";
        cout << "\tMENU USER\t";
        cout << "\n------------------------------\n";
        cout << "1. Lihat Barang\n";
        cout << "2. Sewa Barang\n";
        cout << "3. Ajukan Pembatalan\n";
        cout << "4. Riwayat\n";
        cout << "5. Kembalikan Barang\n";
        cout << "0. Logout\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            barang.tampil();
        }
        else if (pilih == 2) {
            cout << "Masukkan ID Barang   : ";
            cin >> id;
            cout << "Masukkan Durasi (hari): ";
            cin >> durasi;

            NodeBarang* b = barang.cari(id);
            if (b && b->stok > 0) {
                b->stok--;
                transaksi.tambah(user, id, durasi);
                riwayat.tambah(user, "Sewa", id, durasi);

                barang.save();
                logAktivitas.push(user + " sewa barang");
                logAktivitas.save();

                cout << "Sewa berhasil.\n";
            } else {
                cout << "Barang tidak tersedia.\n";
            }
        }
        else if (pilih == 3) {
            cout << "Masukkan ID Barang yang dibatalkan: ";
            cin >> id;
            queueBatal.enqueue(user, id);
            queueBatal.save();
            cout << "Pembatalan diajukan.\n";
        }
        else if (pilih == 4) {
            riwayat.tampilUser(user);
        }else if (pilih == 5) {
    		cout << "Masukkan ID Barang: ";
    		cin >> id;

    		NodeBarang* b = barang.cari(id);
    		if (b) {
        	b->stok++;   // stok kembali

        	riwayat.tambah(user, "Kembali", id, 0);
        	logAktivitas.push(user + " mengembalikan barang");

        	barang.save();
        	logAktivitas.save();

        	cout << "Barang berhasil dikembalikan.\n";
    	} else {
        	cout << "Barang tidak ditemukan.\n";
    	}
	}

    } while (pilih != 0);
}

// =======================
// MAIN
// =======================
int main() {
    queueBatal.load();
    logAktivitas.load();
    barang.load();

    int pilih;
    do {
    cout << "\n=================================\n"; 
    cout << " SISTEM SEWA BARANG ELEKTRONIK\n"; 
    cout << "=================================\n"; 
    cout << "1. Login Admin\n"; 
    cout << "2. Login User\n"; 
    cout << "0. Keluar\n"; 
    cout << "Pilih: "; 
    cin >> pilih;

    if (pilih == 1 && loginAdmin()) {
        menuAdmin();
    }
    else if (pilih == 2) {
        string nik, nama;

        cout << "Masukkan NIK: ";
        cin >> nik;

        if (!loginKTP(nik, nama)) {
            cout << "NIK tidak terdaftar di data KTP!\n";
        } else {
            cout << "Selamat datang, " << nama << endl;
            menuUser(nama);
        }
    }

	}while (pilih != 0);

	cout << "Program selesai.\n";
	return 0;
	}
