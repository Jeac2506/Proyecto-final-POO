#include <iostream>
#include <ctime>
#include <string>
#include "Ahorcado.h"
#include "Concentrese.h"

using namespace std;

// Función global para obtener la fecha y hora actual
string obtenerFechaHora() {
    time_t now = time(0); // Obtiene el tiempo actual en segundos desde Epoch
    tm* ltm = localtime(&now); // Convierte el tiempo a estructura de fecha y hora local
    char buffer[30];
    // Formatea la fecha y hora en el buffer como "YYYY-MM-DD HH:MM:SS"
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer); // Retorna la fecha y hora como string
}

int main()
{
    int opcion; // Variable para almacenar la opción del menú

    do
    {
        // Muestra el menú principal de juegos
        cout << "\n=== MENU DE JUEGOS ===\n";
        cout << "1. Jugar Ahorcado\n";
        cout << "2. Jugar Concentrese\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion; // Lee la opción del usuario

        switch(opcion)
        {
            case 1: { // Opción para jugar Ahorcado
                int modo; // Variable para el modo de juego
                cout << "Selecciona el modo de juego:\n";
                cout << "1. Contra la consola\n";
                cout << "2. Contra otro usuario\n";
                cout << "Selecciona una opcion: ";
                cin >> modo; // Lee el modo de juego
                if (modo == 1){
                    Ahorcado juego(true); // Crea un objeto Ahorcado en modo consola
                    juego.jugar(); // Inicia el juego contra la consola
                } else if (modo == 2) {
                    Ahorcado().jugarDosJugadores(); // Inicia el juego entre dos usuarios
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 2: { // Opción para jugar Concentrese
                int modo; // Variable para el modo de juego
                cout << "Selecciona el modo de juego:\n";
                cout << "1. Contra la consola\n";
                cout << "2. Contra otro usuario\n";
                cout << "Selecciona una opcion: ";
                cin >> modo; // Lee el modo de juego
                if (modo == 1){
                    Concentrese juego; // Crea un objeto Concentrese
                    juego.jugar(); // Inicia el juego contra la consola
                } else if (modo == 2){
                    Concentrese juego; // Crea un objeto Concentrese
                    juego.jugarDosJugadores(); // Inicia el juego entre dos usuarios
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 3:
                cout << "Gracias por jugar.\n"; // Mensaje de despedida
                break;
            default:
                cout << "Opcion invalida\n"; // Mensaje para opción no válida
        }

    } while (opcion != 3); // Repite el menú hasta que el usuario elija salir

    return 0; // Fin del programa
}