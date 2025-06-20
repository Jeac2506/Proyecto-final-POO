#ifndef CONCENTRESE_H
#define CONCENTRESE_H

#include "Juego.h"
#include <vector>
#include <string>
using namespace std;


class Concentrese : public Juego
{
public:

    Concentrese();
    // Constructor que permite especificar si se juega contra la consola
    Concentrese(bool contraConsola);

    // Método para jugar (sobrescribe el método virtual de Juego)
    void jugar() override;

    // Método para jugar en modo dos jugadores
    void dosJugadores();

private:
    vector<string> simbolos;     // Vector que almacena los símbolos del tablero
    vector<bool> descubiertas;   // Vector que indica qué cartas han sido descubiertas
    int filas, columnas;         // Dimensiones del tablero

    // Método para cargar los símbolos en el tablero
    void cargarSimbolos();

    // Método para mostrar el tablero en consola
    void mostrarTablero();

    // Método que verifica si todas las cartas han sido descubiertas
    bool todasDescubiertas();

    // Método para registrar el resultado de la partida
    void registrarResultado(const string &jugador, const string &resultado, int puntos);

    int maxIntentos;             // Número máximo de intentos permitidos
};

#endif // CONCENTRESE_H