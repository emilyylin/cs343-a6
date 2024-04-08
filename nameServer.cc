#include "nameServer.h"

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ):
    printer(prt), numVendingMachines(numVendingMachines) {
        // initialize the vending machine list and the assigned machines to students
        vendingMachineList = new VendingMachine*[numVendingMachines];
        assignedMachines = new unsigned int[numStudents];

        // start the current machine at index 0
        currMachine = 0;
} // nameserver

NameServer::~NameServer(){
    printer.print(Printer::NameServer, 'F');
} // ~NameServer

void NameServer::VMregister (VendingMachine * vendingmachine){
    //register vending machine
    vendingMachineList[currMachine] = vendingmachine;
    printer.print(Printer::NameServer, 'R', currMachine);
    currMachine++; //increment for the next registration
} // VMregister

VendingMachine * NameServer::getMachine( unsigned int id ) {
    //get the current machine
    unsigned int currMachine = assignedMachines[id];
    VendingMachine * vendingMachine = vendingMachineList[currMachine];
    printer.print(Printer::NameServer, 'N', id, currMachine); // new vending machine

    // update the next machine
    unsigned int nextMachine = (currMachine + 1) % numVendingMachines;
    assignedMachines[id] = nextMachine;

    // return the machine
    return vendingMachine;
}  // getMachine

VendingMachine ** NameServer::getMachineList() {
    return vendingMachineList; // return the current list of vending machines
}

void NameServer::main() {
    // logically distribute students evenly across the vending machines in a RR fashion
    for (unsigned int i =0; i < numStudents; i++){
        assignedMachines[i] = i % numVendingMachines;
    } // for

    printer.print(Printer::NameServer, 'S'); // start nameserver

    for (;;) {
        //wait for call to destructor to terminate
        _Accept(~NameServer) {
            break;
        // once all the machines have been created
        } or _When (currMachine == numVendingMachines) _Accept(getMachine || getMachineList);
        // if the machines are not all registered, only let registration happen
        or _When (currMachine < numVendingMachines) _Accept(VMregister);
    } // for
} // main