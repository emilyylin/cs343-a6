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
    } // for (numFlavors)
    
    //begins by registering with the name server
    nameServer.VMregister(this);
} //VendingMachine()

void VendingMachine::main () {

    while (true) {
        // Use concurrent exceptions to raise Funds, Stock or Free on the correct task.
        try {
            _Accept(~VendingMachine) {
                break;  //skip to finished
            } or _Accept(inventory) {
                //start reloading by truck
                printer.print(Printer::Vending, id, 'r');

                //don't accept buys during restocking
                _Accept (restocked) {
                    //finish reloading by truck
                    printer.print(Printer::Vending, id, 'R'); 
                } // _Accept

            } or _Accept (buy) {}

        } catch (uMutexFailure::RendezvousFailure &) {
            //all exceptions go to student
        } //try
    } //while (true)

    printer.print(Printer::Vending, id, 'F'); //finish vending machine
} //main()

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
        } // if (prng(1,5)==1)
    } // if
    printer.print(Printer::Vending, id, 'B', flavour, sodasInStock[flavour]); //student bought a soda
} // buy ()

// the truck calls restocked to indicate the operation is complete
void VendingMachine::restocked () {}

// The truck calls inventory to return a pointer to an array containing the amount each kind of soda currently in the vending machine.
unsigned int * VendingMachine::inventory () {
    return sodasInStock;
} // inventory

// The cost member returns the cost of purchasing a soda for this machine
_Nomutex unsigned int VendingMachine::cost() const {
    return sodaCost;
} // cost

// The getId member returns the identification number of the vending machine.
_Nomutex unsigned int VendingMachine::getId() const {
    return id;
} //getid