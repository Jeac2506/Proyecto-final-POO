#include "Concentrese.h"
#include <iostream>
#include <fstream>
// <ctime> se usa para obtener la hora actual (semilla para srand) el srand es para mezclar los símbolos
// <cstdlib> se usa para srand y rand (mezclar símbolos aleatoriamente)
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

// Declaración externa de una función para obtener la fecha y hora actual
extern string obtenerFechaHora();

// Constructor por defecto: inicializa el tablero de 4x4 y los intentos máximos
Concentrese::Concentrese() : filas(4), columnas(4), maxIntentos(30) {
    cargarSimbolos(); // Carga y mezcla los símbolos para el juego
}

// Constructor alternativo (no usa el parámetro), igual inicializa el tablero
Concentrese::Concentrese(bool /*contraConsola*/) : filas(4), columnas(4), maxIntentos(30) {
    cargarSimbolos();
}

// Carga los símbolos desde un archivo, los duplica y los mezcla aleatoriamente
void Concentrese::cargarSimbolos() {
    ifstream archivo("simbolos.txt"); // Abre el archivo de símbolos
    string simbolo;
    simbolos.clear(); // Limpia el vector de símbolos
    // Lee símbolos y los agrega dos veces (para formar parejas)
    while (archivo >> simbolo) {
        simbolos.push_back(simbolo);
        simbolos.push_back(simbolo);
        if ((int)simbolos.size() >= filas * columnas) break; // Solo los necesarios
    }
    archivo.close();
    // Mezcla aleatoriamente los símbolos usando Fisher-Yates
    srand(time(0));
    for (int i = simbolos.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(simbolos[i], simbolos[j]);
    }
    // Inicializa el vector de descubiertas en falso (todas ocultas)
    descubiertas = vector<bool>(filas * columnas, false);
}

// Muestra el tablero en consola, revelando símbolos descubiertos y ocultando los demás
void Concentrese::mostrarTablero() {
    cout << "\nTablero:\n";
    for (int i = 0; i < filas * columnas; ++i) {
        if (descubiertas[i])
            cout << " " << simbolos[i] << " "; // Muestra símbolo si está descubierto
        else {
            // Muestra el número de la casilla si está oculta
            if (i + 1 < 10)
                cout << " " << i + 1 << " ";
            else
                cout << i + 1 << " ";
        }
        if ((i + 1) % columnas == 0) cout << endl; // Salto de línea al final de cada fila
    }
}

// Verifica si todas las casillas han sido descubiertas
bool Concentrese::todasDescubiertas() {
    for (size_t i = 0; i < descubiertas.size(); ++i)
        if (!descubiertas[i]) return false; // Si alguna está oculta, retorna falso
    return true;
}

// Registra el resultado de la partida en un archivo compartido con otros juegos
void Concentrese::registrarResultado(const string& jugador, const string& resultado, int puntuacion) {
    ofstream archivo("registro_partidas.txt", ios::app); // Abre archivo en modo adjuntar
    archivo << "[" << obtenerFechaHora() << "] [" << jugador << "] [juego: MEM] [resultado: " << resultado << "] [puntuacion: " << puntuacion << "]\n";
    archivo.close();
}

// Lógica principal para jugar contra la consola (un jugador)
void Concentrese::jugar() {
    string jugador;
    cout << "Nombre del jugador: ";
    cin >> jugador;
    // Solicita el número de intentos máximos
    cout << "¿Cuántos intentos máximos deseas? (recomendado 30): ";
    while (!(cin >> maxIntentos) || maxIntentos <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ingresa un número válido de intentos: ";
    }
    int intentos = 0, aciertos = 0;
    string resultado;
    // Bucle principal del juego: termina si se descubren todas o se acaban los intentos
    while (!todasDescubiertas() && intentos < maxIntentos) {
        mostrarTablero(); // Muestra el estado actual del tablero
        int pos1, pos2;
        // Solicita la primera casilla al jugador
        cout << jugador << ", elige la primera casilla: ";
        while (!(cin >> pos1) || pos1 < 1 || pos1 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Ingresa un número válido: ";
        }
        // Solicita la segunda casilla al jugador
        cout << jugador << ", elige la segunda casilla: ";
        while (!(cin >> pos2) || pos2 < 1 || pos2 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Ingresa un número válido: ";
        }
        --pos1; --pos2; // Ajusta a índice base 0
        // Verifica que las posiciones sean válidas y no descubiertas
        if (pos1 == pos2 || descubiertas[pos1] || descubiertas[pos2]) {
            cout << "Posiciones inválidas. Intenta de nuevo.\n";
            continue;
        }
        // Muestra los símbolos seleccionados
        cout << "Descubres: " << simbolos[pos1] << " y " << simbolos[pos2] << endl;
        if (simbolos[pos1] == simbolos[pos2]) {
            cout << "¡Pareja encontrada!\n";
            descubiertas[pos1] = descubiertas[pos2] = true; // Marca como descubiertas
            aciertos++;
        } else {
            cout << "No son pareja.\n";
        }
        intentos++;
    }
    // Determina el resultado y lo muestra
    if (todasDescubiertas()) {
        cout << "¡Felicidades " << jugador << "! Terminaste en " << intentos << " turnos.\n";
        resultado = "G"; // Ganador
    } else {
        cout << "Se acabaron los intentos. ¡Perdiste!\n";
        resultado = "P"; // Perdedor
    }
    registrarResultado(jugador, resultado, aciertos); // Registra el resultado
    // Muestra el registro en pantalla
    cout << "[" << obtenerFechaHora() << "] [" << jugador << "] [juego: MEM] [resultado: " << resultado << "] [puntuacion: " << aciertos << "]\n";
}

