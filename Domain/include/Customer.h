#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std; 

class Customer{
    protected:
        string nombre, rut; int edad;
    public:
        Customer(string nombre, string rut, int edad);
        string getNombre();
        string getRut();
        int getEdad();
        void setNombre(string nombre);
        void setEdad(int edad); 
        ~Customer();
};