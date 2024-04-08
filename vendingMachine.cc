#include "vendingMachine.h"
#include "watcard.h"
#include "nameServer.h"
#include "printer.h"

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
    printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
    
    printer.print(Printer::Vending, id, 'S', sodaCost); // start vending machine

    // A new vending machine is empty (no stock)
    for ( unsigned int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i++ ) {
        sodasInStock[i] = 0;
    } // for
    
    //begins by registering with the name server
    nameServer.VMregister(this);
}

void VendingMachine::main () {

    while (true) {
        // Use concurrent exceptions to raise Funds, Stock or Free on the correct task.
        try {
            _Accept(~VendingMachine) {
                //skip to finished
                break;

            } or _Accept(inventory) {
                //start reloading by truck
                printer.print(Printer::Vending, id, 'r');

                //don't accept buys during restocking
                _Accept (restocked) {
                    //finish reloading by truck
                    printer.print(Printer::Vending, id, 'R'); 
                }

            } or _Accept (buy) {}

        } catch (uMutexFailure::RendezvousFailure &) {
            //all exceptions go to student
        }
    }

    //finished
    printer.print(Printer::Vending, id, 'F');
}

void VendingMachine::buy ( BottlingPlant::Flavours flavour, WATCard & card ) {

    //checks first if the student has sufficient funds to purchase the soda
    if (card.getBalance() < sodaCost ) {
        throw VendingMachine::Funds();

    //checks second if the specified soda is available
    } else if (sodasInStock[flavour]==0) {
        throw VendingMachine::Stock();

    } else {
        sodasInStock[flavour]--;

        // Once a purchase is possible, there is a 1 in 5 chance the soda is free
        // indicated by raising exception Free
        if (prng(1,5)==1) {
             printer.print(Printer::Vending, id, 'A');
            throw VendingMachine::Free();
           

        } else {
            // the student’s WATCard is debited by the cost of a soda
            card.withdraw(sodaCost);
        } // if
    } // if
    //student bought a soda
    printer.print(Printer::Vending, id, 'B', flavour, sodasInStock[flavour]);

} // buy

// the truck calls restocked to indicate the operation is complete
void VendingMachine::restocked () {}

// The truck calls inventory to return a pointer to an array containing the amount each kind of soda currently in the vending machine.
unsigned int * VendingMachine::inventory () {
    return sodasInStock;
}

// The cost member returns the cost of purchasing a soda for this machine
_Nomutex unsigned int VendingMachine::cost() const {
    return sodaCost;
}

// The getId member returns the identification number of the vending machine.
_Nomutex unsigned int VendingMachine::getId() const {
    return id;
}