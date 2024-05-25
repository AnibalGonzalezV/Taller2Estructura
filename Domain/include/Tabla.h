#pragma once
#include "Lista.h"


template <typename C, typename V>
class Tabla {
private:
    Lista<C, V>* tabla;
    unsigned int capacidad;

    unsigned int calcularHash(const C& clave) const;

public:
    Tabla(unsigned int cap);
    ~Tabla();

    void insertar(const C& clave, const V& valor);
    bool obtener(const C& clave, V& valor) const;
};
#include "Domain/src/Tabla.cpp"
