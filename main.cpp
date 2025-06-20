#include <iostream>
#include <ctime>
#include <string>
#include "Ahorcado.h"
#include "Concentrese.h"

using namespace std;

// Funcion para obtener la fecha y hora actual en formato YYYY-MM-DD HH:MM:SS
string obtenerFechaHora() {
    time_t now = time(0); // Obtiene el tiempo actual
    tm* ltm = localtime(&now); // Convierte el tiempo a formato local
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm); // Da formato a la fecha y hora
    return string(buffer); // Retorna la fecha y hora como string
}

int main()
{
    int opcion = 0; // Variable para almacenar la opción del menú principal

    do
    {
        // Muestra el menú principal de juegos
        cout << "\n=== MENU DE JUEGOS ===\n";
        cout << "1. Jugar Ahorcado\n";
        cout << "2. Jugar Concentrese\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        // Manejo de error por si el usuario ingresa un valor no numérico
        if (cin.fail()) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(1000, '\n'); // Descarta la entrada incorrecta
            opcion = 0;
        }

        switch(opcion)
        {
            case 1: { // Opción para jugar Ahorcado
                int modo = 0; // Variable para el modo de juego
                do {
                    // Muestra el submenú de modos de juego para Ahorcado
                    cout << "Selecciona el modo de juego:\n";
                    cout << "1. Contra la consola\n";
                    cout << "2. Contra otro usuario\n";
                    cout << "Selecciona una opcion: ";
                    cin >> modo;
                    // Manejo de error de entrada
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        modo = 0;
                    }
                    if (modo == 1){
                        // Modo contra la consola
                        Ahorcado juego(true);
                        juego.jugar();
                    } else if (modo == 2) {
                        // Modo dos jugadores
                        Ahorcado().dosJugadores();
                    } else if (modo != 0) {
                        cout << "Opcion invalida.\n";
                    }
                } while (modo != 1 && modo != 2); // Repite hasta que se seleccione un modo válido
                break;
            }
            case 2: { // Opción para jugar Concentrese
                int modo = 0; // Variable para el modo de juego
                do {
                    // Muestra el submenú de modos de juego para Concentrese
                    cout << "Selecciona el modo de juego:\n";
                    cout << "1. Contra la consola\n";
                    cout << "2. Contra otro usuario\n";
                    cout << "Selecciona una opcion: ";
                    cin >> modo;
                    // Manejo de error de entrada
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        modo = 0;
                    }
                    if (modo == 1){
                        // Modo contra la consola
                        Concentrese juego;
                        juego.jugar();
                    } else if (modo == 2){
                        // Modo dos jugadores
                        Concentrese juego;
                        juego.dosJugadores();
                    } else if (modo != 0) {
                        cout << "Opcion invalida.\n";
                    }
                } while (modo != 1 && modo != 2); // Repite hasta que se seleccione un modo válido
                break;
            }
            case 3:
                // Opción para salir del programa
                cout << "Gracias por jugar.\n";
                break;
            default:
                // Manejo de opción inválida en el menú principal
                cout << "Opcion invalida\n";
        }

    } while (opcion != 3); // El ciclo se repite hasta que el usuario elija salir

    return 0; // Fin del programa
}