#ifndef NAME_SERVER_H
#define NAME_SERVER_H

#include "printer.h"

_Task VendingMachine; // forward declaration

_Task NameServer {
    Printer& printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    unsigned int currMachine;
    unsigned int* assignedMachines;
    VendingMachine ** vendingMachineList;
	void main();
  public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id ) __attribute__(( warn_unused_result ));
	VendingMachine ** getMachineList() __attribute__(( warn_unused_result ));
};
#endif