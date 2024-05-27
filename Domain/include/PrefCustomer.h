#pragma once
#include <iostream>
#include "Customer.h"


class PrefCustomer : public Customer{
    private:
    string tipo;
    public:
    PrefCustomer(string nombre, string rut, int edad, string tipo);
    string getTipo();
    void setTipo(string tipo);
    ~PrefCustomer();
};