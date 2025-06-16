#ifndef AHORCADO_H
#define AHORCADO_H

#include "Juego.h"
#include <string>
#include <vector>

using namespace std;

class Ahorcado : public Juego
{
public:
    Ahorcado();
    Ahorcado(bool contraConsola);
    void jugar() override; // Ejecuta el juego
    bool jugarConUsuario(const string& nombreAdivina); // Devuelve true si gana, false si pierde
    void jugarDosJugadores(); // Gestiona el modo dos jugadores con rondas y registro
    void mostrarEstado();
    bool letraYaUsada(char letra);

private:
    string palabraSecreta;
    string palabraAdivinada;
    vector<char> letrasUsadas;
    int intentos;
};

#endif // AHORCADO_H