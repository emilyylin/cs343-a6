#include <uPRNG.h>
#include "parent.h"

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) :
    printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

Parent::~Parent() {
    printer.print(Printer::Parent, 'F');
}

void Parent::main() {
    //start
    printer.print(Printer::Parent, 'S');

    //loop check
    for (;;) {
        _Accept(~Parent) { //parent checks for a call to its destructor to know when to terminate
            break;
        } _Else { //terminating else 
            //first yield
            yield(parentalDelay);
            
            //transfer random money [1,3]  to random student [0, numStudents)
            int student = prng(numStudents);
            int giftAmount = prng(1,3);
            printer.print(Printer::Parent,'D', student, giftAmount);
            bank.deposit(student, giftAmount);
        }
    }
}