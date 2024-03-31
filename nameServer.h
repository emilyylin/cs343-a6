#include "printer.h"
#include "vendingMachine.h"

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
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id ) __attribute__(( warn_unused_result ));
	VendingMachine ** getMachineList() __attribute__(( warn_unused_result ));
};