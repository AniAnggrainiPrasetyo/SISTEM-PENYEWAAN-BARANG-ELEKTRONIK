#include "ktp.h"
#include <fstream>
#include <sstream>

bool loginKTP(const std::string& nik, std::string& nama) {
    std::ifstream file("data_ktp_login.txt");
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string nikFile, namaFile;

        getline(ss, nikFile, '|');
        getline(ss, namaFile);

        if (nik == nikFile) {
            nama = namaFile;
            return true;
        }
    }
    return false;
}

