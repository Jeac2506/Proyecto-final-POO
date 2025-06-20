#include "Ahorcado.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Estructura para guardar el resultado de una partida de ahorcado
struct ResultadoAhorcado {
    string fecha;      // Fecha y hora de la partida
    string jugador;    // Nombre del jugador
    string juego;      // Código del juego (AH)
    string resultado;  // "G" para ganar, "P" para perder
    int puntos;        // Puntos obtenidos
};

// Declaración de función externa para obtener la fecha y hora actual
extern string obtenerFechaHora();

// Arreglo con las partes del cuerpo del ahorcado
const string partesCuerpo[] = {
    "Cabeza",
    "Tronco",
    "Brazo Izquierdo",
    "Brazo Derecho",
    "Pierna Izquierda",
    "Pierna Derecha"
};
const int MaxIntentos = 6; // Número máximo de intentos permitidos

// Función para registrar el resultado de una partida en un archivo
void registrarResultadoAhorcado(const ResultadoAhorcado& res) {
    ofstream archivo("registro_partidas.txt", ios::app);
    archivo << "[" << res.fecha << "] [" << res.jugador << "] [juego: " << res.juego << "] [resultado: " << res.resultado << "] [puntuacion: " << res.puntos << "]\n";
    archivo.close();
}

// Constructor de la clase Ahorcado
Ahorcado::Ahorcado(bool contraConsola){
    if (contraConsola){
        // Si se juega contra la consola, se elige una palabra aleatoria de un archivo
        ifstream archivo("palabras.txt");
        vector<string> palabras;
        string palabra;
        // Se leen todas las palabras del archivo usando un bucle while
        while (archivo >> palabra) {
            palabras.push_back(palabra);
        }
        archivo.close();
        srand(time(0)); // Inicializa la semilla para números aleatorios
        palabraSecreta = palabras[rand() % palabras.size()]; // Selecciona una palabra al azar
    }
    else {
        // Si no es contra la consola, el usuario ingresa la palabra secreta
        cout << "Ingrese la palabra secreta: ";
        cin >> palabraSecreta;
        cout << string(50, '\n'); // Limpia la pantalla
    }
    palabraAdivinada = string(palabraSecreta.size(), '_'); // Inicializa la palabra adivinada con guiones bajos
    letrasUsadas.clear(); // Limpia las letras usadas
    intentos = MaxIntentos; // Reinicia los intentos
}

// Constructor por defecto
Ahorcado::Ahorcado() {}


// Método para jugar una partida de ahorcado (modo consola)
void Ahorcado::jugar()
{
    letrasUsadas.clear();
    palabraAdivinada = string(palabraSecreta.size(), '_');
    intentos = MaxIntentos;
    char letra;
    // Bucle principal del juego: se repite mientras haya intentos y no se adivine la palabra
    while (intentos > 0 && palabraAdivinada != palabraSecreta)
    {
        mostrarEstado(); // Muestra el estado actual del juego
        cout << "Ingresa una letra: ";
        cin >> letra;

        if (letraYaUsada(letra))
        {
            cout << "Ya usaste esa letra.\n";
            continue; // Si la letra ya fue usada, se salta a la siguiente iteración
        }

        letrasUsadas.push_back(letra);
        bool acierto = false;

        // Bucle for para comprobar si la letra está en la palabra secreta
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
            intentos--; // Se reduce el número de intentos si no acertó
        }
    }

    string jugador;
    cout << "Ingresa tu nombre para el registro: ";
    cin >> jugador;

    // Se registra el resultado de la partida
    ResultadoAhorcado res;
    res.fecha = obtenerFechaHora();
    res.jugador = jugador;
    res.juego = "AH";
    if (palabraAdivinada == palabraSecreta) {
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << endl;
        res.resultado = "G";
    } else {
        cout << "Perdiste :c la palabra era: " << palabraSecreta << endl;
        res.resultado = "P";
    }
    res.puntos = intentos;
    registrarResultadoAhorcado(res);
    cout << "[" << res.fecha << "] [" << res.jugador << "] [juego: AH] [resultado: " << res.resultado << "] [puntuacion: " << res.puntos << "]\n";
}

