#pragma once

#include <iostream>

using namespace std;

class Producto{
    private:
        string categoria;
        string subcategoria;
        string nombre_producto;
        int precio;
        string codigo;
    public:
        Producto(string categoria, string subcategoria, string nombre_producto, int precio, string codigo);

        ~Producto();

        string getCategoria();
        string getSubCategoria();
        string getNombreProducto();
        int getPrecio();
        string getCodigo();


};
