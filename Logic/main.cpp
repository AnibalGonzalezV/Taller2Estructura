#include "../Domain/include/HashMap.h"
#include "../Domain/include/Lista.h"
#include "../Domain/include/Tabla.h"
#include "../Domain/include/Productos.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Crear un objeto HashMap con clave de tipo string y valor de tipo int
    HashMap<string, int> miHashMap;

    // Insertar algunos elementos en el HashMap
    miHashMap.insertar("uno", 1);
    miHashMap.insertar("dos", 2);
    miHashMap.insertar("tres", 3);

    // Obtener el tamaño del HashMap
    cout << "Tamanio del HashMap: " << miHashMap.obtenerTamanio() << endl;

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
