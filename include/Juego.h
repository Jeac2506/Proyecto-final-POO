#ifndef JUEGO_H
#define JUEGO_H

class Juego
{
public:
    virtual void jugar() = 0;           // Método puro obligatorio
    virtual ~Juego() = 0;               // Destructor puro
};

inline Juego::~Juego() {} // Definición vacía del destructor puro

#endif // JUEGO_H