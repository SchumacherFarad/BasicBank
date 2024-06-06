#include <iostream>
#include "Customer.hpp"


Customer::Customer(double balance, string iban, string name, string surname, string password){
    this->type = "Customer";
    this->balance = balance;
    this->iban = iban;
    this->name = name;
    this->surname = surname;
    this->password = password;
}

void Customer::deposit(double money){
    this->balance += money;
}

void Customer::withdraw(double money){
    this->balance -= money;
}

string Customer::getType(){
    return this->type;
}

double Customer::getBalance(){
    return this->balance;
}

string Customer::getIban(){
    return this->iban;
}

string Customer::getName(){
    return this->name;
}

string Customer::getSurname(){
    return this->surname;
}