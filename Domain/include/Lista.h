#pragma once
#include "Nodo.h"

template <typename C, typename V>
class Lista {
private:
    Nodo<C, V>* head;

public:
    Lista();
    ~Lista();

    void insertar(const C& clave, const V& valor);
    bool obtener(const C& clave, V& valor) const;
    bool actualizar(const C& clave, const V& valor);
};