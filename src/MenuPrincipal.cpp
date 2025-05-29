#include <iostream>
#include <string>
using namespace std;

class Juego {
public:
    virtual void jugar() = 0;
    virtual ~Juego() {}
};

class Ahorcado : public Juego {
public:
    void jugar() override {
        cout << "Jugando Ahorcado..." << endl;
    }
};

class Concentrece : public Juego {
public:
    void jugar() override {
        cout << "Jugando Concentrece..." << endl;
    }
};

int main() {
    Juego* juego = nullptr;
    int opcion;
    cout << "1. Ahorcado\n2. Concentrece\nElige: ";
    cin >> opcion;

    if (opcion == 1)
        juego = new Ahorcado();
    else if (opcion == 2)
        juego = new Concentrece();

    if (juego) {
        juego->jugar();
        delete juego;
    }

    return 0;
}
