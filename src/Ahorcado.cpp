#include "Ahorcado.h"     
#include <iostream>       
#include <cstdlib>        // Para rand() y srand()
#include <ctime>          // Para obtener la hora actual (semilla de aleatoriedad)
#include <fstream>        
#include <vector>         
#include <string>         
using namespace std;

// el ran se usa para generar números aleatorios
// y srand se usa para generar números aleatorios basados en esa semilla

// Estructura que guarda los datos de una partida jugada
struct ResultadoAhorcado {
    string fecha;
    string jugador;
    string juego;
    string resultado;
    int puntos;
};

// Declaración de función externa que devuelve la fecha y hora actual como string
extern string obtenerFechaHora();

// Arreglo con las partes del cuerpo del personaje del ahorcado
const string partesCuerpo[] = {
    "Cabeza", "Tronco", "Brazo Izquierdo", "Brazo Derecho", "Pierna Izquierda", "Pierna Derecha"
};

const int MaxIntentos = 6; // Número máximo de intentos permitidos

// Guarda el resultado de una partida en el archivo de texto
void registrarResultadoAhorcado(const ResultadoAhorcado& res) {
    ofstream archivo("registro_partidas.txt", ios::app); // Abre archivo en modo agregar
    archivo << "[" << res.fecha << "] [" << res.jugador << "] [juego: " << res.juego
            << "] [resultado: " << res.resultado << "] [puntuacion: " << res.puntos << "]\n";
    archivo.close();
}

// Constructor que recibe un booleano para jugar contra la consola o contra otro jugador
Ahorcado::Ahorcado(bool contraConsola) {
    if (contraConsola) {
        // Si se juega contra la consola, se carga una palabra aleatoria desde archivo
        ifstream archivo("palabras.txt");
        vector<string> palabras;
        string palabra;

        while (archivo >> palabra) {
            // Convertir cada palabra a minúsculas antes de guardarla
            for (char &c : palabra) {
                c = tolower(c);
            }
            palabras.push_back(palabra);
        }
        archivo.close();

        srand(time(0)); // Inicializa la semilla aleatoria con la hora actual
        palabraSecreta = palabras[rand() % palabras.size()];
    } else {
        // Si es entre jugadores, uno de ellos ingresa la palabra secreta
        cout << "Ingrese la palabra secreta: ";
        cin >> palabraSecreta;
        // Convertir palabra ingresada a minúsculas
        for (char &c : palabraSecreta) {
            c = tolower(c);
        }
        cout << string(50, '\n'); // Limpia la pantalla para que el otro no vea
    }

    palabraAdivinada = string(palabraSecreta.size(), '_');
    letrasUsadas.clear();
    intentos = MaxIntentos;
}

// Constructor por defecto (puede usarse para pruebas)
Ahorcado::Ahorcado() {}

// Modo de juego individual (contra la consola o jugador oculto)
void Ahorcado::jugar() {
    letrasUsadas.clear();
    palabraAdivinada = string(palabraSecreta.size(), '_');
    intentos = MaxIntentos;
    char letra;

    while (intentos > 0 && palabraAdivinada != palabraSecreta)
    {
        mostrarEstado(); // Muestra el estado actual del juego
        
        string entrada;
        char letra;
        
        cout << "Ingresa una letra: ";
        cin >> entrada;

        if (entrada.length() != 1 || !isalpha(entrada[0])) {
            cout << "Error: Solo se puede ingresar UNA letra válida. Intenta de nuevo.\n";
            continue;
        }

        letra = entrada[0];

        if (letraYaUsada(letra)) {
            cout << "Ya usaste esa letra.\n";
            continue;
        }

        letrasUsadas.push_back(letra);
        bool acierto = false;

        for (size_t i = 0; i < palabraSecreta.size(); i++) {
            if (palabraSecreta[i] == letra) {
                palabraAdivinada[i] = letra;
                acierto = true;
            }
        }

        if (!acierto) {
            int parte = MaxIntentos - intentos;
            if (parte < MaxIntentos)
                cout << "¡Fallaste! : " << partesCuerpo[parte] << endl;
            intentos--;
    }
    }

    // Solicita el nombre del jugador para guardar el resultado
    string nombre;
    cout << "Escribe tu nombre para el registro: ";
    cin >> nombre;

    ResultadoAhorcado res;
    res.fecha = obtenerFechaHora();
    res.jugador = nombre;
    res.juego = "AH";
    res.resultado = (palabraAdivinada == palabraSecreta) ? "G" : "P";
    res.puntos = intentos;

    if (res.resultado == "G") {
        cout << "¡Ganaste! La palabra era: " << palabraSecreta << endl;
    } else {
        cout << "Perdiste :( La palabra era: " << palabraSecreta << endl;
    }

    registrarResultadoAhorcado(res);

    // Muestra el resultado por consola
    cout << "[" << res.fecha << "] [" << res.jugador << "] [juego: AH] [resultado: "
         << res.resultado << "] [puntuacion: " << res.puntos << "]\n";
}

