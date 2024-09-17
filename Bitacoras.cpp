#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility> // For std::pair
#include <unordered_map>

using namespace std;

class Bitacoras {
public:
    Bitacoras(string month, unsigned int day, string hour, string ip, string message)
        : month(std::move(month)), day(day), hour(std::move(hour)), ip(std::move(ip)), message(std::move(message)) {}

    // Optional: Provide a method to display the Bitacora data
    friend ostream& operator<<(ostream& os, const Bitacoras& bitacora) {
        os << bitacora.month << ' ' << bitacora.day << ' ' << bitacora.hour << ' ' << bitacora.ip << ' ' << bitacora.message;
        return os;
    }

    static void loadBitacoras(vector<Bitacoras> &bitacoras) {
        ifstream file("../data/bitacora.txt");
        if (!file.is_open()) {
            cout << "Error al abrir el archivo" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string month, day, hour, ip, message;
            unsigned int monthDay;

            if (
                getline(ss, month, ' ') &&
                getline(ss, day, ' ') &&
                getline(ss, hour, ' ') &&
                getline(ss, ip, ' ') &&
                getline(ss, message, ' ')) {

                month = trim(month);
                hour = trim(hour);
                ip = trim(ip);
                message = trim(message);

                try {
                    monthDay = stoi(day);
                    bitacoras.emplace_back(month, monthDay, hour, ip, message);

                } catch (const invalid_argument &e) {
                    cout << "Error al convertir el día a entero: " << e.what() << endl;
                    continue;
                }
            }
        }
    }

     void assignMonthNumber(vector<Bitacoras> &bitacoras) {
        unordered_map<string, int> monthMap = {
            {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
            {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
            {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
        };

        for (int i = 0; i < bitacoras.size(); i++) {
            bitacoras[i].month = monthMap[bitacoras[i].month];
        }
    }

    static void printBitacoras(vector<Bitacoras> &bitacoras) {
        for (const auto &bitacora : bitacoras) {
            cout << bitacora << endl;
        }
    }

private:
    string month;
    unsigned int day;
    string hour;
    string ip;
    string message;

    static string trim(const string &str) {
        size_t first = str.find_first_not_of(' ');
        if (string::npos == first) {
            return "";
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    // Complejidad O(1)
    void swapF(vector<int> &A, int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }


     static void bubbleSortFlag(vector<int> &A) {
        bool flag;
        for (int i = 0; i < A.size() - 1; i++) {
            flag = false;
            for (int j = i; j < A.size() - i; j++) {
                if (A[j] > A[j + 1]) {
                    swap(A[j], A[j + 1]);
                    flag = true;
                }
            }
            if (flag == false) {
                break;
            }
        }
    }
};

int main() {
    vector<Bitacoras> bitacoras;
    bitacoras.
    

    return 0;
}
