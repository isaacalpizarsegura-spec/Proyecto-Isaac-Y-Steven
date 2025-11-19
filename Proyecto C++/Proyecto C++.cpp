
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



class Agenda {
private:
    vector<Contacto> contactos;
    stack<string> historial;
    queue<Contacto> pendientes;
    BST arbol;

public:
    void agregarContacto(const Contacto& c) {
        contactos.push_back(c);
        historial.push("Agregar: " + c.nombre);
        arbol.insertar(c.nombre);   // ← CORREGIDO
        cout << "Contacto agregado: " << c.nombre << "\n";
    }

    void listarContactos() {
        if (contactos.empty()) {
            cout << "No hay contactos.\n";
            return;
        }
        for (size_t i = 0; i < contactos.size(); i++) {
            cout << i + 1 << ". " << contactos[i].nombre << " | "
                << contactos[i].telefono << " | " << contactos[i].correo << "\n";
        }
    }

    void ordenarPorNombre() {
        sort(contactos.begin(), contactos.end(),
            [](Contacto a, Contacto b) { return a.nombre < b.nombre; });
    }

    void ordenarPorTelefono() {
        sort(contactos.begin(), contactos.end(),
            [](Contacto a, Contacto b) { return a.telefono < b.telefono; });
    }

    int buscarSecuencialPorNombre(const string& nombre) {
        for (size_t i = 0; i < contactos.size(); i++)
            if (contactos[i].nombre == nombre) return (int)i;
        return -1;
    }

    int buscarBinariaPorNombre(const string& nombre) {
        ordenarPorNombre();
        int izq = 0, der = (int)contactos.size() - 1;
        while (izq <= der) {
            int mid = (izq + der) / 2;
            if (contactos[mid].nombre == nombre) return mid;
            if (contactos[mid].nombre < nombre) izq = mid + 1;
            else der = mid - 1;
        }
        return -1;
    }

    bool eliminarContacto(const string& nombre) {
        if (contactos.empty()) return false;

        for (size_t i = 0; i < contactos.size(); i++) {
            if (contactos[i].nombre == nombre) {
                historial.push("Eliminar: " + contactos[i].nombre);
                contactos.erase(contactos.begin() + i);
                cout << "Contacto eliminado: " << nombre << "\n";
                return true;
            }
        }

        cout << "No se encontró el contacto: " << nombre << "\n";
        return false;
    }
};

int main()
{
   
}

