

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
        reconstruirArbol();
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

        Nodo* head = nullptr;
        Nodo* tail = nullptr;
        for (auto& c : contactos) {
            Nodo* node = new Nodo(c);
            if (!head) head = tail = node;
            else { tail->siguiente = node; tail = node; }
        }

        Nodo* curr = head;
        Nodo* prev = nullptr;
        bool eliminado = false;
        while (curr) {
            if (curr->dato.nombre == nombre) {
                if (prev) prev->siguiente = curr->siguiente;
                else head = curr->siguiente;
                historial.push("Eliminar: " + curr->dato.nombre);
                Nodo* borrar = curr;
                curr = curr->siguiente;
                delete borrar;
                eliminado = true;
            }
            else {
                prev = curr;
                curr = curr->siguiente;
            }
        }

        vector<Contacto> nuevo;
        curr = head;
        while (curr) {
            nuevo.push_back(curr->dato);
            Nodo* sig = curr->siguiente;
            delete curr;
            curr = sig;
        }
        contactos.swap(nuevo);
        if (eliminado) {
            reconstruirArbol();
            cout << "Contacto eliminado.\n";
        }
        else {
            cout << "No se encontró el contacto.\n";
        }
        return eliminado;
    }

    void mostrarHistorial() {
        if (historial.empty()) {
            cout << "Historial vacío.\n";
            return;
        }
        stack<string> copia = historial;
        cout << "\nHistorial (última operación primero):\n";
        while (!copia.empty()) {
            cout << "- " << copia.top() << "\n";
            copia.pop();
        }
    }

    void encolarPendiente(const Contacto& c) {
        pendientes.push(c);
        cout << "Pendiente agregado: " << c.nombre << "\n";
    }

    void transferirPendientes() {
        while (!pendientes.empty()) {
            Contacto c = pendientes.front();
            pendientes.pop();
            agregarContacto(c);
        }
    }

    void mostrarPendientes() {
        if (pendientes.empty()) {
            cout << "No hay contactos pendientes.\n";
            return;
        }
        queue<Contacto> copia = pendientes;
        while (!copia.empty()) {
            Contacto c = copia.front();
            copia.pop();
            cout << "- " << c.nombre << " | " << c.telefono << "\n";
        }
    }

    void reconstruirArbol() {
        arbol.limpiar();
        for (auto& c : contactos) arbol.insertar(c);
    }

    void mostrarArbolInorden() { arbol.mostrarInorden(); }
    void mostrarArbolPreorden() { arbol.mostrarPreorden(); }

    bool estaVacia() const { return contactos.empty(); }
};


string leerLinea() {
    string s;
    getline(cin, s);
    return s;
}


int main() {
    Agenda agenda;
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n===== GESTOR DE AGENDA =====\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Listar contactos\n";
        cout << "3. Buscar contacto\n";
        cout << "4. Eliminar contacto\n";
        cout << "5. Ver historial\n";
        cout << "6. Cola de pendientes\n";
        cout << "7. Arbol de contactos\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
        case 1: {
            string n, t, c;
            cout << "Nombre: "; getline(cin, n);
            cout << "Telefono: "; getline(cin, t);
            cout << "Correo: "; getline(cin, c);
            agenda.agregarContacto(Contacto(n, t, c));
            break;
        }
        case 2:
            agenda.listarContactos();
            break;
        case 3: {
            cout << "Buscar por nombre: ";
            string nombre; getline(cin, nombre);
            int pos = agenda.buscarBinariaPorNombre(nombre);
            if (pos == -1) cout << "No encontrado.\n";
            else cout << "Contacto encontrado en la posicion " << pos + 1 << "\n";
            break;
        }
        case 4: {
            cout << "Nombre del contacto a eliminar: ";
            string nombre; getline(cin, nombre);
            agenda.eliminarContacto(nombre);
            break;
        }
        case 5:
            agenda.mostrarHistorial();
            break;
        case 6: {
            int sub;
            cout << "\n1. Encolar contacto\n2. Ver pendientes\n3. Transferir pendientes\n";
            cout << "Seleccione: "; cin >> sub; cin.ignore();
            if (sub == 1) {
                string n, t, c;
                cout << "Nombre: "; getline(cin, n);
                cout << "Telefono: "; getline(cin, t);
                cout << "Correo: "; getline(cin, c);
                agenda.encolarPendiente(Contacto(n, t, c));
            }
            else if (sub == 2) {
                agenda.mostrarPendientes();
            }
            else if (sub == 3) {
                agenda.transferirPendientes();
            }
            break;
        }
        case 7: {
            int tipo;
            cout << "\n1. Inorden\n2. Preorden\nSeleccione: ";
            cin >> tipo; cin.ignore();
            if (tipo == 1) agenda.mostrarArbolInorden();
            else agenda.mostrarArbolPreorden();
            break;
        }
        case 8:
            salir = true;
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    }

    return 0;
}
