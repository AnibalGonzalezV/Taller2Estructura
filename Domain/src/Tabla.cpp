#include "../../Domain/include/Tabla.h"
#include <iostream>

using namespace std;

template class Tabla<string, int>;


template <typename C, typename V>
Tabla<C, V>::Tabla(unsigned int cap) : capacidad(cap) {
    tabla = new Lista<C, V>[capacidad];
}

template <typename C, typename V>
Tabla<C, V>::~Tabla() {
    delete[] tabla;
}

template <typename C, typename V>
unsigned int Tabla<C, V>::calcularHash(const C& clave) const {
    unsigned int hash = 0;
    for (char c : clave) {
        hash += c;
    }
    return hash % capacidad;
}

template <typename C, typename V>
void Tabla<C, V>::insertar(const C& clave, const V& valor) {
    unsigned int indice = calcularHash(clave);
    if (!tabla[indice].actualizar(clave, valor)) {
        tabla[indice].insertar(clave, valor);
    }
}

template <typename C, typename V>
bool Tabla<C, V>::obtener(const C& clave, V& valor) const {
    unsigned int indice = calcularHash(clave);
    return tabla[indice].obtener(clave, valor);
}