#include "Ahorcado.h"
#include <iostream>
#include <cstdlib> // para rand()
#include <ctime> // para time()


using namespace std;

Ahorcado::Ahorcado()
{
    //Las palabras que se pueden elegir aleatoriamente
    vector<string> palabras = {"programacion", "herencia","parcial", "universidad", "computador", "ahorcado"};
    srand(time(0)); //Una semilla que sirve para la aleatoridad
    palabraSecreta = palabras[rand() % palabras.size()]; //Selecciona una palabra al azar.
    palabraAdivinada = string(palabraSecreta.size(), '_');
    intentos = 6;

}

void Ahorcado::jugar()
{
    bool acierto = false;         // para saber si el jugador adivina bien en un turno
    vector<char>  letrasIncorrectas;
    char letra;
    while (intentos > 0 && palabraAdivinada != palabraSecreta)
    {
        mostrarEstado();
        cout << "Ingresa una letra: ";
        cin >> letra;

        if (letraYaUsada(letra))
        {
            cout << "Ya usaste esa letra.\n";
            continue;
        }

        letrasUsadas.push_back(letra);
        bool acerto = false;

        for (size_t i = 0; i < palabraSecreta.size(); i++)
        {
            if (palabraSecreta[i] == letra)
            {
                palabraAdivinada[i] = letra;
                acerto = true;
            }
        }
        if (!acierto)
        {
            letrasIncorrectas.push_back(letra);
            intentos--;
        }
    }

    if (palabraAdivinada == palabraSecreta)
        cout << "�Ganaste! La palabra era: " << palabraSecreta << endl;
    else
        cout << "Perdiste :c la palabra era: " << palabraSecreta << endl;
}

void Ahorcado::mostrarEstado()
{
    cout << "Palabra: " << palabraAdivinada << "\n";
    cout << "Letras usadas: ";
    for (char l : letrasUsadas)
    {
        cout << l << ' ';
    }
    cout << "\n";
}

bool Ahorcado::letraYaUsada(char letra)
{
    for (char l : letrasUsadas)
    {
        if (l == letra) return true;
    }
    return false;
}
