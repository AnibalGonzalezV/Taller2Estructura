#include <queue>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "../Domain/include/Customer.h"
#include "../Domain/include/PrefCustomer.h"
#include "../Domain/include/Product.h"
#include "../Domain/include/StockRoom.h"

using namespace std;


string guardarVenta(StockRoom* &stock_room, vector<Product*> &productosPedidos){
    cout << "**iMPRIMIENDO BOLETA**" << endl;
    int precio = 0;
    for (Product* producto : productosPedidos){
        cout << "Producto: " << producto->getNombreProducto()<<endl;
        precio += producto->getPrecio();
    }
    cout << "Valor Final: "<< precio<< endl;
    string text = "Boleta: " +to_string(precio);
    return text;
}


void agregarPedido(StockRoom* &stock_room, vector<string> &ventas){
    vector<Product*> productosPedidos;
    cout << "Ingrese el ID de los productos que desea (Ingrese 'exit' para finalizar)" << endl;
    string codigoProducto;
    while (true) {
        cout << "Productos e ID´s ";
        getline(cin, codigoProducto);

        if (codigoProducto == "exit"){
            break;
        }
        Product* productObtenido = stock_room->getProductByID(codigoProducto);
        if(productObtenido != nullptr){
            productosPedidos.push_back(productObtenido);
        } else {
            cout << "Error. No Existe Producto con la ID: " << codigoProducto << endl; 
        }
    }

    ventas.push_back(guardarVenta(stock_room, productosPedidos));
}

bool guardarBoleta(vector<string> &ventas, PrefCustomer* &prefCustomer){

    ofstream file("Data/Boletas.txt",ios::app);
    if(!file.is_open()){
        cout << "Error!" << endl;
        return true;
    }
    for (const auto& venta : ventas){
        file << venta << "$, Rut del Cliente: "<< prefCustomer->getRut() <<endl;
    }
    file.close();
    return false;
}
bool guardarBoleta2(vector<string> &ventas, Customer* &customer){

    ofstream file("Data/Boletas.txt",ios::app);
    if(!file.is_open()){
        cout << "Error!" << endl;
        return true;
    }
    for (const auto& venta : ventas){
        file << venta << "$, Rut del Cliente: "<< customer->getRut() <<endl;
    }
    file.close();
    return false;
}



void comenzarVenta(queue<Customer*> &cola_general, queue<PrefCustomer*> &colapref_final, StockRoom* &stock_room){
    int opcion = 0;
    vector<string> ventas;
    cout << "Inicio de Venta.." << endl;
    while(!cola_general.empty() || !colapref_final.empty()){
        while(!colapref_final.empty()){
            PrefCustomer* prefCustomer = colapref_final.front();
            cout << "Bienvenido " << prefCustomer->getNombre()<<endl;
            cout << stock_room->getProductos()<< endl;
            agregarPedido(stock_room, ventas);
            guardarBoleta(ventas, prefCustomer);
            colapref_final.pop();
            delete prefCustomer;
        }
        while(!cola_general.empty()){
            Customer* customer = cola_general.front();
            cout << "Bienvenido "<< customer->getNombre()<< endl;
            cout << stock_room->getProductos()<< endl;
            agregarPedido(stock_room, ventas);
            guardarBoleta2(ventas,customer);
            cola_general.pop();
            delete customer;
        }
    }
    //if(guardarBoleta(ventas, pref) == false){
      //  cout << "Se ha Guardado la boleta final." << endl;
    //}
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

    cout << "Ingrese su nombre: " << endl; getline(cin, nombre);
    cout << "Ingrese su Rut: " << endl; getline(cin, rut);
    cout << "Ingrese su Edad: " << endl; cin >> edad; cin.ignore();

    if(edad >= 65){ tipo = "tercera edad"; } 
    else { 
        cout << "¿Pertenece usted a alguno de los siguientes grupos (Discapacidad/Embarazadas)? Si/No: " << endl;
        getline(cin,opcion);
        if(toLower(opcion) == "si"){
            int op;
            cout << "1. para Discapacidad, 2. para Embarazada" << endl; cin >> op; cin.ignore();
            switch (op){
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
    ordenarFilas(colapref_inicial, colapref_aux, colapref_final,"tercera edad");
    ordenarFilas(colapref_inicial, colapref_aux, colapref_final,"discapacidad");
    ordenarFilas(colapref_inicial, colapref_aux, colapref_final,"embarazada");

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
        cin.ignore();

        switch(opcion) {
            case 1:
                // Lógica para ingresar cliente
                cout << "Registrando Cliente.." << endl;
                agregarCliente(stock_room, cola_general, colapref_inicial, colapref_aux, colapref_final);
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
    ifstream file("bodega.txt");
    string linea;

    while(getline(file, linea)){
        stringstream ss(linea);
        string categoria, subcategoria, nombre_producto, codigoProducto;
        int precio;

        getline(ss, categoria, '/'); getline(ss, subcategoria, '/'); getline(ss, nombre_producto, '/');
        ss >> precio;
        getline(ss, codigoProducto, '/');

        Product* product = new Product(categoria, subcategoria, nombre_producto, precio, codigoProducto);

        stock_room->agregarProducto(nombre_producto, product);
    }

    file.close();
}


int main(){
    StockRoom* stock_room = new StockRoom();
    queue<Customer*> cola_general; 
    queue<PrefCustomer*> colapref_inicial;
    queue<PrefCustomer*> colapref_aux; 
    queue<PrefCustomer*> colapref_final;

    lecturaProductsFile(stock_room);
    menuFarmacia(stock_room, cola_general, colapref_inicial, colapref_aux, colapref_final);
    return 0;
}