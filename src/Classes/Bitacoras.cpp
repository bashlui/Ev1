#include "Bitacoras.h"
# include <iostream>
# include <fstream>
# include <sstream>
# include <utility>
# include <vector>
# include <algorithm>

using namespace std;

Bitacoras::Bitacoras() {
    month = "";
    day = 0;
    hour = "";
    ip = "";
    message = "";
}

Bitacoras::Bitacoras(std::string &_month, unsigned int _day, std::string &_hour, std::string &_ip, std::string &_message) {
    month = _month;
    day = _day;
    hour = _hour;
    ip = _ip;
    message = _message;
}

std::string Bitacoras::getMonth() const {
    return month;
}

unsigned int Bitacoras::getDay() const {
    return day;
}

std::string Bitacoras::getHour() const {
    return hour;
}

std::string Bitacoras::getIp() const {
    return ip;
}

std::string Bitacoras::getMessage() const {
    return message;
}

std::string Bitacoras::trim(const string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

void Bitacoras::loadBitacoras(vector<Bitacoras> &bitacoras) {
    ifstream file("Data/bitacora.txt");
    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string month, dayStr, hour, ip, message;
        
        if (getline(ss, month, ' ') && 
            getline(ss, dayStr, ' ') &&
            getline(ss, hour, ' ') &&
            getline(ss, ip, ' ') &&
            getline(ss, message)) {
            
            month = trim(month);
            dayStr = trim(dayStr);
            hour = trim(hour);
            ip = trim(ip);
            message = trim(message);

            try {
                unsigned int dayInt = stoi(dayStr);
                bitacoras.emplace_back(month, dayInt, hour, ip, message);
            } catch (const invalid_argument &e) {
                cout << "Error: " << e.what() << endl;
                continue;
            }
        }
    }
    file.close();
}

void Bitacoras::printBitacorasList(vector<Bitacoras> &bitacoras) {
    for (int i = 0; i <= bitacoras.size(); i++) {
        cout << bitacoras[i].getMonth() << " " << bitacoras[i].getDay() << " " << bitacoras[i].getHour() << " " << bitacoras[i].getIp() << " " << bitacoras[i].getMessage() << endl;
    }
}


int Bitacoras::monthToNumber(const std::string &month) {
    if (month == "Jun") return 6;
    if (month == "Jul") return 7;
    if (month == "Aug") return 8;
    if (month == "Sep") return 9;
    if (month == "Oct") return 10;
    return -1;
}

int Bitacoras::partition(std::vector<Bitacoras>& bitacoras, int low, int high) {
    Bitacoras pivot = bitacoras[high];  // Pivote
    int i = low - 1;  // Índice del elemento más pequeño

    for (int j = low; j < high; j++) {
        // Si el elemento actual es menor o igual que el pivote (comparar por mes y día)
        if (monthToNumber(bitacoras[j].getMonth()) < monthToNumber(pivot.getMonth()) ||
            (monthToNumber(bitacoras[j].getMonth()) == monthToNumber(pivot.getMonth()) &&
             bitacoras[j].getDay() <= pivot.getDay())) {
            i++;
            swap(bitacoras[i], bitacoras[j]);
        }
    }
    swap(bitacoras[i + 1], bitacoras[high]);
    return i + 1;
}

void Bitacoras::quickSort(std::vector<Bitacoras>& bitacoras, int low, int high) {
    if (low < high) {
        // Índice de partición
        int pi = partition(bitacoras, low, high);

        // Ordenar los elementos antes y después de la partición
        quickSort(bitacoras, low, pi - 1);
        quickSort(bitacoras, pi + 1, high);
    }
}

void Bitacoras::saveSortedBitacorasToFile(const std::vector<Bitacoras> &bitacoras, const std::string &filename) {
    ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        std::cout << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    for (const auto &bitacora : bitacoras) {
        outFile << bitacora.getMonth() << " "
                << bitacora.getDay() << " "
                << bitacora.getHour() << " "
                << bitacora.getIp() << " "
                << bitacora.getMessage() << std::endl;
    }

    outFile.close();
    std::cout << "Bitácoras ordenadas guardadas en: " << filename << std::endl;
}

void Bitacoras::searchBitacorasInRange(const std::vector<Bitacoras>& bitacoras, const std::string& startMonth, unsigned int startDay, const std::string& endMonth, unsigned int endDay) {
    int startMonthNum = monthToNumber(startMonth);
    int endMonthNum = monthToNumber(endMonth);

    if (startMonthNum == -1 || endMonthNum == -1) {
        std::cout << "Mes inválido proporcionado." << std::endl;
        return;
    }

    std::cout << "Bitácoras encontradas en el rango especificado:" << std::endl;
    bool found = false;

    for (const auto& bitacora : bitacoras) {
        int currentMonthNum = monthToNumber(bitacora.getMonth());
        unsigned int currentDay = bitacora.getDay();

        // Verificar si el registro está dentro del rango
        if ((currentMonthNum > startMonthNum || (currentMonthNum == startMonthNum && currentDay >= startDay)) &&
            (currentMonthNum < endMonthNum || (currentMonthNum == endMonthNum && currentDay <= endDay))) {
            std::cout << bitacora.getMonth() << " " << bitacora.getDay() << " " 
                      << bitacora.getHour() << " " << bitacora.getIp() << " " 
                      << bitacora.getMessage() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No se encontraron bitácoras dentro del rango especificado." << std::endl;
    }
}
