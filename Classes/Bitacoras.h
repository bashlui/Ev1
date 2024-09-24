// Bitacoras.h
#ifndef BITACORAS_H
#define BITACORAS_H

#include <vector>
#include <string>

class Bitacoras {
    private:
    std::string month;
    unsigned int day;
    std::string hour;
    std::string ip;
    std::string message;

    public:
        Bitacoras();
        Bitacoras(std::string &_month, unsigned int _day, std::string &_hour, std::string &_ip, std::string &_message);

        std::string getMonth() const;
        unsigned int getDay() const;
        std::string getHour() const;
        std::string getIp() const;
        std::string getMessage() const;

        int monthToNumber(const std::string &month);   
        static std::string trim(const std::string &str);
        void loadBitacoras(std::vector<Bitacoras> &bitacoras);
        void printBitacorasList(std::vector<Bitacoras> &bitacoras);
        void saveSortedBitacorasToFile(const std::vector<Bitacoras> &bitacoras, const std::string &filename);
        void quickSort(std::vector<Bitacoras>& bitacoras, int low, int high);
        int partition(std::vector<Bitacoras>& bitacoras, int lo, int high);
        int sequentialSearchMonth(const std::vector<Bitacoras> &bitacoras, const std::string &month);
        int sequentialSearchDay(const std::vector<Bitacoras> &bitacoras, unsigned int day);
};

#endif // BITACORAS_H