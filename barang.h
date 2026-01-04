#ifndef BARANG_H
#define BARANG_H

#include <iostream>
#include <fstream>
#include <string>

#include "avl.h"   // === TAMBAHAN: untuk AVL Tree ===

using namespace std;

// =======================
// NODE BARANG (SLL)
// =======================
struct NodeBarang {
    int id;
    string nama;
    string merek;
    int harga;
    int stok;
    NodeBarang* next;
};

// =======================
// CLASS BARANG LIST
// =======================
class BarangList {
private:
    NodeBarang* head;
    int nextID;

public:
    // ===================
    // CONSTRUCTOR
    // ===================
    BarangList() {
        head = NULL;
        nextID = 1;
        load();

        // Jika file belum ada / kosong
        if (head == NULL) {
            dataAwal();
            save();
        }
    }

    // ===================
    // DATA AWAL (20 BARANG)
    // ===================
    void dataAwal() {
        tambah("Laptop", "Dell", 70000, 3);
        tambah("Laptop", "Acer", 65000, 4);
        tambah("Laptop", "HP", 68000, 2);
        tambah("Laptop", "Asus", 72000, 3);

        tambah("Kamera", "Canon", 80000, 2);
        tambah("Kamera", "Nikon", 82000, 2);
        tambah("Kamera", "Sony", 85000, 1);

        tambah("Proyektor", "Epson", 90000, 2);
        tambah("Proyektor", "BenQ", 95000, 2);

        tambah("Drone", "DJI", 150000, 1);
        tambah("Drone", "Autel", 140000, 1);

        tambah("HP", "Samsung", 50000, 5);
        tambah("HP", "Oppo", 45000, 4);
        tambah("HP", "Xiaomi", 48000, 4);
        tambah("HP", "Vivo", 46000, 3);

        tambah("Tablet", "Samsung", 55000, 3);
        tambah("Tablet", "iPad", 90000, 2);

        tambah("Monitor", "LG", 60000, 3);
        tambah("Monitor", "Samsung", 62000, 3);
        tambah("Printer", "HP", 50000, 2);
    }

    // ===================
    // TAMBAH BARANG (INTERNAL)
    // ===================
    void tambah(string nama, string merek, int harga, int stok) {
        NodeBarang* b = new NodeBarang;
        b->id = nextID++;
        b->nama = nama;
        b->merek = merek;
        b->harga = harga;
        b->stok = stok;
        b->next = head;
        head = b;
    }

    // ===================
    // TAMBAH BARANG OLEH ADMIN
    // ===================
    void tambahAdmin() {
        string nama, merek;
        int harga, stok;

        cin.ignore();
        cout << "Nama Barang  : ";
        getline(cin, nama);
        cout << "Merek        : ";
        getline(cin, merek);
        cout << "Harga / hari : ";
        cin >> harga;
        cout << "Stok         : ";
        cin >> stok;

        tambah(nama, merek, harga, stok);
        save();

        cout << "Barang berhasil ditambahkan.\n";
    }

    // ===================
    // CARI BARANG
    // ===================
    NodeBarang* cari(int id) {
        NodeBarang* t = head;
        while (t) {
            if (t->id == id) return t;
            t = t->next;
        }
        return NULL;
    }

    // ===================
    // TAMPIL BARANG
    // ===================
    void tampil() {
        cout << "\n===========================================\n";
        cout << " ID   NAMA        MEREK      HARGA   STOK\n";
        cout << "===========================================\n";

        NodeBarang* t = head;
        while (t) {
            cout << t->id << "\t"
                 << t->nama << "\t"
                 << t->merek << "\t"
                 << t->harga << "\t"
                 << t->stok << endl;
            t = t->next;
        }
    }

    // ===================
    // LOAD DARI FILE
    // ===================
    void load() {
        ifstream f("barang.txt");
        if (!f) return;

        head = NULL;
        nextID = 1;

        int id, harga, stok;
        string nama, merek;

        while (true) {
            f >> id;
            if (!f) break;
            f.ignore();               // |
            getline(f, nama, '|');
            getline(f, merek, '|');
            f >> harga;
            f.ignore();               // |
            f >> stok;

            NodeBarang* b = new NodeBarang;
            b->id = id;
            b->nama = nama;
            b->merek = merek;
            b->harga = harga;
            b->stok = stok;
            b->next = head;
            head = b;

            if (id >= nextID)
                nextID = id + 1;
        }
        f.close();
    }

    // ===================
    // SAVE KE FILE
    // ===================
    void save() {
        ofstream f("barang.txt");
        NodeBarang* t = head;
        while (t) {
            f << t->id << "|"
              << t->nama << "|"
              << t->merek << "|"
              << t->harga << "|"
              << t->stok << endl;
            t = t->next;
        }
        f.close();
    }

    // ==================================================
    // === TAMBAHAN UNTUK AVL TREE (INDEXING BARANG)
    // ==================================================
    void masukkanKeAVL(AVLTree &avl) {
        NodeBarang* t = head;
        while (t) {
            avl.insert(t->id, t->nama, t->harga, t->stok);
            t = t->next;
        }
    }

    // ==================================================
    // === TAMBAHAN UNTUK HUFFMAN (EFISIENSI DATA)
    // ==================================================
    string gabungNamaBarang() {
        string data = "";
        NodeBarang* t = head;
        while (t) {
            data += t->nama;
            data += t->merek;
            t = t->next;
        }
        return data;
    }
};

#endif

