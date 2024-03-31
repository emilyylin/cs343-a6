#include "nameServer.h"

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ):
    printer(prt), numVendingMachines(numVendingMachines) {
        vendingMachineList = new VendingMachine*[numVendingMachines];
        assignedMachines = new unsigned int[numStudents];
        currMachine = 0;
}

void NameServer::VMregister (VendingMachine * vendingmachine){
    //TODO: print registration
    vendingMachineList[currMachine] = vendingmachine;
    currMachine++; //increment for the next registration
}

VendingMachine * NameServer::getMachine( unsigned int id ) {
    //get the current machine
    unsigned int currMachine = assignedMachines[id];
    //TODO: print new vending machine
    VendingMachine * vendingMachine = vendingMachineList[currMachine];

    // update the next machine
    unsigned int nextMachine = (currMachine + 1) % numVendingMachines;
    assignedMachines[id] = nextMachine;

    return vendingMachine;
}

VendingMachine ** NameServer::getMachineList() {
    return vendingMachineList;
}

void NameServer::main() {
    //logically distribute students evenly across the vending machines in a RR fashion
    for (unsigned int i =0; i < numStudents; i++){
        assignedMachines[i] = i % numVendingMachines;
    }

    //TODO: print start

    for (;;) {
        //wait for call to destructor to terminate
        _Accept(~NameServer) {
            //TODO: print finish
            break;
        } _Else {
            // when all the are registered, let a  student get a machine or a truck to get machine list
            _When (currMachine == numVendingMachines) _Accept(getMachine || getMachineList);
            // if the machines are not all registered, only let registration happen
            or _When (currMachine < numVendingMachines) _Accept(VMregister);
        }
    }
}