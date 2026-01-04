#ifndef RIWAYAT_H
#define RIWAYAT_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// =======================
// NODE RIWAYAT (SLL)
// =======================
struct NodeRiwayat {
    string user;
    string aksi;        // Sewa / Kembali / Batal
    int idBarang;
    int durasi;
    NodeRiwayat* next;
};

// =======================
// CLASS RIWAYAT LIST
// =======================
class RiwayatList {
private:
    NodeRiwayat* head;

public:
    // ===================
    // CONSTRUCTOR
    // ===================
    NodeRiwayat* getHead() {
    	return head;
	}


    // ===================
    // TAMBAH RIWAYAT
    // ===================
    void tambah(string u, string a, int id, int d) {
        NodeRiwayat* r = new NodeRiwayat{u, a, id, d, NULL};

        if (!head) {
            head = r;
        } else {
            NodeRiwayat* t = head;
            while (t->next)
                t = t->next;
            t->next = r;
        }

        save();
    }

    // ===================
    // TAMPIL RIWAYAT PER USER
    // ===================
    void tampilUser(string u) {
        bool ada = false;
        NodeRiwayat* t = head;

        cout << "\n===== RIWAYAT USER : " << u << " =====\n";

        while (t) {
            if (t->user == u) {
                cout << "- " << t->aksi
                     << " | ID Barang: " << t->idBarang
                     << " | Durasi: " << t->durasi << " hari\n";
                ada = true;
            }
            t = t->next;
        }

        if (!ada) {
            cout << "Belum ada riwayat transaksi.\n";
        }
    }

    // ===================
    // TAMPIL SEMUA RIWAYAT (ADMIN)
    // ===================
    void tampil() {
        NodeRiwayat* t = head;

        cout << "\n=========== SEMUA RIWAYAT TRANSAKSI ===========\n";
        cout << "User | Aksi | ID Barang | Durasi\n";
        cout << "----------------------------------------------\n";

        if (!t) {
            cout << "Belum ada data riwayat.\n";
            return;
        }

        while (t) {
            cout << t->user << " | "
                 << t->aksi << " | "
                 << t->idBarang << " | "
                 << t->durasi << endl;
            t = t->next;
        }
    }

    // ===================
    // LOAD FILE
    // ===================
    void load() {
        ifstream f("riwayat.txt");
        if (!f) return;

        head = NULL;

        string u, a;
        int id, d;

        while (getline(f, u, '|')) {
            getline(f, a, '|');
            f >> id;
            f.ignore();
            f >> d;
            f.ignore();

            NodeRiwayat* r = new NodeRiwayat{u, a, id, d, NULL};

            if (!head) head = r;
            else {
                NodeRiwayat* t = head;
                while (t->next) t = t->next;
                t->next = r;
            }
        }
        f.close();
    }

    // ===================
    // SAVE FILE
    // ===================
    void save() {
        ofstream f("riwayat.txt");
        NodeRiwayat* t = head;
        while (t) {
            f << t->user << "|"
              << t->aksi << "|"
              << t->idBarang << "|"
              << t->durasi << endl;
            t = t->next;
        }
        f.close();
    }
    
    // ===================
	// CEK APAKAH USER PERNAH SEWA BARANG
	// ===================
	bool pernahSewa(string user, int idBarang) {
    	NodeRiwayat* t = head;
    	while (t) {
        if (t->user == user &&
            t->idBarang == idBarang &&
            t->aksi == "Sewa") {
            return true;
        }
        t = t->next;
    }
    return false;
}

};

#endif

