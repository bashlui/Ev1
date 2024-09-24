#include "Classes/Bitacoras.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<Bitacoras> bitacoras;

void showBitacorasList() {
    Bitacoras bitacoraInstance;
    bitacoraInstance.loadBitacoras(bitacoras);
    bitacoraInstance.printBitacorasList(bitacoras);
}
void sortAndSaveBitacoras() {
    Bitacoras bitacoraInstance;
    bitacoraInstance.loadBitacoras(bitacoras);

    // Hacer una copia del vector original antes de ordenar
    std::vector<Bitacoras> bitacorasOrdenadas = bitacoras;
    bitacoraInstance.quickSort(bitacorasOrdenadas, 0, bitacorasOrdenadas.size() - 1);

    // Preguntar si desea guardar las bitácoras ordenadas
    cout << "Deseas guardar las bitacoras ordenadas en un archivo? (s/n): ";
    char saveOption;
    cin >> saveOption;

    if (saveOption == 's' || saveOption == 'S') {
        string outputFile;
        cout << "Ingresa el nombre del archivo para guardar las bitácoras ordenadas (por ejemplo, 'bitacoras_ordenadas.txt'): ";
        cin >> outputFile;
        bitacoraInstance.saveSortedBitacorasToFile(bitacorasOrdenadas, outputFile); // Guardar la copia ordenada
    }
}

void searchBitacoras() {
    Bitacoras bitacoraInstance;
    bitacoraInstance.loadBitacoras(bitacoras);

    std::vector<Bitacoras> bitacorasOrdenadas = bitacoras;
    bitacoraInstance.quickSort(bitacorasOrdenadas, 0, bitacorasOrdenadas.size() - 1);

    cout << "Dame la fecha inicial (mes y día) para buscar bitacoras (por ejemplo, 'Jun 1'): ";
    string month, dayStr;
    cin >> month >> dayStr;

    cout << "Dame la fecha final (mes y día) para buscar bitacoras (por ejemplo, 'Jun 30'): ";
    string month2, dayStr2;
    cin >> month2 >> dayStr2;

    unsigned int startDay = stoi(dayStr);
    unsigned int endDay = stoi(dayStr2);

    bitacoraInstance.searchBitacorasInRange(bitacorasOrdenadas, month, startDay, month2, endDay);
}
  

int main() {
    int n;
    Bitacoras bitacoraInstance;

    // Bucle para mostrar el menú de manera repetitiva
    while (n != 4) {
        cout << "Bienvenido al sistema de bitacoras" << endl;
        cout << "Seleccione una de las opciones del menu" << endl;
        cout << "1. Mostrar bitacoras" << endl;
        cout << "2. Ordenar bitacoras" << endl;
        cout << "3. Buscar bitacoras" << endl;
        cout << "4. Salir" << endl;
        cin >> n;

        switch(n) {
            case 1:
                showBitacorasList();
                break;
            case 2:
            {
                sortAndSaveBitacoras();
                break;
            }
            break;
            case 3:
            {
                searchBitacoras();
                break;
            }
            case 4:
                cout << "Saliendo del sistema de bitacoras." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
            break;
        }
    }

    return 0;
}

