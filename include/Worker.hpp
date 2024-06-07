#pragma once
#include "Customer.hpp"


const int STARTER_SALARY = 1000;

class Worker: public Customer{
    private:
        double salary;
    public:
        Worker(double balance, string iban, string name, string surname, string password, double salary);
        Worker(double balance, string iban, string name, string surname, string password);
        void giveRaise(double percentage);
        void addSalarytoBalance();
        double getSalary();
};