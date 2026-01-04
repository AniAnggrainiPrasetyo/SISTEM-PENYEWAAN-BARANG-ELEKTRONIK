#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <string>
using namespace std;

// =======================
// NODE AVL TREE
// =======================
struct AVLNode {
    int id;
    string nama;
    int harga;
    int stok;
    int height;
    AVLNode* left;
    AVLNode* right;
};

// =======================
// CLASS AVL TREE
// =======================
class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* n) {
        return n ? n->height : 0;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getBalance(AVLNode* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node, int id, string nama, int harga, int stok) {
        if (!node) {
            AVLNode* n = new AVLNode{id, nama, harga, stok, 1, NULL, NULL};
            return n;
        }

        if (id < node->id)
            node->left = insertNode(node->left, id, nama, harga, stok);
        else if (id > node->id)
            node->right = insertNode(node->right, id, nama, harga, stok);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // LL
        if (balance > 1 && id < node->left->id)
            return rotateRight(node);

        // RR
        if (balance < -1 && id > node->right->id)
            return rotateLeft(node);

        // LR
        if (balance > 1 && id > node->left->id) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL
        if (balance < -1 && id < node->right->id) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->id << " | "
             << node->nama << " | "
             << node->harga << " | "
             << node->stok << endl;
        inorder(node->right);
    }

    // ===================
    // SEARCH AVL
    // ===================
    AVLNode* cariNode(AVLNode* node, int id) {
        if (!node) return NULL;
        if (id == node->id) return node;
        if (id < node->id) return cariNode(node->left, id);
        return cariNode(node->right, id);
    }

public:
    AVLTree() {
        root = NULL;
    }

    void insert(int id, string nama, int harga, int stok) {
        root = insertNode(root, id, nama, harga, stok);
    }

    void tampil() {
        cout << "\n=== DATA BARANG (AVL TREE - SORTED) ===\n";
        cout << "ID | Nama | Harga | Stok\n";
        inorder(root);
    }

    AVLNode* cari(int id) {
        return cariNode(root, id);
    }
};

#endif

