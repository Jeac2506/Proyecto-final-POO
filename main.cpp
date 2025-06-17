#include <iostream>
#include <ctime>
#include <string>
#include "Ahorcado.h"
#include "Concentrese.h"

using namespace std;

// Función global para obtener la fecha y hora actual
string obtenerFechaHora() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

int main()
{
    int opcion;

    do
    {
        cout << "\n=== MENU DE JUEGOS ===\n";
        cout << "1. Jugar Ahorcado\n";
        cout << "2. Jugar Concentrese\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1: {
                int modo;
                cout << "Selecciona el modo de juego:\n";
                cout << "1. Contra la consola\n";
                cout << "2. Contra otro usuario\n";
                cout << "Selecciona una opcion: ";
                cin >> modo;
                if (modo == 1){
                    Ahorcado juego(true);
                    juego.jugar();
                } else if (modo == 2) {
                    Ahorcado().jugarDosJugadores();
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 2: {
                int modo;
                cout << "Selecciona el modo de juego:\n";
                cout << "1. Contra la consola\n";
                cout << "2. Contra otro usuario\n";
                cout << "Selecciona una opcion: ";
                cin >> modo;
                if (modo == 1){
                    Concentrese juego;
                    juego.jugar();
                } else if (modo == 2){
                    Concentrese juego;
                    juego.jugarDosJugadores();
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 3:
                cout << "Gracias por jugar.\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 3);

    return 0;
}