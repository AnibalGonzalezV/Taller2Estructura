#pragma once
#include <vector>
#include <iostream>

class Costumer{
    private:
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