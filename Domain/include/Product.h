#pragma once
#include <iostream>
using namespace std;

class Product{
    private:
        int precio; string categoria, subcategoria, nombreProducto, codigoProducto;
    public:
        Producto(string categoria, string subcategoria, string nombreProducto, int precio, string codigoProducto);
        int getPrecio();
        string getCategoria();
        string getSubCategoria();
        string getNombreProducto();
        string getCodigo();
        ~Producto();
};
