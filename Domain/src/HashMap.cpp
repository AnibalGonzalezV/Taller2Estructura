#include "../../Domain/include/HashMap.h"

template <typename C, typename V>
HashMap<C, V>::HashMap(int capacidad) : tabla(capacidad), tamanio(0) {}

template <typename C, typename V>
void HashMap<C, V>::insertar(const C& clave, const V& valor) {
    tabla.insertar(clave, valor);
    ++tamanio;
}

template <typename C, typename V>
bool HashMap<C, V>::obtener(const C& clave, V& valor) const {
    return tabla.obtener(clave, valor);
}

template <typename C, typename V>
int HashMap<C, V>::obtenerTamanio() const {
    return tamanio;
}