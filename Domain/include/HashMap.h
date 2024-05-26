#pragma once
#include "Tabla.h"

template<typename C, typename V>
class HashMap {
private:
    Tabla<C, V> tabla;
    unsigned int tamanio;

public:
    HashMap(unsigned int capacidad = 20) : tabla(capacidad), tamanio(0) {}

    void insertar(const C& clave, const V& valor) {
        tabla.insertar(clave, valor);
        ++tamanio;
    }

    bool obtener(const C& clave, V& valor) const {
        return tabla.obtener(clave, valor);
    }

    unsigned int obtenerTamanio() const {
        return tamanio;
    }
};
