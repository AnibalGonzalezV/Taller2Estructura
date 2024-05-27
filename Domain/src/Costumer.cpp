#include "../include/Customer.h"
using namespace std; 

Customer::Customer(string nombre, string rut, int edad) { this -> nombre = nombre; this -> rut = rut; this -> edad = edad; };

string Customer::getNombre(){ return this -> nombre; }

string Customer::getRut(){ return this -> rut; }

int Customer::getEdad(){ return this -> edad; }

void Customer::setNombre(string nombre){ this -> nombre = nombre; }

void Customer::setEdad(int edad){ this -> edad = edad; }

Customer::~Customer(){ cout<<"Customer object ("<< nombre << ") is being removed..." << endl; }