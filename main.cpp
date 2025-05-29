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
        cout << "\n=== MENÚ DE JUEGOS ===\n";
        cout << "1. Jugar Ahorcado\n";
        cout << "2. Jugar Concentrese\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                juego = new Ahorcado();
                break;
            case 2:
                juego = new Concentrese();
                break;
            case 3:
                cout << "Gracias por jugar.\n";
                break;
            default:
                cout << "Opción invalida\n";
        }
        if (juego != nullptr)
        {
            juego->jugar();
            delete juego;
            juego = nullptr;
        }

    }while (opcion != 3);

    return 0;
}
