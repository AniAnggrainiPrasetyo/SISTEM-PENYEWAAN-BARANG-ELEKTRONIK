#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct StackNode {
    string log;
    StackNode* next;
};

class StackLog {
    StackNode* top;

public:
    StackLog() {
        top = NULL;
    }

    void push(string s) {
        StackNode* n = new StackNode{s, top};
        top = n;
    }

    void tampil() {
        StackNode* t = top;
        while (t) {
            cout << t->log << endl;
            t = t->next;
        }
    }

    // ? FILE-BASED
    void load() {
        ifstream f("log.txt");
        if (!f) return;

        string s;
        while (getline(f, s)) {
            push(s);
        }
        f.close();
    }

    void save() {
        ofstream f("log.txt");
        StackNode* t = top;
        while (t) {
            f << t->log << endl;
            t = t->next;
        }
        f.close();
    }
};

#endif