// Lógica principal para jugar dos jugadores alternando turnos
void Concentrese::dosJugadores() {
    string jugador1, jugador2;
    cout << "Nombre del jugador 1: ";
    cin >> jugador1;
    cout << "Nombre del jugador 2: ";
    cin >> jugador2;
    // Solicita el número de intentos máximos
    cout << "¿Cuántos intentos máximos desean? (recomendado 30): ";
    while (!(cin >> maxIntentos) || maxIntentos <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ingresa un número válido de intentos: ";
    }
    int puntos1 = 0, puntos2 = 0, turno = 0, intentos = 0;
    string resultado1, resultado2;
    // Bucle principal del juego para dos jugadores
    while (!todasDescubiertas() && intentos < maxIntentos) {
        mostrarTablero(); // Muestra el tablero
        string actual = (turno % 2 == 0) ? jugador1 : jugador2; // Alterna jugador
        int pos1, pos2;
        // Solicita la primera casilla
        cout << actual << ", elige la primera casilla: ";
        while (!(cin >> pos1) || pos1 < 1 || pos1 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Ingresa un número válido: ";
        }
        // Solicita la segunda casilla
        cout << actual << ", elige la segunda casilla: ";
        while (!(cin >> pos2) || pos2 < 1 || pos2 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Ingresa un número válido: ";
        }
        --pos1; --pos2; // Ajusta a índice base 0
        // Verifica que las posiciones sean válidas y no descubiertas
        if (pos1 == pos2 || descubiertas[pos1] || descubiertas[pos2]) {
            cout << "Posiciones inválidas. Intenta de nuevo.\n";
            continue;
        }
        // Muestra los símbolos seleccionados
        cout << "Descubres: " << simbolos[pos1] << " y " << simbolos[pos2] << endl;
        if (simbolos[pos1] == simbolos[pos2]) {
            cout << "¡Pareja encontrada!\n";
            descubiertas[pos1] = descubiertas[pos2] = true; // Marca como descubiertas
            if (turno % 2 == 0) puntos1++; else puntos2++; // Suma puntos al jugador actual
        } else {
            cout << "No son pareja.\n";
            turno++; // Cambia de turno solo si no acierta
        }
        intentos++;
    }
    // Muestra el puntaje final de ambos jugadores
    cout << "Puntaje final:\n";
    cout << jugador1 << ": " << puntos1 << " parejas\n";
    cout << jugador2 << ": " << puntos2 << " parejas\n";
    // Determina el resultado de cada jugador
    resultado1 = (puntos1 > puntos2) ? "G" : "P";
    resultado2 = (puntos2 > puntos1) ? "G" : "P";
    if (!todasDescubiertas()) {
        cout << "Se acabaron los intentos. ¡Nadie completó el tablero!\n";
        resultado1 = "P";
        resultado2 = "P";
    }
    // Registra los resultados de ambos jugadores
    registrarResultado(jugador1, resultado1, puntos1);
    registrarResultado(jugador2, resultado2, puntos2);
    // Muestra el registro en pantalla
    cout << "[" << obtenerFechaHora() << "] [" << jugador1 << "] [juego: MEM] [resultado: " << resultado1 << "] [puntuacion: " << puntos1 << "]\n";
    cout << "[" << obtenerFechaHora() << "] [" << jugador2 << "] [juego: MEM] [resultado: " << resultado2 << "] [puntuacion: " << puntos2 << "]\n";
}