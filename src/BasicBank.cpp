#include <iostream>
#include "Bank.hpp"
#include "Customer.hpp"
#include "Worker.hpp"

using namespace std;
bool isRunning;
Bank bank;
const int MAX_TRIES = 3;

int login()
{
    string logiban, logpass;
    int index, tries = 0;
    cout << "Please login to your account" << "\n";
    cout << "Iban: ";
    cin >> logiban;
    bool validib = false;
    while (!validib)
    {
        for (int i = 0; i < bank.get_customers()->size(); i++)
        {
            if (bank.get_customers()->at(i)->getIban() == logiban)
            {
                validib = true;
                index = i;
            }
            else
            {
                cout << "The Iban that you entered is not valid. Please enter another" << "\n";
                cout << "Iban: ";
                cin >> logiban;
            }
        }
    }
    cout << "Password:" << "\n";
    for (int i = 0; i < MAX_TRIES; i++)
    {
        cin >> logpass;
        if (bank.get_customers()->at(index)->getPassword() == logpass)
        {
            cout << "Logged in succesfully" << "\n";
            return index;
        }
        else
        {
            cout << "Wrong Password!" << "\n";
        }
    }
    cout << "Login Failed! Account Blocked!" << "\n";
    isRunning = false;
    return -1;
}

void createAccount()
{
    string tempname, tempsurname, temppass;
    double tempbal;
    string isworker;
    cout <<"Please enter your Name: ";
    cin >> tempname;
    cout <<"Please enter your Surname: ";
    cin >> tempsurname;
    cout <<"Please enter your Password: ";
    cin >> temppass;
    cout <<"How much money do you want to deposit first: ";
    cin >> tempbal;
    cout << "Are you working for us? [Y/n]: ";
    cin >> isworker;
    while (isworker != "Y" || isworker != "n")
    {
        cout << "You entered a wrong key. Please Try Again: ";
        cin >> isworker;
    }
    if (isworker == "Y")
    {
        bank.addWorker(tempname, tempsurname, temppass, tempbal);
    }
    else
    {
        bank.addCustomer(tempname, tempsurname, temppass, tempbal);
    }
    cout << "Thanks for creating account!" << "\n";
}

int main()
{
    bank.readPeople("People.csv");
    cout << "Welcome to the YatırBank" << "\n\n";
    int index = login();
    int choice;
    while (isRunning)
    {
        cout << "Please select an operation" << "\n";
        cout << "1. Create an account" << "\n";
        cout << "2. Delete Your account" << "\n";
        cout << "3. Deposit" << "\n";
        cout << "4. Withdraw" << "\n";
        cout << "X. Exit" << "\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            deleteAccount();
            break;
        
        default:
            break;
        }
    }
}