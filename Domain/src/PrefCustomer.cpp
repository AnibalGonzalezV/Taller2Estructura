#include "../include/PrefCustomer.h"
using namespace std;

PrefCustomer::PrefCustomer(string nombre, string rut, int edad, string tipo) : Customer(nombre, rut, edad) { this ->tipo = tipo; }

PrefCustomer::~PrefCustomer(){ cout<<"Preferencial Customer object ("<< nombre << ") is being removed..." << endl; }

string PrefCustomer::getTipo() { return this -> tipo; }

void PrefCustomer::setTipo(string tipo) { this -> tipo = tipo; }