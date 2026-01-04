#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// =======================
// NODE TRANSAKSI (SLL)
// =======================
struct NodeTransaksi {
    int idTransaksi;
    string user;
    int idBarang;
    int durasi;
    string status; // Aktif / Selesai / Batal
    NodeTransaksi* next;
};

// =======================
// CLASS TRANSAKSI LIST
// =======================
class TransaksiList {
private:
    NodeTransaksi* head;
    int counter;

public:
    TransaksiList() {
        head = NULL;
        counter = 1;
        load();
    }

    // ===================
    // TAMBAH TRANSAKSI
    // ===================
    void tambah(string user, int idBarang, int durasi) {
        NodeTransaksi* t = new NodeTransaksi;
        t->idTransaksi = counter++;
        t->user = user;
        t->idBarang = idBarang;
        t->durasi = durasi;
        t->status = "Aktif";
        t->next = NULL;

        if (!head) head = t;
        else {
            NodeTransaksi* p = head;
            while (p->next) p = p->next;
            p->next = t;
        }

        save();
    }

    // ===================
    // SELESAI TRANSAKSI
    // ===================
    bool selesai(string user, int idBarang) {
        NodeTransaksi* p = head;
        while (p) {
            if (p->user == user &&
                p->idBarang == idBarang &&
                p->status == "Aktif") {

                p->status = "Selesai";
                save();
                return true;
            }
            p = p->next;
        }
        return false;
    }

    // ===================
    // BATAL TRANSAKSI
    // ===================
    bool batal(string user, int idBarang) {
        NodeTransaksi* p = head;
        while (p) {
            if (p->user == user &&
                p->idBarang == idBarang &&
                p->status == "Aktif") {

                p->status = "Batal";
                save();
                return true;
            }
            p = p->next;
        }
        return false;
    }

    // ===================
    // TAMPIL TRANSAKSI USER
    // ===================
    void tampilUser(string u) {
        cout << "\n=== TRANSAKSI AKTIF USER ===\n";
        NodeTransaksi* p = head;
        while (p) {
            if (p->user == u && p->status == "Aktif") {
                cout << "ID Barang: " << p->idBarang
                     << " | Durasi: " << p->durasi
                     << " hari\n";
            }
            p = p->next;
        }
    }

    // ===================
    // LOAD FILE
    // ===================
    void load() {
        ifstream f("transaksi.txt");
        if (!f) return;

        head = NULL;
        counter = 1;

        while (!f.eof()) {
            NodeTransaksi* t = new NodeTransaksi;
            f >> t->idTransaksi;
            f >> t->user;
            f >> t->idBarang;
            f >> t->durasi;
            f >> t->status;

            if (!f) break;

            t->next = NULL;
            counter = t->idTransaksi + 1;

            if (!head) head = t;
            else {
                NodeTransaksi* p = head;
                while (p->next) p = p->next;
                p->next = t;
            }
        }
        f.close();
    }

    // ===================
    // SAVE FILE
    // ===================
    void save() {
        ofstream f("transaksi.txt");
        NodeTransaksi* p = head;
        while (p) {
            f << p->idTransaksi << " "
              << p->user << " "
              << p->idBarang << " "
              << p->durasi << " "
              << p->status << endl;
            p = p->next;
        }
        f.close();
    }
};

#endif

