#include "bank.h"

using namespace std;

// The Bank is a monitor, which behaves like a server, that manages student-account information for all students.
Bank::Bank ( unsigned int numStudents ) : numStudents(numStudents) {
    // initialize balance anad waiting accounts
    balance = new unsigned int[numStudents];
    accountWait = new uCondition[numStudents];

    // Each student’s account initially starts with a balance of $0.
    for ( unsigned int i=0; i < numStudents; i++ ) {
        balance[i]=0;
    } // for
} // bank

Bank::~Bank () {
    // delete balance and waiting accounts
    delete [] balance;
    delete [] accountWait;
} //~Bank

void Bank::deposit( unsigned int id, unsigned int amount ) { 
    balance[id] += amount; // add the amount to the student's balance

    // signal students waiting on withdrawing
    while(!accountWait[id].empty()) {
        accountWait[id].signal();
    }
} // deposit

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    
    // The courier waits until enough money has been deposited, which may require multiple deposits.
    while (balance[id] < amount ) {
        accountWait[id].wait();
    } //while

    balance[id]-=amount; // remove the amount from the balance
} // withdraw