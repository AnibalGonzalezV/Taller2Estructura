#pragma once
#include "Product.h"
#include "HashMap.h"
#include <iostream>
#include <sstream>
using namespace std;

class StockRoom{
private:
    HashMap<string, Product*> productos;
public:
    StockRoom();
    //Agregar productos al MAP
    void agregarProducto(string nombreProducto, Product* producto);
    //Obtener un producto en especifico por su codigo
    Product* getProductByID(string codigoProducto);
    //metodo obtener todos los productos en un string
    string getProductos();
    ~StockRoom();
};