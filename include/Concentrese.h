#ifndef CONCENTRESE_H
#define CONCENTRESE_H

#include "Juego.h"

class Concentrese : public Juego
{
    public:
        Concentrese();
        Concentrese (bool contraConsola);
        void jugar() override;
        void jugarDosJugadores();

    protected:

    private:
    vector <string> simbolos;
    vector <bool> descubiertas;
    int filas, columnas;
    void cargarSimbolos();
    void mostrarTablero();
    void TableroDescubiertas();
    void registrarResultado(const string &jugador, const string& resultado, int puntos);
};

#endif // CONCENTRESE_H
