#pragma once
#include "Tabla.h"


template<typename C, typename V>
class HashMap {
private:
    Tabla<C, V> tabla;
    unsigned int tamanio;

public:
    HashMap(unsigned int capacidad = 20);

    void insertar(const C& clave, const V& valor);
    bool obtener(const C& clave, V& valor) const;
    unsigned int obtenerTamanio() const;

};
#include "/Domain/src/HashMap.cpp"