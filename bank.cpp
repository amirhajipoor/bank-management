#include "bank.h"
#include <stdlib.h>
#include <iostream>

void Customer::showInfo(Bank& bank, Customer customer)
{
    system("cls");
    cout << "First name: " << firstName << endl;
    cout << "Last name: " << lastName << endl;
    cout << "National code: " << nationalCode << endl;
    cout << "Date of birth: " << dateOfBirth << endl;
    cout << "Account Balance: " << customer.account.getBalance();

    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') customerMenu(bank, customer);

    } while (q != 'y' || q != 'n');
}

void Manager::showEmployeeInfo(Bank& bank)
{
    PersonnelId id;
    cout << "Personnel id: " << endl;
    cin >> id;

    for (const auto& person : bank.employeeList)
    {
        if (person.id == id)
        {
            cout << endl;
            cout << "Personnel Id: " << person.id << endl;
            cout << "First name: " << person.firstName << endl;
            cout << "Last name: " << person.lastName << endl;
            cout << "Salary: " << person.salary << endl;
            cout << "Date of birth: " << person.dateOfBirth << endl;
            cout << "Required Hours: " << person.requireHours << endl;
            cout << "Present hours: " << person.presentHours << endl;
        }
    }
}

void Manager::addEmployee(Bank& bank)
{
    system("cls");

    string fname, lname, date;

    cout << "First name: ";
    cin >> fname;
    cout << "Last name: ";
    cin >> lname;
    cout << "Date of birth: ";
    cin >> date;

    Employee emp{fname, lname, date};

    bank.employeeList.push_back(emp);
    id++;

    cout << endl << "Employee added." << endl;

    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') managerMenu(bank);

    } while (q != 'y' || q != 'n');
}

void Manager::deleteEmployee(Bank& bank)
{
    system("cls");
    cout << "employees: " << endl;

    for (const auto& p : bank.employeeList)
    {
        cout << "Id: " << p.id << endl;
        cout << "Name: " << p.firstName + ' ' + p.lastName << endl << endl;
    }

    bool found = false;

    do {
        PersonnelId id;
        cout << "Write id to delete employee: ";
        cin >> id;

        for (auto i = bank.employeeList.begin(); i != bank.employeeList.end(); i++)
        {
            if (i->id == id) {
                bank.employeeList.erase(i);
                cout << "Employee deleted.";
                found = true;
                break;
            }
        }
    } while (!found);


    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') managerMenu(bank);

    } while (q != 'y' || q != 'n');
}

void startMenu(Bank bank)
{
    system("cls");
    int q = 0;

    do {
        cout << "1) Employee" << endl;
        cout << "2) Manager" << endl;
        cout << "3) Customer" << endl;
        cout << "4) Exit" << endl;

    } while(q < 0 || q > 4);

    cin >> q;

    switch (q)
    {
    case 1:
        login(bank, "employee");
        break;

    case 2:
        login(bank, "manager");
        break;

    case 3:
        login(bank, "customer");
        break;

    case 4:
        abort();
        break;
    }
}

void employeeMenu(Bank bank, Employee employee)
{
    system("cls");
    int q = 0;

    do {
        cout << "1) Show Personal info" << endl;
        cout << "2) Show Customer info" << endl;
        cout << "3) Add Account for Customer" << endl;
        cout << "4) Delete Customer" << endl;
        cout << "5) Logout" << endl;
        cin >> q;

    } while(q < 0 || q > 5);

    if (q == 1) {
        showEmployeePersonalInfo(bank, employee);
    } else if (q == 2) {
        employee.showCustomerInfo(bank, employee);
    } else if (q == 3) {
        employee.addCustomer(bank, employee);
    } else if (q == 4) {
        employee.deleteCustomer(bank, employee);
    } else if (q == 5) {
        startMenu(bank);
    }
}

bool login(Bank bank, string role)
{
    system("cls");

    cout << "Please enter your Personnel id or National code: ";

    PersonnelId id;
    cin >> id;

    if (role == "employee") {
        for (const auto& p : bank.employeeList)
        {
            if (p.id == id)
            {
                employeeMenu(bank, p);
                return true;
            }
        }
    } else if (role == "manager") {
        if (bank.manager.id == id)
        {
            managerMenu(bank);
            return true;
        }
    } else if (role == "customer") {
        for (const auto& c : bank.customerList)
        {
            if (c.nationalCode == to_string(id))
            {
                customerMenu(bank, c);
                return true;
            }
        }
    }

    // Not found
    login(bank, role);


    return false;
}

void showEmployeePersonalInfo(Bank& bank, Employee& employee)
{
    system("cls");

    cout << "Personnel id: " << employee.id << endl;
    cout << "First name: " << employee.firstName << endl;
    cout << "Last name: " << employee.lastName << endl;
    cout << "Date of birth: " << employee.dateOfBirth << endl;
    cout << "Salary: " << employee.salary << endl;
    cout << "Require hours: " << employee.requireHours << endl;
    cout << "Persent hours: " << employee.presentHours << endl;

    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') employeeMenu(bank, employee);

    } while (q != 'y' || q != 'n');
}

