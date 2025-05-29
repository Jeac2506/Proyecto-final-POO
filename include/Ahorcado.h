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
        void jugar() override; //Ac� se implementa el m�todo abstracto
        void mostrarEstado();
        bool letraYaUsada(char letra); //para verificar si ya se us� la letra


    private:
        string palabraSecreta;
        string palabraAdivinada;
        vector<char> letrasUsadas;
        int intentos;
};

#endif // AHORCADO_H
