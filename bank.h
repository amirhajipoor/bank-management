#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <ctime>

using namespace std;

typedef unsigned long int Amount;
typedef unsigned int PersonnelId;

const Amount baseSalary = 7000000;
const int baseRequireHours = 50;


class Bank;


class Account
{
public:
    string createdAt;

    Account(string holderNationalCode)
    {
        time_t now = time(0);

        char* createdAt = ctime(&now);

        static long id = 1500;
        this->id = id;
        this->holderNationalCode = holderNationalCode;
        this->createdAt  = createdAt;
        this->balance = 0;
        this->isActive = true;
        id++;
    }

    Amount getBalance() { return this->balance; }
    void setBalance(Amount a) { balance = a; }
    bool getIsActive() { return this->isActive; }

private:
    long id;
    string holderNationalCode;
    Amount balance;
    bool isActive;
protected:

};

class Customer
{
public:
    string firstName;
    string lastName;
    string nationalCode;
    string dateOfBirth;
    Account account;

    Customer(string fname, string lname, string nat, string birth)
        : account(nat)
    {
        this->firstName = fname;
        this->lastName = lname;
        this->nationalCode = nat;
        this->dateOfBirth = birth;
    }

    void showInfo(Bank& bank, Customer customer);

private:

protected:
};

typedef vector<Customer> CustomerList;

class Employee
{
public:
    string firstName;
    string lastName;
    PersonnelId id;
    string dateOfBirth;
    Amount salary;
    int requireHours; // ساعت موظفی
    int presentHours; // ساعت حضور

    Employee(string fname, string lname, string date)
    {
        static PersonnelId baseId = 2000;
        id = baseId;
        firstName = fname;
        lastName = lname;
        dateOfBirth = date;
        salary = baseSalary;
        requireHours = baseRequireHours;
        presentHours = 0;
        baseId++;

    }

    void calculateSalary(Employee& employee);
    void showCustomerInfo(Bank& bank, Employee employee);
    void addCustomer(Bank& bank, Employee employee);
    void deleteCustomer(Bank& bank, Employee employee);

private:

protected:
};

typedef vector<Employee> EmployeeList;

class Manager : public Employee
{
public:
    void showEmployeeInfo(Bank &bank);
    void addEmployee(Bank& bank);
    void deleteEmployee(Bank& bank);
    void showCustomerInfo(Bank& bank);
    void addCustomer(Bank& bank);
    void deleteCustomer(Bank& bank);
    void setEmployeePresentHours(Bank& bank);

    Manager(string fname, string lname, string date)
        : Employee(fname, lname, date)
    {
        this->presentHours = requireHours;
    }

    void showEmployeeSalary(Bank& bank);
    void calculateSalary();
};

class Bank
{
public:
    string name;
    string branchName;
    string branchCode;
    Manager manager;
    EmployeeList employeeList;
    CustomerList customerList;

    Bank(Manager m): manager(m) {}

private:

protected:
};

void startMenu(Bank bank);
bool login(Bank bank, string role);
void employeeMenu(Bank bank, Employee employee);
void managerMenu(Bank bank);
void customerMenu(Bank bank, Customer customer);
void showEmployeePersonalInfo(Bank& bank, Employee& employee);
void showCustomerInfo(Bank bank);

#endif // BANK_H