void showManagerPersonalInfo(Bank bank)
{
    system("cls");

    cout << "Personnel id: " << bank.manager.id << endl;
    cout << "First name: " << bank.manager.firstName << endl;
    cout << "Last name: " << bank.manager.lastName << endl;
    cout << "Date of birth: " << bank.manager.dateOfBirth << endl;
    cout << "Salary: " << bank.manager.salary << endl;
    cout << "Require hours: " << bank.manager.requireHours << endl;
    cout << "Persent hours: " << bank.manager.presentHours << endl;


    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') managerMenu(bank);

    } while (q != 'y' || q != 'n');
}

void Employee::showCustomerInfo(Bank& bank, Employee employee)
{
    system("cls");
    cout << "National Code: ";
    string code;
    cin >> code;

    bool found = false;

    for (auto person : bank.customerList)
    {
        if (person.nationalCode == code)
        {
            cout << endl;
            cout << "First name: " << person.firstName << endl;
            cout << "Last name: " << person.lastName << endl;
            cout << "National code: " << person.nationalCode << endl;
            cout << "Date of birth: " << person.dateOfBirth << endl;
            cout << "Account Balance: " << person.account.getBalance() << endl;
            cout << "Account created at: " << person.account.createdAt << endl;
            found = true;
        }
    }

    if (!found) employee.showCustomerInfo(bank, employee);

    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') employeeMenu(bank, employee);

    } while (q != 'y' || q != 'n');
}


void Manager::showCustomerInfo(Bank& bank)
{
    system("cls");
    cout << "National Code: ";
    string code;
    cin >> code;

    bool found = false;

    for (auto person : bank.customerList)
    {
        if (person.nationalCode == code)
        {
            cout << endl;
            cout << "First name: " << person.firstName << endl;
            cout << "Last name: " << person.lastName << endl;
            cout << "National code: " << person.nationalCode << endl;
            cout << "Date of birth: " << person.dateOfBirth << endl;
            cout << "Account Balance: " << person.account.getBalance() << endl;
            cout << "Account created at: " << person.account.createdAt << endl;
            found = true;
        }
    }

    if (!found) bank.manager.showCustomerInfo(bank);

    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') managerMenu(bank);

    } while (q != 'y' || q != 'n');
}

void Employee::addCustomer(Bank& bank, Employee employee)
{
    system("cls");

    string firstName, lastName, dateOfBirth, nationalCode;

    cout << "First name: " << endl;
    cin >> firstName;
    cout << "Last name: " << endl;
    cin >> lastName;
    cout << "National code: " << endl;
    cin >> nationalCode;
    cout << "Date of birth: " << endl;
    cin >> dateOfBirth;

    Customer customer{firstName, lastName, nationalCode, dateOfBirth};

    bank.customerList.push_back(customer);
    cout << "Customer added!";

    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') employeeMenu(bank, employee);

    } while (q != 'y' || q != 'n');
}

void Manager::addCustomer(Bank& bank)
{
    system("cls");

    string firstName, lastName, dateOfBirth, nationalCode;

    cout << "First name: " << endl;
    cin >> firstName;
    cout << "Last name: " << endl;
    cin >> lastName;
    cout << "National code: " << endl;
    cin >> nationalCode;
    cout << "Date of birth: " << endl;
    cin >> dateOfBirth;

    Customer customer{firstName, lastName, nationalCode, dateOfBirth};

    bank.customerList.push_back(customer);
    cout << "Customer added!";

    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') managerMenu(bank);

    } while (q != 'y' || q != 'n');
}

void Employee::deleteCustomer(Bank& bank, Employee employee)
{
    system("cls");
    cout << "Customers: " << endl;

    for (const auto& person : bank.customerList)
    {
        cout << person.nationalCode << " - " << person.firstName << " " << person.lastName << endl;
    }

    bool found = false;
    string code;

    do {
        cout << "Which Customer you want to delete? type national code" << endl;
        cin >> code;

        for (auto iter = bank.customerList.begin(); iter != bank.customerList.end(); iter++)
        {
            if (iter->nationalCode == code) {
                bank.customerList.erase(iter);
                cout << "Customer deleted !";
                found = true;
                break;
            }
        }
    } while (!found);


    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') employeeMenu(bank, employee);

    } while (q != 'y' || q != 'n');
}

void Manager::deleteCustomer(Bank& bank)
{
    system("cls");
    cout << "Customers: " << endl;

    for (const auto& person : bank.customerList)
    {
        cout << person.nationalCode << " - " << person.firstName << " " << person.lastName << endl;
    }

    bool found = false;
    string code;

    do {
        cout << "Which Customer you want to delete? type national code" << endl;
        cin >> code;

        for (auto iter = bank.customerList.begin(); iter != bank.customerList.end(); iter++)
        {
            if (iter->nationalCode == code) {
                bank.customerList.erase(iter);
                cout << "Customer deleted !";
                found = true;
                break;
            }
        }
    } while (!found);


    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') managerMenu(bank);

    } while (q != 'y' || q != 'n');
}

