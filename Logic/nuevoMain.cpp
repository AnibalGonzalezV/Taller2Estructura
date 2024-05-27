#include <queue>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "../include/Customer.h"
#include "../include/PrefCustomer.h"
#include "../include/Product.h"
#include "../include/StockRoom.h"

using namespace std;


void comenzarVenta(queue<Customer*> &cola_general, queue<PrefCustomer*> &colapref_final, StockRoom* &stock_room){
    int opcion = 0;
    vector<string> ventas;
    cout << "Inicio de Venta.." << endl;
    while(!cola_general.empty() || !colapref_final.empty()){
        while(!colapref_final.empty()){
            PrefCustomer* prefCustomer = colapref_final.front();
            cout << "Bienvenido " << prefCustomer->getNombre()<<endl;
            cout << stock_room->obtenerTodosLosProductos()<< endl;
            agregarPedido(stock_room, ventas);
            guardarBoleta(ventas, prefCustomer);
            colapref_final.pop();
            delete prefCustomer;
        }
        while(!cola_general.empty()){
            Customer* customer = cola_general.front();
            cout << "Bienvenido "<< customer->getNombre()<< endl;
            cout << stock_room->obtenerTodosLosProductos()<< endl;
            agregarPedido(stock_room, ventas);
            guardarBoleta2(ventas,customer);
            cola_general.pop();
            delete customer;
        }
    }
    if(guardarBoleta(ventas) == false){
        cout << "Se ha Guardado la boleta final." << endl;
    }
}

bool guardarBoleta(vector<string> &ventas, PrefCustomer* &prefCustomer){

    ofstream file("Informes/Boletas.txt",ios::app);
    if(!file.is_open()){
        cout << "Error!" << endl;
        return true
    }
    for (const auto& venta : ventas){
        file << venta << "$, Rut del Cliente: "<< prefCustomer->getRut() <<endl;
    }
    file.close();
    return false;
}
bool guardarBoleta2(vector<string> &ventas, Customer* &customer){

    ofstream file("Informes/Boletas.txt",ios::app);
    if(!file.is_open()){
        cout << "Error!" << endl;
        return true
    }
    for (const auto& venta : ventas){
        file << venta << "$, Rut del Cliente: "<< ustomer->getRut() <<endl;
    }
    file.close();
    return false;
}


void agregarPedido(StockRoom* &stock_room, vector<string> &ventas){
    vector<Product*> productosPedidos;
    cout << "Ingrese el ID de los productos que desea (Ingrese 'exit' para finalizar)" << endl;
    string codigoProducto;
    while (true) {
        cout << "Productos e ID´s";
        getline(cin, codigoProducto);

        if (id == "exit"){
            break;
        }
        Product* productObtenido = stock_room->getProductByID(id);
        if(productObtenido != nullptr){
            productosPedidos.push_back(productObtenido);
        } else {
            cout << "Error. No Existe Producto con la ID: " << codigoProducto << endl; 
        }
    }

    ventas.push_back(guardarVenta(stock_room, productosPedidos));
}

string guardarVenta(StockRoom* &stock_room, vector<Product*> &productosPedidos){
    cout << "**iMPRIMIENDO BOLETA**" << endl;
    int precio = 0;
    for (Product* producto : productosPedidos){
        cout << "Producto: " << productosPedidos->getNombre()<<endl;
        precio += productoPedido->getPrecio();
    }
    cout << "Valor Final: "<< precio<< endl;
    string text = "Boleta: " +to_string(precio);
    return text;


}


void ordenarFilas(queue<PrefCustomer*>& colapref_inicial,
queue<PrefCustomer*>& colapref_aux,
queue<PrefCustomer*>& colapref_final, const string &tipo){
    while(!colapref_inicial.empty()){
        if(colapref_inicial.front() -> getTipo() == tipo){
            PrefCustomer* lugar = colapref_inicial.front();
            colapref_inicial.pop();
            colapref_final.push(lugar);
        } else {
            PrefCustomer* lugar = colapref_inicial.front();
            colapref_inicial.pop();
            colapref_aux.push(lugar);
        }
    }
    colapref_inicial.swap(colapref_aux);
}

