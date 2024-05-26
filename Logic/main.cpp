#include "/Domain/include/HashMap.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    HashMap<string, int> mapa;

    mapa.insertar("Juan", 30);
    mapa.insertar("Pedro", 25);
    mapa.insertar("Ana", 40);
    mapa.insertar("Pepe", 14);   

    string nombre = "Pedro";
    int edad;
    if(mapa.obtener(nombre, edad)){
        cout << "La edad de " << nombre << " es " << edad << " años." << endl;
    } else {
        cout << "No se encontró informacion para " << nombre << "." << endl;
    }

    string nombre = "Anibal";
    int edad;
    if(mapa.obtener(nombre, edad)){
        cout << "La edad de " << nombre << " es " << edad << " años." << endl;
    } else {
        cout << "No se encontró informacion para " << nombre << "." << endl;
    }


}
