
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

class BST {
private:
    NodoArbol* raiz;

    NodoArbol* insertarRec(NodoArbol* nodo, const Contacto& c) {
        if (!nodo) return new NodoArbol(c);
        if (c.nombre < nodo->dato.nombre)
            nodo->izq = insertarRec(nodo->izq, c);
        else
            nodo->der = insertarRec(nodo->der, c);
        return nodo;
    }
    void inordenRec(NodoArbol* nodo) {
        if (!nodo) return;
        inordenRec(nodo->izq);
        cout << nodo->dato.nombre << " | " << nodo->dato.telefono << " | " << nodo->dato.correo << "\n";
        inordenRec(nodo->der);
    }

    void preordenRec(NodoArbol* nodo) {
        if (!nodo) return;
        cout << nodo->dato.nombre << " | " << nodo->dato.telefono << " | " << nodo->dato.correo << "\n";
        preordenRec(nodo->izq);
        preordenRec(nodo->der);
    }

    void liberar(NodoArbol* nodo) {
        if (!nodo) return;
        liberar(nodo->izq);
        liberar(nodo->der);
        delete nodo;
    }
public:
    BST() { raiz = nullptr; }
    ~BST() { liberar(raiz); }

    void insertar(const Contacto& c) { raiz = insertarRec(raiz, c); }
    void limpiar() { liberar(raiz); raiz = nullptr; }

    void mostrarInorden() {
        if (!raiz) { cout << "Arbol vacío.\n"; return; }
        inordenRec(raiz);
    }

    void mostrarPreorden() {
        if (!raiz) { cout << "Arbol vacío.\n"; return; }
        preordenRec(raiz);
    }
};

int main()
{
   
}

