#include "Concentrese.h"
#include <iostream>
#include <vector>
#include <string>
#include "Juego.h"
#include <fstream> // necesario para std::ifstream
#include <cstdlib> // esta libreria sirve para usar rand() y srand()
// el rand() genera un numero aleatorio y srand() inicializa el generador de numeros aleatorios
#include <ctime> // esta libreria sirve para usar time() para inicializar srand() con el tiempo actual


using namespace std;

string obtenerFechaHora(){
    time_t now = time(0);
    tm*ltm = localtime(&now); // esto se hace para obtener la fecha y hora actual
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

Concentrese::Concentrese()  : filas(4), columnas(4) // Inicializa el tablero a 4x4
{
    cargarSimbolos();
}
Concentrese::Concentrese(bool contraConsola) : filas(4), columnas(4) // Inicializa el tablero a 4x4
{
    cargarSimbolos();
}

void Concentrese::cargarSimbolos()
{
    ifstream archivo("simbolos.txt");
    string simbolo;
    simbolos.clear();
    while (archivo >> simbolo) // esto es para poder leer los simbolos del archivo
    {
        simbolos.push_back(simbolo);
        simbolos.push_back(simbolo); // Agrega el mismo simbolo dos veces para que haya pares
        if (simbolos.size() >= filas * columnas)
            break;
    }
    archivo.close();

    // Mezcla los simbolos aleatoriamente
    srand(time(0));
    for (int i = simbolos.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        string temp = simbolos[i]; // el string temp es una variable temporal para poder intercambiar los simbolos
        simbolos[i] = simbolos[j]; // aqui se intercambian los simbolos
        simbolos[j] = temp; // se iguala a temp para completar el intercambio
    }
    descubiertas = vector<bool>(filas * columnas, false);
void Concentrese::mostrarTablero()
{
    cout << "Tablero" << endl;
    for (int i = 0; i < filas * columnas; ++i) {
        if (descubiertas[i])
            cout << " " << simbolos[i] << " ";
        else {
            if (i + 1 < 10)
                cout << " " << i + 1 << " ";
            else
                cout << i + 1 << " ";
        }
        if ((i + 1) % columnas == 0)
            cout << endl; // Esto es para que se muestre el tablero en filas y columnas
    }
}

bool Concentrese::todasDescubiertas()
{
    for (size_t i = 0; i < descubiertas,size(); ++i)
        if(!descubiertas[i] return false;
    return true;)
}

void Concentrese::registrarResultado(const string& jugador, const strign& resultado, int puntos){
    ofstream archivo("RegistroPartidas.txt", ios:: app);
    archivo << "[" << obtenerFechaHora() << "] [" << jugador << "] [juego: Conc] [resultado: "<< resultado << "] [Puntuacion: "]<< puntuacion << "]\n";
    arcchivo.close();
}
void Concentrese::jugar(){
    string jugador;
    cout << "Nombre del jugador: ";
    cin>> jugador;
    int intentos = 0, aciertos = 0;
    while (!todasDescubiertas()){
        mostrarTablero();
        int pos1, pos2;
        cout<< jugador << ", eliga su primera casilla:  ";
        cin >> pos1;
        cout << jugador << ", eliga su segunda casilla: ";
        cin>> pos2;
        --pos1, --pos2;

        if (pos1 == pos2 || pos < 0 || pos2 < 0 || pos1 >= filas * columnas || pos2 >= filas * columnas || descubiertas [pos1] || descubiertas[pos2]){
            
        }
    }
}