#include "Concentrese.h" // Incluye la declaración de la clase Concentrese
#include <iostream>      // Para entrada/salida estándar (cout, cin)
#include <fstream>       // Para manejo de archivos (ifstream, ofstream)
#include <ctime>         // Para obtener la fecha y hora actual
#include <cstdlib>       // Para funciones de aleatoriedad (rand, srand)
#include <vector>        // Para usar el contenedor vector
using namespace std;

// Función para obtener la fecha y hora actual en formato string
string obtenerFechaHora() {
    time_t now = time(0);                // Obtiene el tiempo actual
    tm* ltm = localtime(&now);           // Convierte a estructura de tiempo local
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm); // Formatea la fecha/hora
    return string(buffer);               // Retorna como string
}

// Constructor por defecto: inicializa el tablero de 4x4 y carga los símbolos
Concentrese::Concentrese() : filas(4), columnas(4) {
    cargarSimbolos();
}

// Constructor alternativo (no usado aquí, pero permite jugar contra la consola)
Concentrese::Concentrese(bool contraConsola) : filas(4), columnas(4) {
    cargarSimbolos();
}

// Carga los símbolos desde un archivo y los mezcla aleatoriamente
void Concentrese::cargarSimbolos() {
    ifstream archivo("simbolos.txt"); // Abre el archivo de símbolos
    string simbolo;
    simbolos.clear();
    // Lee símbolos y los agrega dos veces (para formar pares)
    while (archivo >> simbolo) {
        simbolos.push_back(simbolo);
        simbolos.push_back(simbolo);
        if (simbolos.size() >= filas * columnas) break; // Solo los necesarios
    }
    archivo.close();
    // Mezcla los símbolos usando el algoritmo de Fisher-Yates
    srand(time(0));
    for (int i = simbolos.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        string temp = simbolos[i];
        simbolos[i] = simbolos[j];
        simbolos[j] = temp;
    }
    // Inicializa el vector de descubiertas en falso
    descubiertas = vector<bool>(filas * columnas, false);
}

// Muestra el tablero en consola, mostrando símbolos descubiertos o el número de casilla
void Concentrese::mostrarTablero() {
    cout << "\nTablero:\n";
    for (int i = 0; i < filas * columnas; ++i) {
        if (descubiertas[i])
            cout << " " << simbolos[i] << " ";
        else {
            if (i + 1 < 10)
                cout << " " << i + 1 << " ";
            else
                cout << i + 1 << " ";
        }
        if ((i + 1) % columnas == 0) cout << endl;
    }
}

// Verifica si todas las casillas han sido descubiertas
bool Concentrese::todasDescubiertas() {
    for (size_t i = 0; i < descubiertas.size(); ++i)
        if (!descubiertas[i]) return false;
    return true;
}

// Registra el resultado de la partida en un archivo de texto
void Concentrese::registrarResultado(const string& jugador, const string& resultado, int puntuacion) {
    ofstream archivo("registro_partidas.txt", ios::app); // Abre en modo append
    archivo << "[" << obtenerFechaHora() << "] [" << jugador << "] [juego: MEM] [resultado: " << resultado << "] [puntuacion: " << puntuacion << "]\n";
    archivo.close();
}

// Lógica del juego para un solo jugador
void Concentrese::jugar() {
    string jugador;
    cout << "Nombre del jugador: ";
    cin >> jugador;
    int intentos = 0, aciertos = 0;
    while (!todasDescubiertas()) {
        mostrarTablero();
        int pos1, pos2;
        cout << jugador << ", elige la primera casilla: ";
        cin >> pos1;
        cout << jugador << ", elige la segunda casilla: ";
        cin >> pos2;
        --pos1; --pos2; // Ajusta a índice base 0
        // Valida las posiciones elegidas
        if (pos1 == pos2 || pos1 < 0 || pos2 < 0 || pos1 >= filas * columnas || pos2 >= filas * columnas || descubiertas[pos1] || descubiertas[pos2]) {
            cout << "Posiciones inválidas. Intenta de nuevo.\n";
            continue;
        }
        cout << "Descubres: " << simbolos[pos1] << " y " << simbolos[pos2] << endl;
        if (simbolos[pos1] == simbolos[pos2]) {
            cout << "¡Pareja encontrada!\n";
            descubiertas[pos1] = descubiertas[pos2] = true;
            aciertos++;
        } else {
            cout << "No son pareja.\n";
        }
        intentos++;
    }
    cout << "¡Felicidades " << jugador << "! Terminaste en " << intentos << " turnos.\n";
    registrarResultado(jugador, "G", aciertos);
}

// Lógica del juego para dos jugadores
void Concentrese::jugarDosJugadores() {
    string jugador1, jugador2;
    cout << "Nombre del jugador 1: ";
    cin >> jugador1;
    cout << "Nombre del jugador 2: ";
    cin >> jugador2;
    int puntos1 = 0, puntos2 = 0, turno = 0;
    while (!todasDescubiertas()) {
        mostrarTablero();
        string actual = (turno % 2 == 0) ? jugador1 : jugador2;
        cout << actual << ", elige la primera casilla: ";
        int pos1, pos2;
        cin >> pos1;
        cout << actual << ", elige la segunda casilla: ";
        cin >> pos2;
        --pos1; --pos2;
        // Valida las posiciones elegidas
        if (pos1 == pos2 || pos1 < 0 || pos2 < 0 || pos1 >= filas * columnas || pos2 >= filas * columnas || descubiertas[pos1] || descubiertas[pos2]) {
            cout << "Posiciones inválidas. Intenta de nuevo.\n";
            continue;
        }
        cout << "Descubres: " << simbolos[pos1] << " y " << simbolos[pos2] << endl;
        if (simbolos[pos1] == simbolos[pos2]) {
            cout << "¡Pareja encontrada!\n";
            descubiertas[pos1] = descubiertas[pos2] = true;
            if (turno % 2 == 0) puntos1++; else puntos2++;
        } else {
            cout << "No son pareja.\n";
            turno++;
        }
    }
    cout << "Puntaje final:\n";
    cout << jugador1 << ": " << puntos1 << " parejas\n";
    cout << jugador2 << ": " << puntos2 << " parejas\n";
    string resultado1 = (puntos1 > puntos2) ? "G" : "P";
    string resultado2 = (puntos2 > puntos1) ? "G" : "P";
    registrarResultado(jugador1, resultado1, puntos1);
    registrarResultado(jugador2, resultado2, puntos2);
}