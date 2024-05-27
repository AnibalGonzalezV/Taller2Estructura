#include <queue>
#include <ctime>
#include <iomanip>
#include <vector> // Sólo se utiliza para separar las partes del txt y demás, no para guardar productos
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "../include/StockRoom.h"
#include "../include/Product.h"
#include "../include/Customer.h"
#include "../include/PrefCustomer.h"
using namespace std;

vector<string> split(const string& linea, char separador) {
    vector<string> partes; stringstream ss(linea); string parte;
    while (getline(ss, parte, separador)) { partes.push_back(parte); }
    return partes;
}

bool verificarArchivo(string rutaTxt){
    ifstream file(rutaTxt);
    if(!file.is_open()){ return false; }
    return true;
}

void leerArchivoBodega(string rutaTxt){
    
    if (!verificarArchivo(rutaTxt)) { cout << "El archivo de la bodega no se puede abrir." << endl; return -1; }
    ifstream file(rutaTxt); string line;

    while(getline(file,line)){
        vector <string> partes = split(line,'/');
        string categoria = partes[0]; string subcategoria = partes[1]; string nombreProducto = partes[2];
        int precio = stoi(partes[3]); string codigoProducto = partes[4];
        Product* producto = new Product(categoria,subcategoria,nombreProducto,precio,codigoProducto);
    }
    file.close();
}

int guardarVenta(vector<string> &ventas){
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ofstream archivo("data/Ventas.txt",ios::app);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return -1;
    }
    for (const auto& venta : ventas) {
        archivo <<venta+" fecha: "<< put_time(&tm, "%d-%m-%Y ")<< endl;
    }
    archivo.close();
    return 0;
}

string generarVenta(Bodega* &bodega, vector<Producto*> &productos){
    cout<< "**GESTIONAR VENTA**" << endl;
    cout << "Se genero la venta con los siguientes productos:\n";
    int precioTotal = 0;
    for (Producto* producto : productos) {
        cout<<producto ->getNombre()<<endl;
        precioTotal += producto -> getPrecio();
    }
    cout<<"total: "<<precioTotal<<endl;
    string salida = "Venta total: "+to_string(precioTotal);
    return salida;
}

void ingresarPedido(Bodega* &bodega, vector<string> &ventas){
    vector<Producto*> productosSolicitados;
    cout << "Ingrese los productos que el cliente solicita (Ingrese 'fin' para finalizar):\n";
    cout << "No olividar ingresar el producto igual como aparece " << std :: endl;
    string producto;
    while (true) {
        cout << "Producto: ";
        getline(cin, producto);
        
        if (producto == "fin") {
            break;// Termina el bucle cuando se ingresa "fin"
        }
        Producto* productoObtenido = bodega-> obtenerProducto(producto);
        if(productoObtenido != nullptr){
            productosSolicitados.push_back(productoObtenido);
        }else {
            cerr << "Error: Producto no encontrado en la bodega: " << producto << endl;
        }
    }
    
    ventas.push_back(generarVenta(bodega,productosSolicitados));
}

