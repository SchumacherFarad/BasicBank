#include <iostream>
#include "Bank.hpp"
#include "Customer.hpp"
#include "Worker.hpp"

using namespace std;

bool isRunning, isbankworker;
Bank bank;
const int MAX_TRIES = 3;

int createAccount()
{
    string tempname, tempsurname, temppass;
    double tempbal;
    string workinp;
    cout << "Please enter your Name: ";
    cin >> tempname;
    cout << "Please enter your Surname: ";
    cin >> tempsurname;
    cout << "Please enter your Password: ";
    cin >> temppass;
    cout << "How much money do you want to deposit first: ";
    cin >> tempbal;
    cout << "Are you working for us? [Y/n]: ";
    cin >> workinp;
    while (workinp != "Y" && workinp != "n")
    {
        cout << "You entered a wrong key. Please Try Again: ";
        cin >> workinp;
    }
    if (workinp == "Y")
    {
        bank.addWorker(tempname, tempsurname, temppass, tempbal);
        cout << "Thanks for creating account!" << "\n";
        return bank.get_workers()->size() - 1;
    }
    else
    {
        bank.addCustomer(tempname, tempsurname, temppass, tempbal);
        cout << "Thanks for creating account!" << "\n";
        return bank.get_customers()->size() - 1;
    }
    return -1;
}

int login()
{
    string logorcre;
    cout << "L -- Login To your account" << "\n";
    cout << "C -- Create an account" << "\n";
    cin >> logorcre;
    while (logorcre != "L" && logorcre != "C")
    {
        cout << "You wrote an unvalid input! Please try again" << "\n";
        cout << "L -- Login To your account" << "\n";
        cout << "C -- Create an account" << "\n";
        cin >> logorcre;
    }

    string logiban, logpass;
    int index;
    if (logorcre == "L")
    {
        cout << "Please login to your account" << "\n";
        cout << "Iban: ";
        cin >> logiban;
        bool validib = false;
        while (!validib)
        {
            for (int i = 0; i < static_cast<int>(bank.get_customers()->size()); i++)
            {
                if (bank.get_customers()->at(i)->getIban() == logiban)
                {
                    validib = true;
                    index = i;
                    isbankworker = false;
                }
            }
            for (int i = 0; i < static_cast<int>(bank.get_workers()->size()); i++)
            {
                if (bank.get_workers()->at(i)->getIban() == logiban)
                {
                    validib = true;
                    index = i;
                    isbankworker = true;
                }
            }

            if (!validib)
            {
                cout << "The Iban that you entered is not valid. Please enter another" << "\n";
                cout << "Iban: ";
                cin >> logiban;
            }
        }
        cout << "Password:" << "\n";
        for (int i = 0; i < MAX_TRIES; i++)
        {
            cin >> logpass;
            if (!isbankworker)
            {
                if (bank.get_customers()->at(index)->getPassword() == logpass)
                {
                    cout << "Logged in succesfully" << "\n";
                    isRunning = true;
                    return index;
                }
                else
                {
                    cout << "Wrong Password!" << "\n";
                }
            }
            else
            {
                if (bank.get_workers()->at(index)->getPassword() == logpass)
                {
                    cout << "Logged in succesfully" << "\n";
                    isRunning = true;
                    return index;
                }
                else
                {
                    cout << "Wrong Password!" << "\n";
                }
            }
        }
        cout << "Login Failed! Account Blocked!" << "\n";
        isRunning = false;
        return -1;
    }
    if (logorcre == "C")
    {
        index = createAccount();
        return index;
    }
    return -1;
}

int main()
{
    bank.readPeople("O:/ITU/GITHUB/BasicBank/BasicBank/src/People.csv");
    cout << "Welcome to the YatırBank" << "\n\n";
    int index = login();
    int choice;
    while (isRunning)
    {
        cout << "Please select an operation" << "\n";
        cout << "1. Deposit" << "\n";
        cout << "2. Withdraw" << "\n";
        cout << "3. Delete Your account" << "\n";
        if (isbankworker)
        {
            cout << "4. Get Salary" << "\n";
        }
        cout << "9. Exit" << "\n";
        cin >> choice;
        string sure;
        switch (choice)
        {
        case 1:
            int money_to_deposit;
            cout << "How much money do you want to deposit?" << "\n";
            cin >> money_to_deposit;
            if (isbankworker)
            {
                bank.get_workers()->at(index)->deposit(money_to_deposit);
            }
            else
            {
                bank.get_customers()->at(index)->deposit(money_to_deposit);
            }
            break;
        case 2:
            int money_to_withdraw;
            cout << "How much money do you want to withdraw?" << "\n";
            cin >> money_to_withdraw;
            if (isbankworker)
            {
                bank.get_workers()->at(index)->withdraw(money_to_withdraw);
            }
            else
            {
                bank.get_customers()->at(index)->withdraw(money_to_withdraw);
            }
            break;
        case 3:
            cout << "Are you sure deleting your account? [Y/n]" << "\n";
            cin >> sure;
            while (sure != "Y" || sure != "n")
            {
                cout << "You entered an unvalid input. Please try again." << "\n";
                cin >> sure;
            }
            if (sure == "Y")
            {
                if (isbankworker)
                {
                    bank.get_workers()->erase(bank.get_workers()->begin() + index);
                    isRunning = false;
                }
                else
                {
                    bank.get_customers()->erase(bank.get_customers()->begin() + index);
                    isRunning = false;
                }
            }
            else
            {
                cout << "Thanks for not deleting your account" << "\n";
            }
            break;
        case 4:
            if (isbankworker)
            {
                bank.get_workers()->at(index)->addSalarytoBalance();
            }
            else
            {
                cout << "You entered an invalid input. Please try again.";
            }
            break;
        case 9:
            isRunning = false;
            break;
        default:
            cout << "You entered an invalid input. Please try again.";
            break;
        }
    }
    bank.writePeople("O:/ITU/GITHUB/BasicBank/BasicBank/src/People.csv");
}