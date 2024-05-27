#include "../Domain/include/HashMap.h"
#include "../Domain/include/Lista.h"
#include "../Domain/include/Tabla.h"
#include "../Domain/include/Producto.h"
#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
#include <string>

using namespace std;


/*
string toLowerCase(string& cadenaInicial){
    string cadenaFinal;
    for(char c: cadenaInicial){ cadenaFinal += tolower(c); }
    return cadenaFinal;
}

vector<string> split(const string& linea, char separador) {
    vector<string> partes;
    stringstream ss(linea);
    string parte;
    while (getline(ss, parte, separador)) {
        partes.push_back(parte);
    }
    return partes;
}

Producto* crearProducto(string categoria, string subcategoria, string nombre, int precio, string codigoProducto){
    Producto* p = new Producto(categoria,subcategoria,nombre,precio,codigoProducto);
    return p;
}

void leerArchivoBodega(string rutaTxt,HashMap<>map){
    ifstream file(rutaTxt);
    string line;

    while(getline(file,line)){
        vector <string> partes = split(line,'/');
        string categoria = partes[0]; string subcategoria = partes[1]; string nombre = partes[2];
        int precio = stoi(partes[3]); string codigoProducto = partes[4];
        Producto* p = crearProducto(categoria,subcategoria,nombre,precio,codigoProducto);
        map.insertar(codigoProducto,*p);
    }
}
*/



int main() {
    // Crear un objeto HashMap con clave de tipo string y valor de tipo int
    HashMap<string, int> miHashMap;
    //HashMap<string,Producto> map;

    // Insertar algunos elementos en el HashMap
    miHashMap.insertar("uno", 1);
    miHashMap.insertar("dos", 2);
    miHashMap.insertar("tres", 3);



    // Obtener el tamaño del HashMap
    cout << "Tamanio del HashMap: " << miHashMap.obtenerTamanio() << endl;
    //cout << "Tamanio del HashMap: " << map.obtenerTamanio() << endl;

    // Obtener el valor asociado a una clave y mostrarlo por pantalla
    int valor;
    if (miHashMap.obtener("dos", valor)) {
        cout << "El valor asociado a 'dos' es: " << valor << endl;
    } else {
        cout << "No se encontró la clave 'dos' en el HashMap." << endl;
    }

    // Intentar obtener un valor para una clave que no existe
    if (miHashMap.obtener("cuatro", valor)) {
        cout << "El valor asociado a 'cuatro' es: " << valor << endl;
    } else {
        cout << "No se encontro la clave 'cuatro' en el HashMap." << endl;
    }

    return 0;
}
