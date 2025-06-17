#include "Ahorcado.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Definición de la estructura ResultadoAhorcado
struct ResultadoAhorcado {
    string fecha;
    string jugador;
    string juego;
    string resultado;
    int puntos;
};

// Declaración anticipada (solo declaración, la definición está en main.cpp)
extern string obtenerFechaHora();

const string partesCuerpo[] = {
    "Cabeza",
    "Tronco",
    "Brazo Izquierdo",
    "Brazo Derecho",
    "Pierna Izquierda",
    "Pierna Derecha"
};
const int MaxIntentos = 6;

Ahorcado::Ahorcado(bool contraConsola){
    if (contraConsola){
        ifstream archivo("palabras.txt");
        vector<string> palabras;
        string palabra;
        while (archivo >> palabra) {
            palabras.push_back(palabra);
        }
        archivo.close();
        srand(time(0));
        palabraSecreta = palabras[rand() % palabras.size()];
    }
    else {
        cout << "Ingrese la palabra secreta: ";
        cin >> palabraSecreta;
        cout << string(50, '\n');
    }
    palabraAdivinada = string(palabraSecreta.size(), '_');
    letrasUsadas.clear();
    intentos = MaxIntentos;
}

Ahorcado::Ahorcado() {}

void Ahorcado::jugar()
{
    letrasUsadas.clear();
    palabraAdivinada = string(palabraSecreta.size(), '_');
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
            int parte = MaxIntentos - intentos;
            if (parte < MaxIntentos)
                cout << "¡Fallaste! : " << partesCuerpo[parte] << endl;
            intentos--;
        }
    }

    if (palabraAdivinada == palabraSecreta) {
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << endl;
    } else {
        cout << "Perdiste :c la palabra era: " << palabraSecreta << endl;
    }
}

bool Ahorcado::jugarConUsuario(const string& nombreAdivina){
    letrasUsadas.clear();
    palabraAdivinada = string(palabraSecreta.size(), '_');
    intentos = MaxIntentos;
    char letra;
    while (intentos > 0 && palabraAdivinada != palabraSecreta)
    {
        mostrarEstado();
        cout << nombreAdivina << ", ingresa una letra: ";
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
            int parte = MaxIntentos - intentos;
            if (parte < MaxIntentos)
                cout << "¡Fallaste! : " << partesCuerpo[parte] << endl;
            intentos--;
        }
    }

    if (palabraAdivinada == palabraSecreta){
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << endl;
        return true;
    }
    else{
        cout << "Perdiste :c la palabra era: " << palabraSecreta << endl;
        return false;
    }
}

void Ahorcado::jugarDosJugadores()
{
    string nombreJugador1, nombreJugador2;
    cout << "Ingrese el nombre del jugador 1: ";
    cin >> nombreJugador1;
    cout << "Ingrese el nombre del jugador 2: ";
    cin >> nombreJugador2;
    
    int rondas;
    do{
        cout << "¿Cuántas rondas quieren jugar? (1-5): ";
        cin >> rondas;
    }while (rondas < 1 || rondas > 5);

    int puntos1 = 0, puntos2 = 0;
    vector<ResultadoAhorcado> resultados;

    for (int ronda = 1; ronda <= rondas; ++ronda){
        cout << "\n--- Ronda " << ronda <<" ---\n";

        cout << nombreJugador1 << ", ingrese la palabra secreta para que " << nombreJugador2 << " la adivine.\n";
        Ahorcado* ahorcado1 = new Ahorcado(false);
        bool adivino2 = ahorcado1->jugarConUsuario(nombreJugador2);
        int puntosRonda2 = adivino2 ? 10 : 0;
        puntos2 += puntosRonda2;
        ResultadoAhorcado res2;
        res2.fecha = obtenerFechaHora();
        res2.jugador = nombreJugador2;
        res2.juego = "AH";
        res2.resultado = adivino2 ? "Gano" : "Perdio";
        res2.puntos = puntosRonda2;
        resultados.push_back(res2);
        delete ahorcado1;

        cout << nombreJugador2 << ", ingrese la palabra secreta para que " << nombreJugador1 << " la adivine.\n";
        Ahorcado* ahorcado2 = new Ahorcado(false);
        bool adivino1 = ahorcado2->jugarConUsuario(nombreJugador1);
        int puntosRonda1 = adivino1 ? 10 : 0;
        puntos1 += puntosRonda1;
        ResultadoAhorcado res1;
        res1.fecha = obtenerFechaHora();
        res1.jugador = nombreJugador1;
        res1.juego = "AH";
        res1.resultado = adivino1 ? "Gano" : "Perdio";
        res1.puntos = puntosRonda1;
        resultados.push_back(res1);
        delete ahorcado2;
    }

    cout << "\n### REGISTRO DE PARTIDAS ###\n";
    for (size_t i = 0; i < resultados.size(); ++i){
        const ResultadoAhorcado& r = resultados[i];
        cout << "[" << r.fecha << "] [" << r.jugador << "] [juego: " << r.juego << "] [resultado: " << r.resultado << "] [puntos: " << r.puntos << "]\n";
    }
    cout << "\n=== RESULTADOS FINALES ===\n";
    cout << nombreJugador1 << ": " << puntos1 << " puntos\n";
    cout << nombreJugador2 << ": " << puntos2 << " puntos\n";
    if (puntos1 > puntos2) {
        cout << nombreJugador1 << " gana la partida!\n";
    } else if (puntos2 > puntos1) {
        cout << nombreJugador2 << " gana la partida!\n";
    } else {
        cout << "Empate!\n";
    }
}

void Ahorcado::mostrarEstado()
{
    cout << "\nPalabra: ";
    for (char c : palabraAdivinada)
        cout << c << ' ';
    cout << "\nLetras usadas: ";
    for (char l : letrasUsadas)
        cout << l << ' ';
    cout << "\nIntentos restantes: " << intentos << endl;
}

bool Ahorcado::letraYaUsada(char letra)
{
    for (char l : letrasUsadas)
    {
        if (l == letra) return true;
    }
    return false;
}