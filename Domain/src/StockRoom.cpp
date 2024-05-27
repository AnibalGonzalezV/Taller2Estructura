#include "../include/StockRoom.h"
using namespace std;

StockRoom::StockRoom() {}

void StockRoom::agregarProducto(string nombreProducto, Product* producto) { productos.insert(nombreProducto, producto); }

Product* StockRoom::getProductByID(string codigoProducto) {
    try { return productos.get(codigoProducto); } 
    catch (const runtime_error& e) { return nullptr; }
}

string StockRoom::getProductos() {
    stringstream ss;
    ss << "Inventario de los productos:\n";
    for (int i = 0; i < productos.getCapacity(); ++i) {
        HashNode<string, Product*>* nodo = productos.getTable()[i];
        while (nodo != nullptr) { ss << "Nombre: " << nodo->key << endl; nodo = nodo->next; }
    }
    return ss.str();
}

StockRoom::~StockRoom() { cout << "[i] StockRoom object is being removed... " << endl; }