#include "vendingMachine.h"
#include "watcard.h"
#include "nameServer.h"
#include "printer.h"

using namespace std;

// A vending machine’s function is to sell soda to students at some cost.
// id : range [0, NumVendingMachines) for identification
// sodaCost: the MSRP price for a bottle of soda
VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
    printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
    
    //starting (prints favorite soda f, number of bottles b to purchase)
    printer.print(Printer::Vending, 'S', id, sodaCost);

    // A new vending machine is empty (no stock)
    for ( unsigned int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i++ ) {
        sodasInStock[i] = 0;
    }
    
    //begins by registering with the name server
    nameServer.VMregister(this);

}

void VendingMachine::main () {
    
    bool restocking = false;

    while (true) {
        // Use concurrent exceptions to raise Funds, Stock or Free on the correct task.
        try {
            When(!restocking) _Accept(~VendingMachine) {
                //skip to finished
                break;

            } or _Accept(inventory) {
                restocking=true;

                //start reloading by truck
                printer.print(Printer::Vending, 'r');

                // The truck uses this information to transfer as much of its stock as fits into the machine;
                // for each kind of soda, no more than MaxStockPerFlavour per flavour can be added to a machine
                // If the truck cannot top-up a particular flavour because there is insufficient stock, it transfers as many bottles as it has (which could be 0)
                // After transferring new soda into the machine by directly modifying the array passed from inventory  

                //finish reloading by truck
                printer.print(Printer::Vending, 'R'); 


            // The vending machine cannot accept buy calls during restocking
            } or _When(!restocking) _Accept (buy) {

            } or _Accept(restocked) {
                restocking=false;
            }

        } catch () {

        }

    }

    //finished
    printer.print(Printer::Vending, 'F');
    
}

void VendingMachine::buy ( BottlingPlant::Flavours flavour, WATCard & card ) {

    //checks first if the student has sufficient funds to purchase the soda
    if (card.getBalance() < sodaCost ) {
        status = Funds;

    //checks second if the specified soda is available
    } else if (sodasInStock[flavour]==0) {
        status = Stock;

    } else {
        sodasInStock[flavour]--;

        // Once a purchase is possible, there is a 1 in 5 chance the soda is free
        // indicated by raising exception Free
        if ((rand() % 5)==1) {
            status = Free;

        } else {
            // the student’s WATCard is debited by the cost of a soda
            watcard.withdraw(sodaCost);
        }

    }
    

    //student bought a soda
    printer.print(Printer::Vending, 'B', flavour, amountRemaining);

}

// the truck calls restocked to indicate the operation is complete
void VendingMachine::restocked () {
}

// The truck calls inventory to return a pointer to an array containing the amount each kind of soda currently in the vending machine.
unsigned int * VendingMachine::inventory () {
    return sodasInStock;
}

// The cost member returns the cost of purchasing a soda for this machine
_Nomutex unsigned int VendingMachine::cost() const {
    return sodaCost;
}

// The getId member returns the identification number of the vending machine.
_Nomutex unsigned int VendingMachine::getId() const () {
    return id;
}