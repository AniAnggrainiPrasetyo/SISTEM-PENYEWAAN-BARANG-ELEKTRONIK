#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct HuffNode {
    char ch;
    int freq;
    HuffNode *left, *right;

    HuffNode(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

struct Compare {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

class HuffmanTree {
public:
    HuffNode* build(map<char,int> freq) {
        priority_queue<HuffNode*, vector<HuffNode*>, Compare> pq;

        for (auto p : freq)
            pq.push(new HuffNode(p.first, p.second));

        while (pq.size() > 1) {
            HuffNode* l = pq.top(); pq.pop();
            HuffNode* r = pq.top(); pq.pop();

            HuffNode* n = new HuffNode('-', l->freq + r->freq);
            n->left = l;
            n->right = r;
            pq.push(n);
        }
        return pq.top();
    }

    void generate(HuffNode* root, string s, map<char,string>& code) {
        if (!root) return;
        if (root->ch != '-')
            code[root->ch] = s;

        generate(root->left, s + "0", code);
        generate(root->right, s + "1", code);
    }
};

#endif

