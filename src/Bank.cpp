#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Bank.hpp"
using namespace std;

string lastiban;
void Bank::readPeople(string file)
{
    ifstream readFile;
    readFile.open(file);
    string line;
    string type, iban, name, surname, password;
    double balance, salary;
    while (getline(readFile, line))
    {
        stringstream lineStream(line);
        string cell;
        getline(lineStream, cell, ',');
        type = cell;
        getline(lineStream, cell, ',');
        iban = cell;
        getline(lineStream, cell, ',');
        name = cell;
        getline(lineStream, cell, ',');
        surname = cell;
        getline(lineStream, cell, ',');
        balance = stod(cell);
        if (type == "Worker")
        {
            getline(lineStream, cell, ',');
            password = cell;
            getline(lineStream, cell, '\r');
            salary = stod(cell);
            Worker *worker_to_add = new Worker(balance, iban, name, surname, password, salary);
            workers.push_back(worker_to_add);
        }
        else
        {
            getline(lineStream, cell, '\r');
            password = cell;
            Customer *customer_to_add = new Customer(balance, iban, name, surname, password);
            customers.push_back(customer_to_add);
        }
    }
    readFile.close();
    lastiban = "TR";
    lastiban += string((24 - to_string(max(stoll(customers.at(customers.size() - 1)->getIban().substr(2, 24)), stoll(workers.at(workers.size() - 1)->getIban().substr(2, 24))) + 1).size()),'0');
    lastiban += to_string(max(stoll(customers.at(customers.size() - 1)->getIban().substr(2, 24)), stoll(workers.at(workers.size() - 1)->getIban().substr(2, 24))) + 1);
}

void Bank::writePeople(string file)
{
    ofstream writeFile;
    writeFile.open(file);
    for (int i = 0; i < workers.size(); i++)
    {
        writeFile << workers[i]->getType() << ',' << workers[i]->getIban() << ',' << workers[i]->getName() << ',' << workers[i]->getSurname() << ',' << workers[i]->getBalance()<< ',' << workers[i]->getPassword() << ',' << workers[i]->getSalary()<<"\n";
    }
    for (int i = 0; i < customers.size(); i++)
    {
        writeFile << customers[i]->getType() << ',' << customers[i]->getIban() << ',' << customers[i]->getName() << ',' << customers[i]->getSurname() << ',' << customers[i]->getBalance()<< ',' << customers[i]->getPassword()<<"\n";
    }
}

vector<Customer *> *Bank::get_customers()
{
    return &customers;
}
vector<Worker *> *Bank::get_workers()
{
    return &workers;
}

void Bank::addWorker(string name, string surname, string pass, double tempbal){
    Worker* worker_to_add = new Worker(tempbal, lastiban, name, surname, pass);
    this->get_workers()->push_back(worker_to_add);
    lastiban = "TR" + '0'*(24-to_string(stoll(lastiban.substr(2,24))+1).size()) + to_string(stoll(lastiban.substr(2,24))+1);
}
void Bank::addCustomer(string name, string surname, string pass, double tempbal){
    Customer* customer_to_add = new Customer(tempbal, lastiban, name, surname, pass);
    this->get_customers()->push_back(customer_to_add);
    lastiban = "TR" + '0'*(24-to_string(stoll(lastiban.substr(2,24))+1).size()) + to_string(stoll(lastiban.substr(2,24))+1);
}

Bank::Bank(){
    customers = {};
    workers = {};
}
Bank::~Bank(){
    customers.clear();
    workers.clear();
}

void Bank::transferMoney(bool isworker, int index, string iban_to_transfer, double money_to_transfer){
    bool transfer_isworker;
    int indextransfer;
    int balancefirst = isworker ? get_workers()->at(index)->getBalance() : get_customers()->at(index)->getBalance(); 
    for (int i = 0; i < static_cast<int>(get_customers()->size()); i++)
    {
        if(iban_to_transfer == get_customers()->at(i)->getIban()){
            transfer_isworker = false;
            indextransfer= i;
        }
    }
    for (int i = 0; i < static_cast<int>(get_workers()->size()); i++)
    {
        if (iban_to_transfer == get_workers()->at(i)->getIban()){
            transfer_isworker = true;
            indextransfer = i;
        }
    }
    if (isworker)
    {
        if (transfer_isworker)
        {
            get_workers()->at(index)->withdraw(money_to_transfer);
            if (get_workers()->at(index)->getBalance() != balancefirst)
            {
                get_workers()->at(indextransfer)->deposit(money_to_transfer);
                cout << "Transaction has been completed successfully. \n";
            }
        }
        else
        {
            get_workers()->at(index)->withdraw(money_to_transfer);
            if (get_workers()->at(index)->getBalance() != balancefirst)
            {
                get_customers()->at(indextransfer)->deposit(money_to_transfer);
                cout << "Transaction has been completed successfully. \n";
            }
        }
    }
    else
    {
        if (transfer_isworker)
        {
            get_customers()->at(index)->withdraw(money_to_transfer);
            if (get_customers()->at(index)->getBalance() != balancefirst)
            {
                get_workers()->at(indextransfer)->deposit(money_to_transfer);
                cout << "Transaction has been completed successfully. \n";
            }
        }
        else
        {
            get_customers()->at(index)->withdraw(money_to_transfer);
            if (get_customers()->at(index)->getBalance() != balancefirst)
            {
                get_customers()->at(indextransfer)->deposit(money_to_transfer);
                cout << "Transaction has been completed successfully. \n";
            }
        }
    }
}