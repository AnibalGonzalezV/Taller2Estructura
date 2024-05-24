#include "Domain/include/Productos.h"
#include <iostream>

using namespace std;

Producto::Producto(string categoria, string subcategoria, string nombre_producto, int precio, string codigo){
    this -> categoria = categoria;
    this -> subcategoria = subcategoria;
    this -> nombre_producto = nombre_producto;
    this -> precio = precio;
    this -> codigo = codigo;


};

Producto::~Producto(){};

string Producto::getCategoria(){
    return categoria;
}
string Producto::getSubCategoria(){
    return subcategoria;
}
string Producto::getNombreProducto(){
    return nombre_producto;
}
int Producto::getPrecio(){
    return precio;
}
string Producto::getCodigo(){
    return codigo;
}