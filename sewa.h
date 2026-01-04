#ifndef SEWA_H
#define SEWA_H

#include <iostream>
#include "barang.h"
#include "riwayat.h"
using namespace std;

struct NodeSewa {
    string user;
    int idBarang;
    int durasi;
    NodeSewa* next;
};

class SewaList {
private:
    NodeSewa* head;

public:
    SewaList() {
        head = NULL;
    }

    // ===== SEWA BARANG =====
    void sewa(string u, NodeBarang* b, int d, RiwayatList& r) {
        if (!b || b->stok <= 0) {
            cout << "Stok habis!\n";
            return;
        }

        b->stok--;
        NodeSewa* baru = new NodeSewa{u, b->id, d, head};
        head = baru;

        r.tambah(u, "Sewa", b->id, d);
    }

    // ===== KEMBALIKAN BARANG =====
    bool kembalikan(string u, int id, BarangList& barang, RiwayatList& r) {
        NodeSewa* cur = head;
        NodeSewa* prev = NULL;

        while (cur) {
            if (cur->user == u && cur->idBarang == id) {

                // tambah stok barang
                NodeBarang* b = barang.cari(id);
                if (b) b->stok++;

                // hapus node sewa (SLL)
                if (prev)
                    prev->next = cur->next;
                else
                    head = cur->next;

                r.tambah(u, "Kembali", id, cur->durasi);

                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }
};

#endif

