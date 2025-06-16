#include <iostream>
#include "Ahorcado.h"
#include "Concentrese.h"

using namespace std;

int main()
{
    int opcion;
    Juego* juego = nullptr;

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
            case 1:
                int modo;
                cout << "Selecciona el modo de juego:\n";
                cout << "1. Contra la consola\n";
                cout << "2. Contra otro usuario\n";
                cout << "Selecciona una opcion: ";
                cin >> modo;
                if (modo == 1){
                    juego = new Ahorcado(true);
                    juego ->jugar();
                    delete juego; // Liberar memoria
                    juego = nullptr;
                }else if (modo ==2) {
                    string nombre;
                    cout << "Nombre del jugador que adivina: ";
                    cin >> nombre;
                    Ahorcado* ahorcado = new Ahorcado(false);
                    ahorcado->jugarConUsuario(nombre);
                    delete ahorcado; // Liberar memoria
                }else {
                    cout << "Opcion invalida.\n";
                }break;
            case 2:
                juego = new Concentrese();
                break;
            case 3:
                cout << "Gracias por jugar.\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
        if (juego != nullptr)
        {
            juego->jugar();
            delete juego;
            juego = nullptr;
        }

    } while (opcion != 3);

    return 0;
}
