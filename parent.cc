#include <uPRNG.h>
#include "parent.h"

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) :
    printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

Parent::~Parent() {
    printer.print(Printer::Parent, 'F');
} // ~Parent

void Parent::main() {
    //start
    printer.print(Printer::Parent, 'S');

    //loop check
    for (;;) {
        _Accept(~Parent) { //parent checks for a call to its destructor to know when to terminate
            break;
        } _Else { //terminating else 
            yield(parentalDelay); //first yield
            
            // pick a random student and a random gift amount
            int student = prng(numStudents);
            int giftAmount = prng(1,3);
            
            // deposit the money to the student's bank account
            printer.print(Printer::Parent,'D', student, giftAmount);
            bank.deposit(student, giftAmount);
        } // accept
    } // for
} // main