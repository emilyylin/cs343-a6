#include "nameServer.h"

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ):
    printer(prt), numVendingMachines(numVendingMachines) {
        printer.print(Printer::NameServer, 'S'); // start nameserver
        // initialize the vending machine list and the assigned machines to students
        vendingMachineList = new VendingMachine*[numVendingMachines];
        assignedMachines = new unsigned int[numStudents];

        // logically distribute students evenly across the vending machines in a RR fashion
        for (unsigned int i =0; i < numStudents; i++){
            assignedMachines[i] = i % numVendingMachines;
        } // for
        currMachine = 0;  // start the current machine at index 0
} // nameserver

NameServer::~NameServer(){
    printer.print(Printer::NameServer, 'F'); // finish nameserver

    // deallocate the list of vending machines and assigned machines
    delete [] vendingMachineList;
    delete [] assignedMachines;
} // ~NameServer

void NameServer::VMregister (VendingMachine * vendingmachine){
    //register vending machine
    vendingMachineList[currMachine] = vendingmachine;
    printer.print(Printer::NameServer, 'R', currMachine);
    currMachine++; //increment for the next registration
} // VMregister

VendingMachine * NameServer::getMachine( unsigned int id ) {
    //get the current machine
    unsigned int machine = assignedMachines[id];
    VendingMachine * vendingMachine = vendingMachineList[machine];
    printer.print(Printer::NameServer, 'N', id, machine); // new vending machine

    // update the next machine
    unsigned int nextMachine = (machine + 1) % numVendingMachines;
    assignedMachines[id] = nextMachine;

    // return the machine
    return vendingMachine;
}  // getMachine

VendingMachine ** NameServer::getMachineList() {
    return vendingMachineList; // return the current list of vending machines
} // getMachineList

void NameServer::main() {
    for (;;) {
        _Accept(~NameServer) { //wait for call to destructor to terminate
            break;
        // once all the machines have been created, let getMachine and getMachineList happen
        } or _When (currMachine == numVendingMachines) _Accept(getMachine || getMachineList);
        // if the machines are not all registered, only let registration happen
        or _When (currMachine < numVendingMachines) _Accept(VMregister);
    } // for
} // main