void managerMenu(Bank bank)
{
    system("cls");
    int q = 0;

    do {
        cout << "1) Show Personal Info" << endl;
        cout << "2) Show Customer info" << endl;
        cout << "3) Add Account for Customer" << endl;
        cout << "4) Delete Customer" << endl;
        cout << "5) Show Employee info" << endl;
        cout << "6) Add employee" << endl;
        cout << "7) Delete employee" << endl;
        cout << "8) Set employees present hours" << endl;
        cout << "9) Logout" << endl;
        cin >> q;

    } while(q < 0 || q > 9);

    if (q == 1) {
        showManagerPersonalInfo(bank);
    } else if (q == 2) {
        bank.manager.showCustomerInfo(bank);
    } else if (q == 3) {
        bank.manager.addCustomer(bank);
    } else if (q == 4) {
        bank.manager.deleteCustomer(bank);
    } else if (q == 5) {
        bank.manager.showEmployeeInfo(bank);
    } else if (q == 6) {
        bank.manager.addEmployee(bank);
    } else if (q == 7) {
        bank.manager.deleteEmployee(bank);
    } else if (q == 8) {
        bank.manager.setEmployeePresentHours(bank);
    } else if (q == 9) {
        startMenu(bank);
    }
}


void customerMenu(Bank bank, Customer customer)
{
    system("cls");
    cout << "1) Increament balance" << endl;
    cout << "2) Take money" << endl;
    cout << "3) Show presonal info" << endl;
    cout << "4) Logout" << endl;

    int q = 0;
    while (q < 1 || q > 4) cin >> q;

    if (q == 1)
    {
        Amount amount;
        cout << "Current balance: " << customer.account.getBalance() << endl;
        cout << "How much do yo want to increament your balance? ";
        cin >> amount;
        customer.account.setBalance( customer.account.getBalance() + amount );
        cout << "done!" << endl;
        cout << "Current balance: " << customer.account.getBalance() << endl;

        char q = 'n';

        do {
            cout << endl;
            cout << "back to menu? (y/n): ";
            cin >> q;

            if (q == 'y') customerMenu(bank, customer);

        } while (q != 'y' || q != 'n');

    } else if (q == 2) {

        Amount amount;
        cout << "Current balance: " << customer.account.getBalance() << endl;

        if (!customer.account.getIsActive())
        {
            cout << "Sorry, your account inactive.";
        } else {
            cout << "How much do yo want to take? ";
            cin >> amount;

            if (customer.account.getBalance() >= amount) {
                customer.account.setBalance( customer.account.getBalance() - amount );
                cout << "done!" << endl;
                cout << "Current balance: " << customer.account.getBalance() << endl;
            } else {
                cout << "Sorry, your balance is not enough";
            }
        }

        char q = 'n';

        do {
            cout << endl;
            cout << "back to menu? (y/n): ";
            cin >> q;

            if (q == 'y') customerMenu(bank, customer);

        } while (q != 'y' || q != 'n');

    } else if (q == 3) {
        customer.showInfo(bank, customer);
    } else if (q == 4) {
        startMenu(bank);
    }
}

void Manager::setEmployeePresentHours(Bank& bank)
{
    system("cls");
    cout << "employees: " << endl;

    for (const auto& p : bank.employeeList)
    {
        cout << "Id: " << p.id << endl;
        cout << "Name: " << p.firstName + ' ' + p.lastName << endl << endl;
    }

    bool found = false;

    do {
        PersonnelId id;
        cout << "Write id to set hours: ";
        cin >> id;

        for (auto p : bank.employeeList)
        {
            if (p.id == id) {
                cout << "Current present hours: " << p.presentHours << endl;
                cout << "Enter present hours: ";
                cin >> p.presentHours;
                p.calculateSalary(p);
                cout << "Done!" << endl;
                cout << "Current present hours: " << p.presentHours << endl;
                cout << "Salary: " << p.salary << endl;
                found = true;
                break;
            }
        }

        bank.manager.calculateSalary();
        cout << "Manager Salary: " << bank.manager.salary << endl;

    } while (!found);


    char q = 'n';

    do {
        cout << endl;
        cout << "back to menu? (y/n): ";
        cin >> q;

        if (q == 'y') managerMenu(bank);

    } while (q != 'y' || q != 'n');
}


void Employee::calculateSalary(Employee& employee)
{
    if (employee.presentHours > employee.requireHours)
    {
        int hours = employee.presentHours - employee.requireHours;

        employee.salary += hours * 120000;
    } else {
        int freeHours = employee.requireHours - employee.presentHours;

        if (freeHours > 15) {
            employee.salary -= ((freeHours - 15) * 100000);
        }
    }
}

void Manager::calculateSalary()
{
    if (this->presentHours > this->requireHours)
    {
        int hours = this->presentHours - this->requireHours;

        this->salary += hours * 200000;
    } else {
        int freeHours = this->requireHours - this->presentHours;

        if (freeHours > 15) {
            this->salary -= ((freeHours - 15) * 100000);
        }
    }
}
