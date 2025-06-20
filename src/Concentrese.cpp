#include "Concentrese.h"   
#include <iostream>         
#include <fstream>          // Para manejo de archivos (registro y carga de símbolos)
#include <ctime>            // Para obtener la hora actual y semilla de aleatoriedad
#include <cstdlib>          // Para funciones rand() y srand()
#include <vector>           
#include <string>           
using namespace std;

// Función externa que devuelve la fecha y hora actual como string
extern string obtenerFechaHora();

// Constructor por defecto: inicializa un tablero 4x4 con 30 intentos
Concentrese::Concentrese() : filas(4), columnas(4), maxIntentos(30) {
    cargarSimbolos();
}

// Constructor alternativo: se comporta igual que el por defecto
Concentrese::Concentrese(bool /*contraConsola*/) : filas(4), columnas(4), maxIntentos(30) {
    cargarSimbolos();
}

// Carga los símbolos del archivo, los duplica para formar parejas, y los mezcla
void Concentrese::cargarSimbolos() {
    ifstream archivo("simbolos.txt"); // Abre el archivo que contiene los símbolos
    string simbolo;
    simbolos.clear();

    // Se leen los símbolos y se agregan dos veces al vector (para formar pares)
    while (archivo >> simbolo) {
        simbolos.push_back(simbolo);
        simbolos.push_back(simbolo);
        if ((int)simbolos.size() >= filas * columnas) break; // Limita a 16 elementos (4x4)
    }
    archivo.close();

    // Mezcla los símbolos usando el algoritmo de Fisher-Yates
    srand(time(0));
    for (int i = simbolos.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(simbolos[i], simbolos[j]);
    }

    // Inicializa el vector de casillas descubiertas en "false"
    descubiertas = vector<bool>(filas * columnas, false);
}

// Muestra el tablero actual en pantalla, con casillas numeradas o símbolos descubiertos
void Concentrese::mostrarTablero() {
    cout << "\nTablero:\n";
    for (int i = 0; i < filas * columnas; ++i) {
        if (descubiertas[i]) {
            cout << " " << simbolos[i] << " ";
        } else {
            if (i + 1 < 10) cout << " " << i + 1 << " ";
            else cout << i + 1 << " ";
        }

        if ((i + 1) % columnas == 0) cout << endl;
    }
}

// Revisa si todas las casillas están descubiertas (fin del juego)
bool Concentrese::todasDescubiertas() {
    for (bool estado : descubiertas) {
        if (!estado) return false;
    }
    return true;
}

// Registra el resultado de una partida en un archivo de texto
void Concentrese::registrarResultado(const string& jugador, const string& resultado, int puntuacion) {
    ofstream archivo("registro_partidas.txt", ios::app); // Abre en modo agregar
    archivo << "[" << obtenerFechaHora() << "] [" << jugador << "] [juego: MEM] [resultado: "
            << resultado << "] [puntuacion: " << puntuacion << "]\n";
    archivo.close();
}

// Lógica del juego en modo individual (1 jugador)
void Concentrese::jugar() {
    string jugador;
    cout << "Nombre del jugador: ";
    cin >> jugador;

    // Se pregunta cuántos intentos desea el jugador
    cout << "¿Cuántos intentos quieres? (recomendado: 30): ";
    while (!(cin >> maxIntentos) || maxIntentos <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Por favor, ingresa un número válido: ";
    }

    int intentos = 0, aciertos = 0;
    string resultado;

    // Ciclo principal del juego
    while (!todasDescubiertas() && intentos < maxIntentos) {
        mostrarTablero();

        int pos1, pos2;
        // Primera selección
        cout << jugador << ", elige la primera casilla: ";
        while (!(cin >> pos1) || pos1 < 1 || pos1 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Intenta otra: ";
        }

        // Segunda selección
        cout << jugador << ", elige la segunda casilla: ";
        while (!(cin >> pos2) || pos2 < 1 || pos2 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Intenta otra: ";
        }

        pos1--; pos2--; // Ajuste a índice base 0

        // Validación de jugadas
        if (pos1 == pos2 || descubiertas[pos1] || descubiertas[pos2]) {
            cout << "Casillas no válidas. Repite tu intento.\n";
            continue;
        }

        cout << "Descubres: " << simbolos[pos1] << " y " << simbolos[pos2] << endl;

        // Verifica si hay coincidencia
        if (simbolos[pos1] == simbolos[pos2]) {
            cout << "¡Encontraste una pareja!\n";
            descubiertas[pos1] = descubiertas[pos2] = true;
            aciertos++;
        } else {
            cout << "No coinciden.\n";
        }

        intentos++;
    }

    // Fin de la partida: gana o pierde según descubiertos
    if (todasDescubiertas()) {
        cout << "¡Bien hecho " << jugador << "! Ganaste en " << intentos << " intentos.\n";
        resultado = "G";
    } else {
        cout << "Se acabaron los intentos. No lograste completar el tablero.\n";
        resultado = "P";
    }

    registrarResultado(jugador, resultado, aciertos);

    cout << "[" << obtenerFechaHora() << "] [" << jugador << "] [juego: MEM] [resultado: "
         << resultado << "] [puntuacion: " << aciertos << "]\n";
}

