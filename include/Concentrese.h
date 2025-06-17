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
    Concentrese(bool contraConsola);
    void jugar() override;
    void jugarDosJugadores();

private:
    vector<string> simbolos;
    vector<bool> descubiertas;
    int filas, columnas;
    void cargarSimbolos();
    void mostrarTablero();
    bool todasDescubiertas();
    void registrarResultado(const string &jugador, const string &resultado, int puntos);
};

#endif // CONCENTRESE_H