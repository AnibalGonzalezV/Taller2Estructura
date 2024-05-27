#pragma once
#include <iostream>
#include "Costumer.h"


class PrefCustomer : public Costumer{
    private:
    string tipo;
    public:
    PrefCustomer(string nombre, string rut, int edad, string tipo);
    string getTipo();
    void setTipo(string tipo);
    ~PrefCustomer();
};