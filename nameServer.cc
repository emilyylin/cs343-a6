#include <nameServer.h>

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ):
    printer(prt), numVendingMachines(numVendingMachines) {
        vendingMachineList = new VendingMachine*[numVendingMachines];
        assignedMachines = new unsigned int[numStudents];
        currMachine = 0;
}

void NameServer::VMregister (VendingMachine * vendingmachine){

}

VendingMachine * NameServer::getMachine( unsigned int id ) {

}

VendingMachine ** NameServer::getMachineList() {
    
}

void NameServer::main() {
    //logically distribute students evenly across the vending machines
    for (unsigned int i =0; i < numStudents; i++){
        assignedMachines[i] = i % numVendingMachines;
    }
}