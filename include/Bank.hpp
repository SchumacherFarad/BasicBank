#include <iostream>
#include <vector>
#include "Customer.hpp"
#include "Worker.hpp"

string lastiban = "TR000000000000000000000001";

class Bank
{
private:
    vector<Customer *> customers;
    vector<Worker *> workers;

public:
    Bank();
    ~Bank();
    void readPeople(string file);
    void writePeople(string file);
    vector<Customer *> *get_customers();
    vector<Worker *> *get_workers();
    void addWorker(string name, string surname, string pass, double tempbal);
    void addCustomer(string name, string surname, string pass, double tempbal);
};
