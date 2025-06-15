#ifndef JUEGO_H
#define JUEGO_H


class Juego
{
    public:
        virtual void jugar() = 0; // Metodo puro (obligatorio de implementar en las clases hijas)
    virtual ~Juego() {} // Destructor virtual para evitar errores al borrar punteros

};

#endif // JUEGO_H
