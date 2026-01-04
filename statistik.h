#ifndef STATISTIK_H
#define STATISTIK_H

#include <iostream>
#include <string>
#include "riwayat.h"
#include "barang.h"

using namespace std;

// =======================
// NODE STATISTIK BARANG
// =======================
struct NodeStatBarang {
    int idBarang;
    int jumlahSewa;
    int totalDurasi;
    int totalPendapatan;
    NodeStatBarang* next;
};

// =======================
// NODE STATISTIK USER
// =======================
struct NodeStatUser {
    string user;
    int jumlahTransaksi;
    NodeStatUser* next;
};

// =======================
// CLASS STATISTIK
// =======================
class Statistik {
private:
    NodeStatBarang* barangHead;
    NodeStatUser* userHead;

    int totalPendapatanSistem;
    int totalDurasiSistem;
    int totalTransaksi;

    // BIAYA OPERASIONAL (asumsi tetap)
    int biayaOperasional;

public:
    Statistik() {
        barangHead = NULL;
        userHead = NULL;

        totalPendapatanSistem = 0;
        totalDurasiSistem = 0;
        totalTransaksi = 0;

        biayaOperasional = 3000000; // contoh biaya tetap
    }

    // ===================
    // PROSES DATA RIWAYAT
    // ===================
    void proses(RiwayatList& r, BarangList& barang) {
        NodeRiwayat* t = r.getHead();
        while (t) {
            if (t->aksi == "Sewa") {
                NodeBarang* b = barang.cari(t->idBarang);
                if (b) {
                    int pendapatan = t->durasi * b->harga;

                    totalPendapatanSistem += pendapatan;
                    totalDurasiSistem += t->durasi;
                    totalTransaksi++;

                    tambahBarang(t->idBarang, t->durasi, pendapatan);
                    tambahUser(t->user);
                }
            }
            t = t->next;
        }
    }

    // ===================
    // UPDATE STAT BARANG
    // ===================
    void tambahBarang(int id, int durasi, int pendapatan) {
        NodeStatBarang* t = barangHead;
        while (t) {
            if (t->idBarang == id) {
                t->jumlahSewa++;
                t->totalDurasi += durasi;
                t->totalPendapatan += pendapatan;
                return;
            }
            t = t->next;
        }

        NodeStatBarang* baru = new NodeStatBarang;
        baru->idBarang = id;
        baru->jumlahSewa = 1;
        baru->totalDurasi = durasi;
        baru->totalPendapatan = pendapatan;
        baru->next = barangHead;
        barangHead = baru;
    }

    // ===================
    // UPDATE STAT USER
    // ===================
    void tambahUser(string u) {
        NodeStatUser* t = userHead;
        while (t) {
            if (t->user == u) {
                t->jumlahTransaksi++;
                return;
            }
            t = t->next;
        }

        NodeStatUser* baru = new NodeStatUser;
        baru->user = u;
        baru->jumlahTransaksi = 1;
        baru->next = userHead;
        userHead = baru;
    }

    // ===================
    // LAPORAN KEPUTUSAN
    // ===================
    void tampilLaporanKeputusan(BarangList& barang) {
        cout << "\n===== LAPORAN PENGAMBILAN KEPUTUSAN =====\n";

        cout << "Total Pendapatan Sistem : Rp "
             << totalPendapatanSistem << endl;

        cout << "Total Biaya Operasional : Rp "
             << biayaOperasional << endl;

        int keuntungan = totalPendapatanSistem - biayaOperasional;
        cout << "Keuntungan / Kerugian   : Rp "
             << keuntungan << endl;

        cout << "Total Transaksi         : "
             << totalTransaksi << endl;

        if (totalTransaksi > 0) {
            cout << "Rata-rata Durasi Sewa   : "
                 << (float)totalDurasiSistem / totalTransaksi
                 << " hari\n";
        }

        NodeStatBarang* favorit = NULL;
        NodeStatBarang* tidakLaku = NULL;
        NodeStatUser* userAktif = NULL;

        for (NodeStatBarang* b = barangHead; b; b = b->next) {
            if (!favorit || b->jumlahSewa > favorit->jumlahSewa)
                favorit = b;

            if (!tidakLaku || b->jumlahSewa < tidakLaku->jumlahSewa)
                tidakLaku = b;
        }

        for (NodeStatUser* u = userHead; u; u = u->next)
            if (!userAktif || u->jumlahTransaksi > userAktif->jumlahTransaksi)
                userAktif = u;

        if (favorit) {
            NodeBarang* data = barang.cari(favorit->idBarang);
            if (data) {
                cout << "\nBarang Terfavorit      : " << data->nama << endl;
                cout << "Jumlah Disewa          : " << favorit->jumlahSewa << endl;
                cout << "Pendapatan Barang      : Rp "
                     << favorit->totalPendapatan << endl;
            }
        }

        if (tidakLaku) {
            NodeBarang* data = barang.cari(tidakLaku->idBarang);
            if (data) {
                cout << "\nBarang Kurang Diminati : "
                     << data->nama
                     << " (" << tidakLaku->jumlahSewa << " sewa)\n";
            }
        }

        if (userAktif) {
            cout << "\nUser Paling Aktif      : "
                 << userAktif->user
                 << " (" << userAktif->jumlahTransaksi
                 << " transaksi)\n";
        }
    }

    // ===================
    // DETAIL STATISTIK
    // ===================
    void tampilDetail() {
        cout << "\n===== STATISTIK BARANG =====\n";
        for (NodeStatBarang* b = barangHead; b; b = b->next)
            cout << "ID " << b->idBarang
                 << " | Sewa: " << b->jumlahSewa
                 << " | Durasi: " << b->totalDurasi
                 << " | Pendapatan: Rp " << b->totalPendapatan << endl;

        cout << "\n===== STATISTIK USER =====\n";
        for (NodeStatUser* u = userHead; u; u = u->next)
            cout << u->user
                 << " | Transaksi: " << u->jumlahTransaksi << endl;
    }
};

#endif

