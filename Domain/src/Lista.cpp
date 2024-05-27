#include "../../Domain/include/Lista.h"
#include <iostream>


template class Lista<std::string, int>;

template<typename C, typename V>
Lista<C, V>::Lista() : head(nullptr){}


template<typename C, typename V>
Lista<C, V>::~Lista(){
    Nodo<C, V>* actual = head;
    while(actual != nullptr){
        Nodo<C, V>* siguiente = actual-> siguiente;
        delete actual;
        actual = siguiente;
    }
}

template<typename C, typename V>
void Lista<C, V>::insertar(const C& clave, const V& valor){
    Nodo<C, V>* nuevo = new Nodo<C, V>(clave, valor);
    nuevo->siguiente = head;
    head = nuevo;
}

template <typename C, typename V>
bool Lista<C, V>::obtener(const C& clave, V& valor) const {
    Nodo<C, V>* actual = head;
    while (actual != nullptr) {
        if (actual->clave == clave) {
            valor = actual->valor;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

template <typename C, typename V>
bool Lista<C, V>::actualizar(const C& clave, const V& valor){
    Nodo<C, V>* actual = head;
    while(actual != nullptr){
        if(actual->clave == clave){
            actual->valor = valor;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}
