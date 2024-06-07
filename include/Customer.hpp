#include <string>


using namespace std;


class Customer{
    protected:
        string type;
        double balance;
        string iban;
        string name;
        string surname;
        string password;
    public:
        Customer(double balance, string iban, string name, string surname, string password);
        ~Customer();
        Customer();
        void deposit(double money);
        void withdraw(double money);
        string getType();
        double getBalance();
        string getIban();
        string getName();
        string getSurname();
        string getPassword();
};