string toLower(const string& str) {
    string result = str;
    for (char& c : result) { c = tolower(c); }
    return result;
}

void agregarCliente(StockRoom* stock_room, queue<Customer*>& cola_general,
    queue<PrefCustomer*>& colapref_inicial,
    queue<PrefCustomer*>& colapref_aux,
    queue<PrefCustomer*>& colapref_final){
    int edad; string opcion, nombre, tipo, rut;

    cout << "Ingrese su nombre: " << endl; getLine(cin, nombre);
    cout << "Ingrese su Rut: " << endl; getline(cin, rut);
    cout << "Ingrese su Edad: " << endl; cin >> edad; cin.ignore();

    if(edad >= 65){ tipo = "tercera edad"; } 
    else { 
        cout << "¿Pertenece usted a alguno de los siguientes grupos (Discapacidad/Embarazadas)? Si/No: " << endl;
        if(toLower(opcion) == "si"){
            switch (stoi(opcion)){
                case 1:
                    tipo = "discapacidad"; break;
                case 2:
                    tipo = "embarazada"; break;
            }
        }
    }

    if(tipo != "tercera edad" && tipo!= "discapacidad" && tipo != "embarazada"){
        Customer* customer = new Customer(nombre, rut, edad); cola_general.push(customer);
    } else {
        PrefCustomer* prefCustomer= new PrefCustomer(nombre, rut, edad, tipo);
        colapref_inicial.push(prefCustomer);
    }
    ordenarFila(cola_pref_inicial, cola_aux, cola_pref_final,"tercera edad");
    ordenarFila(cola_pref_inicial, cola_aux, cola_pref_final,"discapacidad");
    ordenarFila(cola_pref_inicial, cola_aux, cola_pref_final,"embarazada");

}



void menuFarmacia(StockRoom* stock_room, queue<Customer*>& cola_general,
queue<PrefCustomer*>& colapref_inicial,
queue<PrefCustomer*>& colapref_aux,
queue<PrefCustomer*>& colapref_final){
    int opcion;
    do {
        cout << "----------- Menú de Farmacia -----------" << endl;
        cout << "1. Ingresar Cliente." << endl;
        cout << "2. Guardar y Salir." << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                // Lógica para ingresar cliente
                cout << "Registrando Cliente.." << endl;
                agregarCliente(stock_room, cola_general, cola_pref_inicial, cola_aux, cola_pref_final);
                comenzarVenta(cola_general, colapref_final, stock_room);
                break;
            case 2:
                // Lógica para guardar y salir
                cout << "Guardando y terminando la ejecución del programa..." << endl;
                delete stock_room; break;
            default:
                cout << "Opción inválida. Por favor, seleccione 1 ó 2." << endl; break;
        }
    } while(opcion != 2);    
}


void lecturaProductsFile(StockRoom* stock_room){
    ifstream file("productos.txt");
    string linea;

    while(getline(file, linea)){
        stringstream ss(line);
        string categoria, subcategoria, nombre_producto, codigoProducto;
        int precio;

        getline(ss, categoria, '/'); getline(ss, subcategoria, '/'); getline(ss, nombre_producto, '/');
        ss >> precio;
        getline(ss, codigoProducto, '/');

        Product* product = new Product(categoria, subcategoria, nombre_producto, precio, codigoProducto);

        stock_room->insertar(nombre_producto, product);
    }

    file.close();
}


int main(){
    StockRoom* stock_room = new StockRoom();
    queue<Cliente*> cola_comun; 
    queue<ClientePreferencial*> colapref_inicial;
    queue<ClientePreferencial*> colapref_aux; 
    queue<ClientePreferencial*> colapref_final;

    lecturaProductsFile(stock_room);
    menuFarmacia(stock_room, cola_general, cola_pref_inicial, cola_aux, cola_pref_final);
    return 0;
}