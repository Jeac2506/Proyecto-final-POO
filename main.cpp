#include <iostream>
#include "Ahorcado.h"

using namespace std;

int main()
{
    Juego* juego = new Ahorcado(); //Se implementa el polimorfismo
    juego->jugar(); //llama el metodo jugar() de la clase ahorcado
    delete juego;
    return 0;
}
