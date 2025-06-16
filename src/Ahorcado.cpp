#include "Ahorcado.h"
#include <iostream>
#include <cstdlib> // para rand()
#include <ctime>   // para time()
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const string partesCuerpo[] = {
    "Cabeza",
    "Tronco",
    "Brazo Izquierdo",
    "Brazo Derecho",
    "Pierna Izquierda",
    "Pierna Derecha"
};
const int MaxIntentos = 6;

Ahorcado::Ahorcado(bool  contraConsola){
    if (contraConsola){
        ifstream archivo("palabras.txt");
        vector <string> palabras;
        string palabra;
        while (archivo >> palabra) // las >> se usan para leer palabras
        {
            palabras.push_back(palabra);
        }
        archivo.close();
        srand(time(0)); // este es para generar numeros aleatorios
        palabraSecreta = palabras[rand() % palabras.size()];
    }
    else {
        cout << "Ingrese la palabra secreta:";
        cin >> palabraSecreta;
        cout << string(50, '\n'); // se utiliza para limpiar la pantalla
    }
    palabraAdivinada = string(palabraSecreta.size(), '_'); // se hace esto para que la palabra adivinada tenga el mismo tamaño que la palabra secreta
    letrasUsadas.clear();
    intentos = MaxIntentos;
}

Ahorcado::Ahorcado() {}

void Ahorcado::jugar()
{
    letrasUsadas.clear();
    palabraAdivinada = string (palabraSecreta.size(), '_');
    intentos = MaxIntentos;
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
        bool acierto = false; // Solo una variable acierto

        for (size_t i = 0; i < palabraSecreta.size(); i++)
        {
            if (palabraSecreta[i] == letra)
            {
                palabraAdivinada[i] = letra;
                acierto = true;
            }
        }
        if (!acierto)
        {
            int parte = MaxIntentos - intentos; // Calcular la parte del cuerpo a dibujar
            if (parte < MaxIntentos)
               cout << "¡Fallaste! : " << partesCuerpo[parte] << endl;
            intentos--;
        }
    }

    if (palabraAdivinada == palabraSecreta)
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << endl;
    else
        cout << "Perdiste :c la palabra era: " << palabraSecreta << endl;
}
void Ahorcado::jugarConUsuario(const string& nombreAdivina){
    letrasUsadas.clear();
    palabraAdivinada = string(palabraSecreta.size(), '_');
    intentos = MaxIntentos;
    char letra;
    while (intentos > 0 && palabraAdivinada != palabraSecreta)
    {
        mostrarEstado();
        cout << nombreAdivina << ", Ingresa una letra: ";
        cin >> letra;

        if (letraYaUsada(letra))
        {
            cout << "Ya usaste esa letra.\n";
            continue;
        }

        letrasUsadas.push_back(letra);
        bool acierto = false;

        for (size_t i = 0; i < palabraSecreta.size(); i++)
        {
            if (palabraSecreta[i] == letra)
            {
                palabraAdivinada[i] = letra;
                acierto = true;
            }
        }
        if (!acierto)
        {
            int parte = MaxIntentos - intentos; // Calcular la parte del cuerpo a dibujar
            if (parte < MaxIntentos)
               cout << "¡Fallaste! : " << partesCuerpo[parte] << endl;
            intentos--;
        }
    }

    if (palabraAdivinada == palabraSecreta){
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << endl;
    }
    else{
        cout << "Perdiste :c la palabra era: " << palabraSecreta << endl;
    }
}

void Ahorcado::mostrarEstado()
{
    cout << "\nPalabra: " << palabraAdivinada << "\n";
    cout << "Letras usadas: ";
    for (char c : palabraAdivinada)
        cout << c << ' ';
    cout << "\nLetras usadas: ";
    for (char l : letrasUsadas)
        cout << l << ' ';
    cout << "\n Intentos restantes: " << intentos << endl;
}

bool Ahorcado::letraYaUsada(char letra)
{
    for (char l : letrasUsadas)
    {
        if (l == letra) return true;
    }
    return false;
}