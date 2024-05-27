#include "../include/PrefCustomer.h"
using namespace std;

PrefCustomer::PrefCustomer(){};

PrefCustomer::PrefCustomer(string nombre, int edad, string preferencia) : Customer(nombre, edad) { this ->preferencia = preferencia; }

PrefCustomer::~PrefCustomer(){ cout<<"Preferencial Customer object ("<< nombre << ") is being removed..." << endl; }

string PrefCustomer::getPreferencia() { return this -> preferencia; }

void PrefCustomer::setPreferencia(string preferencia) { this -> preferencia = preferencia; }