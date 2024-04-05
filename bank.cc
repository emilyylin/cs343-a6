#include "bank.h"

using namespace std;

// The Bank is a monitor, which behaves like a server, that manages student-account information for all students.
Bank::Bank ( unsigned int numStudents ) : numStudents(numStudents) {

    balance = new unsigned int[numStudents];
    accountWait = new uCondition[numStudents];

    // Each student’s account initially starts with a balance of $0.
    for ( unsigned int i=0; i < numStudents; i++ ) {
        balance[i]=0;
    }
    
}

Bank::~Bank () {

    delete [] balance;
    delete [] accountWait;

}

// The parent calls deposit to endow gifts to a specific student.
void Bank::deposit( unsigned int id, unsigned int amount ) {

    balance[id] += amount;

    while(!accountWait[id].empty()) {
        accountWait[id].signal();
    }

}

void Bank::withdraw( unsigned int id, unsigned int amount ) {

    // The courier waits until enough money has been deposited, which may require multiple deposits.
    while (balance[id] < amount ) {
        accountWait[id].wait();
    }

    balance[id]-=amount;

}