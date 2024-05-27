#include "../../Domain/include/Product.h"
#include <iostream>

using namespace std;

Product::Product(string categoria, string subcategoria, string nombreProducto, int precio, string codigoProducto){
    this -> categoria = categoria;
    this -> subcategoria = subcategoria;
    this -> nombreProducto = nombreProducto;
    this -> precio = precio;
    this -> codigoProducto = codigoProducto;
};

Product::~Product(){};

string Product::getCategoria(){
    return categoria;
}
string Product::getSubCategoria(){
    return subcategoria;
}
string Product::getNombreProduct(){
    return nombre_Product;
}
int Product::getPrecio(){
    return precio;
}
string Product::getCodigo(){
    return codigo;
}