// Método para jugar con otro usuario (devuelve true si gana, false si pierde)
bool Ahorcado::jugarConUsuario(const string& nombreAdivina){
    letrasUsadas.clear();
    palabraAdivinada = string(palabraSecreta.size(), '_');
    intentos = MaxIntentos;
    char letra;
    // Bucle principal del juego
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

        // Bucle for para comprobar si la letra está en la palabra secreta
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

    // Solo devuelve el resultado, no imprime ni registra
    return palabraAdivinada == palabraSecreta;
}

// Método para jugar en modo dos jugadores
void Ahorcado::dosJugadores()
{
    string nombreJugador1, nombreJugador2;
    cout << "Ingrese el nombre del jugador 1: ";
    cin >> nombreJugador1;
    cout << "Ingrese el nombre del jugador 2: ";
    cin >> nombreJugador2;
    
    int rondas;
    // Bucle do-while para validar el número de rondas
    do{
        cout << "¿Cuántas rondas quieren jugar? (1-5): ";
        cin >> rondas;
    }while (rondas < 1 || rondas > 5);

    int puntos1 = 0, puntos2 = 0;
    vector<ResultadoAhorcado> resultados;

    // Bucle for para jugar varias rondas
    for (int ronda = 1; ronda <= rondas; ++ronda){
        cout << "\n--- Ronda " << ronda <<" ---\n";

        // Jugador 1 pone palabra, jugador 2 adivina
        cout << nombreJugador1 << ", ingrese la palabra secreta para que " << nombreJugador2 << " la adivine.\n";
        Ahorcado* ahorcado1 = new Ahorcado(false);
        bool adivino2 = ahorcado1->jugarConUsuario(nombreJugador2);
        int puntosRonda2 = adivino2 ? 10 : 0;
        puntos2 += puntosRonda2;
        ResultadoAhorcado res2;
        res2.fecha = obtenerFechaHora();
        res2.jugador = nombreJugador2;
        res2.juego = "AH";
        res2.resultado = adivino2 ? "G" : "P";
        res2.puntos = puntosRonda2;
        resultados.push_back(res2);
        delete ahorcado1;

        // Jugador 2 pone palabra, jugador 1 adivina
        cout << nombreJugador2 << ", ingrese la palabra secreta para que " << nombreJugador1 << " la adivine.\n";
        Ahorcado* ahorcado2 = new Ahorcado(false);
        bool adivino1 = ahorcado2->jugarConUsuario(nombreJugador1);
        int puntosRonda1 = adivino1 ? 10 : 0;
        puntos1 += puntosRonda1;
        ResultadoAhorcado res1;
        res1.fecha = obtenerFechaHora();
        res1.jugador = nombreJugador1;
        res1.juego = "AH";
        res1.resultado = adivino1 ? "G" : "P";
        res1.puntos = puntosRonda1;
        resultados.push_back(res1);
        delete ahorcado2;
    }

    // Muestra los resultados finales y registra
    cout << "\n=== RESULTADOS DE TODAS LAS RONDAS ===\n";
    for (const auto& res : resultados) {
        registrarResultadoAhorcado(res);
        cout << "[" << res.fecha << "] [" << res.jugador << "] [juego: AH] [resultado: " << res.resultado << "] [puntuacion: " << res.puntos << "]\n";
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

// Método para mostrar el estado actual del juego
void Ahorcado::mostrarEstado()
{
    cout << "\nPalabra: ";
    // Bucle for-each para mostrar la palabra adivinada hasta el momento
    for (char c : palabraAdivinada)
        cout << c << ' ';
    cout << "\nLetras usadas: ";
    // Bucle for-each para mostrar las letras ya usadas
    for (char l : letrasUsadas)
        cout << l << ' ';
    cout << "\nIntentos restantes: " << intentos << endl;
}

// Método para verificar si una letra ya fue usada
bool Ahorcado::letraYaUsada(char letra)
{
    // Bucle for-each para buscar la letra en el vector de letras usadas
    for (char l : letrasUsadas)
    {
        if (l == letra) return true;
    }
    return false;
}