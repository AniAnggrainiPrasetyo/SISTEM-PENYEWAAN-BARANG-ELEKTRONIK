#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct QueueNode {
    string user;
    int idBarang;
    QueueNode* next;
};

class QueuePembatalan {
    QueueNode *front, *rear;

public:
    QueuePembatalan() {
        front = rear = NULL;
    }

    void enqueue(string user, int id) {
        QueueNode* n = new QueueNode{user, id, NULL};
        if (!rear) {
            front = rear = n;
        } else {
            rear->next = n;
            rear = n;
        }
    }

    bool approve(string& user, int& id) {
        if (!front) return false;
        user = front->user;
        id = front->idBarang;

        QueueNode* del = front;
        front = front->next;
        if (!front) rear = NULL;
        delete del;
        return true;
    }

    void tampil() {
        QueueNode* t = front;
        while (t) {
            cout << t->user << " | " << t->idBarang << endl;
            t = t->next;
        }
    }

    // ? FILE-BASED (WAJIB ADA DI CLASS)
    void load() {
        ifstream f("queue.txt");
        if (!f) return;

        string u;
        int id;
        while (f >> u) {
            f.ignore();
            f >> id;
            enqueue(u, id);
        }
        f.close();
    }

    void save() {
        ofstream f("queue.txt");
        QueueNode* t = front;
        while (t) {
            f << t->user << "|" << t->idBarang << endl;
            t = t->next;
        }
        f.close();
    }
};

#endif

