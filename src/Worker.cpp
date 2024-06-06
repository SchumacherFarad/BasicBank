#include <iostream>
#include "Worker.hpp"

Worker::Worker(double balance, string iban, string name, string surname, string password, double salary){
    this->type = "Worker";
    this->name = name;
    this->surname = surname;
    this->balance = balance;
    this->iban = iban;
    this->password = password;
    this->salary = salary;
}

Worker::Worker(double balance, string iban, string name, string surname, string password){
    this->type = "Worker";
    this->name = name;
    this->surname = surname;
    this->balance = balance;
    this->iban = iban;
    this->password = password;
    this->salary = STARTER_SALARY;
}

void Worker::addSalarytoBalance(){
    this->balance += this->salary;
}
void Worker::giveRaise(double percentage){
    this->salary += this->salary*percentage;
}
double Worker::getSalary(){
    return this->salary;
}