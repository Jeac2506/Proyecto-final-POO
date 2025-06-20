#ifndef JUEGO_H
#define JUEGO_H

class Juego
{
public:
    virtual void jugar() = 0;                // Método puro obligatorio
    virtual void dosJugadores() = 0;    // Método puro obligatorio para dos jugadores
    virtual ~Juego() = 0;                    // Destructor puro
};

inline Juego::~Juego() {} // Definición vacía del destructor puro

#endif // JUEGO_H