#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

enum Role { ADMIN, USER };

struct NodeUser {
    string username;
    string password;
    Role role;
    NodeUser* next;
};

class UserManager {
private:
    NodeUser* head;

public:
    UserManager() {
        head = NULL;
        // admin
        tambah("admin", "admin123", ADMIN);
        // user tanpa password
        tambah("andi", "", USER);
        tambah("budi", "", USER);
    }

    void tambah(string u, string p, Role r) {
        NodeUser* baru = new NodeUser{u, p, r, head};
        head = baru;
    }

    NodeUser* login(string u, string p = "") {
        NodeUser* cur = head;
        while (cur) {
            if (cur->username == u &&
                (cur->role == USER || cur->password == p))
                return cur;
            cur = cur->next;
        }
        return NULL;
    }
};

#endif