void asignarLugar(queue<Customer*> &cola_comun, 
                queue<PrefCustomer*> &cola_preferencial) {
    int opcion;
    string nombre;
    int edad;
    string preferencia;

    cout << "Ingrese nombre: " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    getline(cin, nombre);

    cout << "Ingrese edad: " << endl;
    while (!(cin >> edad)) {
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Por favor, ingrese una edad válida: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

    if (edad >= 60) {
        preferencia = "tercera edad";
    } else {
        cout << "discapacidad (1) / embarazada (2) / nada (3)" << endl;
        while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Opción ingresada no válida. Por favor, ingrese una opción válida (1/2/3): ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        switch (opcion) {
        case 1:
            preferencia = "discapacidad";
            break;
        case 2:
            preferencia = "embarazada";
            break;
        default:
            preferencia = "nada";
            break;
        }
    }
    
    if (preferencia == "nada") {
        Cliente* cliente = new Cliente(nombre, edad);
        cola_comun.push(cliente);
    } else {
        ClientePreferencial* clientepref = new ClientePreferencial(nombre, edad, preferencia);
        cola_preferencial.push(clientepref);
    }
}

void ordenar_colas(queue<ClientePreferencial*>  &cola_1,
                   queue<ClientePreferencial*>  &cola_2, 
                   queue<ClientePreferencial*>  &cola_aux, 
                   const string &pref)
{
    while(!cola_1.empty()) {
        if(cola_1.front() -> getPreferencia() == pref) {
            ClientePreferencial* elemento = cola_1.front();
            cola_1.pop();
            cola_2.push(elemento);
        } else {
            ClientePreferencial* elemento = cola_1.front();
            cola_1.pop();
            cola_aux.push(elemento);
        }
    }
    cola_1.swap(cola_aux); // Cambia la cola_1 con cola_aux
}

void fila(queue<Cliente*> &cola_comun, 
          queue<ClientePreferencial*> &cola_preferencial){
    int opcion;
    cout<<"MENU"<<endl;
    cout<<"(1) Agregar clientes a la cola"<<endl;
    cout<<"(2) Finalizar"<<endl;
    cin>>opcion;
    while(opcion != 2){
        dar_numero(cola_comun, cola_preferencial);
        cout<<"Cliente agregado a la cola"<<endl;
        cout<<"************"<<endl;
        cout<<"(1) Agregar clientes a la cola"<<endl;
        cout<<"(2) Finalizar"<<endl;
        cin>>opcion;
    }
}

void GestionarCliente(queue<Cliente*> &cola_comun,
                      queue<ClientePreferencial*> &cola_1,
                      queue<ClientePreferencial*> &cola_2,
                      queue<ClientePreferencial*> &cola_aux,
                      Bodega* &bodega){
    cout<< "**GESTIONAR CLIENTE**" << endl;
    fila(cola_comun, cola_1);
    ordenar_colas(cola_1,cola_2,cola_aux,"tercera edad");
    ordenar_colas(cola_1,cola_2,cola_aux,"embarazada");
    ordenar_colas(cola_1,cola_2,cola_aux,"discapacidad");
}

void GestionarVenta(queue<Cliente*> &cola_comun,
                    queue<ClientePreferencial*> &cola_pref,
                    Bodega* &bodega){
    int opcion=0;
    vector<string> ventas;
    cout<< "**GESTIONAR VENTA**" << endl;
    while(!cola_comun.empty() || !cola_pref.empty()){
        while(!cola_pref.empty()){
            ClientePreferencial* cliente = cola_pref.front();
            cout<<"Hola "<<cliente->getNombre()<<endl;
            cout<<bodega -> obtenerTodosLosProductos()<<endl;
            ingresarPedido(bodega,ventas);
            cola_pref.pop();
            delete cliente;
            cout<< "*******" << endl;
        }
        while(!cola_comun.empty()){
            Cliente* cliente = cola_comun.front();
            cout<<"Hola "<<cliente->getNombre()<<endl;
            cout<<bodega -> obtenerTodosLosProductos()<<endl;
            ingresarPedido(bodega,ventas);
            cola_comun.pop();
            delete cliente;
            cout<< "*******" << endl;
        }
    }
    if(guardarVenta(ventas) == 0){
        cout<<"ventas guardadas"<<endl;
    }
}

int displayOpciones(){
    int opcion = 0;
    cout<< "Bienvenido a Farmacias Cruz Naranja" << endl;
    cout << "(0) Salir \n(1) Administrar fila de clientes" << endl;
    cout << "Ingrese opción:" << endl; cin >> opcion;
    while(opcion > 1 || opcion < 0){
        cout << "[!] Opción ingresada no es válida. Intente de nuevo. " << endl;
        cin >> opcion;
    }
    cin.ignore();

    return opcion;
}

void Menu(Bodega* &bodega){
    queue<Customer*> fila; 
    queue<PrefCustomer*> filaPref;
    queue<PrefCustomer*> filaPrefAuxiliar; 
    queue<PrefCustomer*> filaPrefOrdenada;
    int opcion = displayOpciones();
    switch (opcion) {
    case 1:
        GestionarCliente(cola_comun, colapref_inicial, colapref_final, colapref_aux, bodega);
        GestionarVenta(cola_comun, colapref_final, bodega);
        break;
    case 2:
        cout << "Saliendo del programa..." << endl;
        break;
    }
}

int main(){
    StockRoom* bodega = new StockRoom();
    //if(leerArchivoBodega(bodega) == 0){
      //  Menu(bodega);
    //}
    menuPrincipal();

    delete bodega;
    return 0;
}