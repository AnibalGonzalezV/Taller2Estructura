#pragma once

template <typename C, typename V>
struct Nodo {
    C clave;
    V valor;
    Nodo* siguiente;

    Nodo(const C& c, const V& v) : clave(c), valor(v), siguiente(nullptr){}
};