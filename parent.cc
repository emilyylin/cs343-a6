#include "parent.h"

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) :
    printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

Parent::~Parent() {
    //TODO: print finish
}

void main() {
    //TODO: print start
    for (;;) {
        _Accept(~Parent) { //parent checks for a call to its destructor to know when to terminate
            break;
        } _Else { //terminating else 
            //first yield
            yield(parentalDelay);
            //TODO: print deposit gift
            //transfer random money [1,3]  to random student [0, numStudents)
            bank.deposit(prng(numStudents), prng(1,3));
        }
    }
}