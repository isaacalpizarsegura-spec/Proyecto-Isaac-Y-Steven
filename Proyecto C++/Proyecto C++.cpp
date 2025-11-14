
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <limits>


using namespace std;


class Contacto {
public:
    string nombre;
    string telefono;
    string correo;

    Contacto() {}
    Contacto(string n, string t, string c) {
        nombre = n;
        telefono = t;
        correo = c;
    }
};
struct Nodo {
    Contacto dato;
    Nodo* siguiente;
    Nodo(const Contacto& c) : dato(c), siguiente(nullptr) {}
};


struct NodoArbol {
    Contacto dato;
    NodoArbol* izq;
    NodoArbol* der;
    NodoArbol(const Contacto& c) : dato(c), izq(nullptr), der(nullptr) {}
};

int main()
{
    std::cout << !\n";
}