// Modo de juego donde un jugador adivina la palabra que ingresó otro
bool Ahorcado::jugarConUsuario(const string& nombreAdivina) {
    letrasUsadas.clear();
    palabraAdivinada = string(palabraSecreta.size(), '_');
    intentos = MaxIntentos;
    char letra;

    while (intentos > 0 && palabraAdivinada != palabraSecreta) {
        mostrarEstado();
        cout << nombreAdivina << ", escribe una letra: ";
        cin >> letra;

        // Validar entrada
        if (!isalpha(letra)) {
            cout << "Por favor ingresa solo letras del alfabeto.\n";
            continue;
        }
        letra = tolower(letra); // Convertir a minúscula

        if (letraYaUsada(letra)) {
            cout << "Esa ya la usaste.\n";
            continue;
        }

        letrasUsadas.push_back(letra);
        bool acierto = false;

        for (size_t i = 0; i < palabraSecreta.size(); i++) {
            if (palabraSecreta[i] == letra) {
                palabraAdivinada[i] = letra;
                acierto = true;
            }
        }

        if (!acierto) {
            int parte = MaxIntentos - intentos;
            if (parte < MaxIntentos)
                cout << "Fallaste: " << partesCuerpo[parte] << endl;
            intentos--;
        }
    }

    // Retorna si ganó o no, sin registrar aún
    return palabraAdivinada == palabraSecreta;
}

// Modo para jugar entre dos personas en varias rondas
void Ahorcado::dosJugadores() {
    string nombre1, nombre2;
    cout << "Nombre del jugador 1: ";
    cin >> nombre1;
    cout << "Nombre del jugador 2: ";
    cin >> nombre2;

    int rondas;
    do {
        cout << "¿Cuántas rondas quieren jugar? (1-5): ";
        cin >> rondas;
    } while (rondas < 1 || rondas > 5);

    int puntos1 = 0, puntos2 = 0;
    vector<ResultadoAhorcado> resultados;

    for (int ronda = 1; ronda <= rondas; ++ronda) {
        cout << "\nRonda " << ronda << ":\n";

        // Turno jugador 2 adivina
        cout << nombre1 << " escribe la palabra para que " << nombre2 << " adivine.\n";
        Ahorcado* juego1 = new Ahorcado(false);
        bool adivino2 = juego1->jugarConUsuario(nombre2);
        delete juego1;

        ResultadoAhorcado res2;
        res2.fecha = obtenerFechaHora();
        res2.jugador = nombre2;
        res2.juego = "AH";
        res2.resultado = adivino2 ? "G" : "P";
        res2.puntos = adivino2 ? 10 : 0;
        puntos2 += res2.puntos;
        resultados.push_back(res2);

        // Turno jugador 1 adivina
        cout << nombre2 << " escribe la palabra para que " << nombre1 << " adivine.\n";
        Ahorcado* juego2 = new Ahorcado(false);
        bool adivino1 = juego2->jugarConUsuario(nombre1);
        delete juego2;

        ResultadoAhorcado res1;
        res1.fecha = obtenerFechaHora();
        res1.jugador = nombre1;
        res1.juego = "AH";
        res1.resultado = adivino1 ? "G" : "P";
        res1.puntos = adivino1 ? 10 : 0;
        puntos1 += res1.puntos;
        resultados.push_back(res1);
    }

    // Mostrar resumen y registrar
    cout << "\n=== RESULTADOS ===\n";
    for (const auto& res : resultados) {
        registrarResultadoAhorcado(res);
        cout << "[" << res.fecha << "] [" << res.jugador << "] [juego: AH] [resultado: "
             << res.resultado << "] [puntos: " << res.puntos << "]\n";
    }

    cout << "\nPuntaje Final:\n";
    cout << nombre1 << ": " << puntos1 << " puntos\n";
    cout << nombre2 << ": " << puntos2 << " puntos\n";

    if (puntos1 > puntos2)
        cout << nombre1 << " gana la partida!\n";
    else if (puntos2 > puntos1)
        cout << nombre2 << " gana la partida!\n";
    else
        cout << "Empate!\n";
}

// Muestra el estado actual de la palabra adivinada, letras usadas e intentos restantes
void Ahorcado::mostrarEstado() {
    cout << "\nPalabra: ";
    for (char c : palabraAdivinada)
        cout << c << ' ';
    cout << "\nLetras usadas: ";
    for (char l : letrasUsadas)
        cout << l << ' ';
    cout << "\nIntentos restantes: " << intentos << endl;
}

// Verifica si una letra ya fue utilizada previamente
bool Ahorcado::letraYaUsada(char letra) {
    for (char l : letrasUsadas) {
        if (l == letra) return true;
    }
    return false;
}