// Lógica para modo dos jugadores (turnos alternos)
void Concentrese::dosJugadores() {
    string jugador1, jugador2;
    cout << "Nombre del jugador 1: ";
    cin >> jugador1;
    cout << "Nombre del jugador 2: ";
    cin >> jugador2;

    // Pregunta cuántos intentos usarán en total
    cout << "¿Cuántos intentos desean en total? (recomendado: 30): ";
    while (!(cin >> maxIntentos) || maxIntentos <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ingresa un número válido de intentos: ";
    }

    int puntos1 = 0, puntos2 = 0, turno = 0, intentos = 0;
    string resultado1, resultado2;

    // Ciclo principal del juego por turnos
    while (!todasDescubiertas() && intentos < maxIntentos) {
        mostrarTablero();
        string actual = (turno % 2 == 0) ? jugador1 : jugador2;

        int pos1, pos2;
        cout << actual << ", elige la primera casilla: ";
        while (!(cin >> pos1) || pos1 < 1 || pos1 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Intenta otra: ";
        }

        cout << actual << ", elige la segunda casilla: ";
        while (!(cin >> pos2) || pos2 < 1 || pos2 > filas * columnas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Posición inválida. Intenta otra: ";
        }

        pos1--; pos2--;

        if (pos1 == pos2 || descubiertas[pos1] || descubiertas[pos2]) {
            cout << "Casillas inválidas. Pierdes el turno.\n";
            continue;
        }

        cout << "Descubres: " << simbolos[pos1] << " y " << simbolos[pos2] << endl;

        if (simbolos[pos1] == simbolos[pos2]) {
            cout << "¡Bien! Encontraste una pareja.\n";
            descubiertas[pos1] = descubiertas[pos2] = true;
            if (turno % 2 == 0) puntos1++;
            else puntos2++;
        } else {
            cout << "No es pareja.\n";
            turno++;  // Solo cambia si falló
        }

        intentos++;
    }

    // Muestra el resultado final de la partida
    cout << "\nPuntaje final:\n";
    cout << jugador1 << ": " << puntos1 << " parejas\n";
    cout << jugador2 << ": " << puntos2 << " parejas\n";

    if (!todasDescubiertas()) {
        cout << "Nadie completó el tablero. Empate forzado.\n";
        resultado1 = resultado2 = "P";
    } else {
        resultado1 = (puntos1 > puntos2) ? "G" : "P";
        resultado2 = (puntos2 > puntos1) ? "G" : "P";
    }

    registrarResultado(jugador1, resultado1, puntos1);
    registrarResultado(jugador2, resultado2, puntos2);

    cout << "[" << obtenerFechaHora() << "] [" << jugador1 << "] [juego: MEM] [resultado: "
         << resultado1 << "] [puntuacion: " << puntos1 << "]\n";
    cout << "[" << obtenerFechaHora() << "] [" << jugador2 << "] [juego: MEM] [resultado: "
         << resultado2 << "] [puntuacion: " << puntos2 << "]\n";
}
