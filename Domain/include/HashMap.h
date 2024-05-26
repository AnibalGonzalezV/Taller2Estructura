#pragma once
#include "Tabla.h"


template<typename C, typename V>
class HashMap {
private:
    Tabla<C, V> tabla;
    int tamanio;

public:
    HashMap(int capacidad = 20);

    void insertar(const C& clave, const V& valor);
    bool obtener(const C& clave, V& valor) const;
    int obtenerTamanio() const;

};
