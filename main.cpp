#include <iostream>
#include "bank.h"
#include <conio.h>

using namespace std;

int main()
{
    Manager manager{"ali", "modiri", "1991"};
    Bank bank{manager};

    Customer customer{"reza", "bayat", "123", "1990/04/20"};
    Employee emp{"amir", "hajipoor", "2004/05/09"};

    bank.customerList.push_back(customer);
    bank.employeeList.push_back(emp);

    startMenu(bank);

    getch();
    return 0;
}
