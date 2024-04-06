#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "watcard.h"

_Task VendingMachine {

    Printer & printer;
    NameServer & nameServer;

    unsigned int id;
    unsigned int sodaCost;
	void main();

  public:

	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// flavour out of stock

	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );

	void buy( BottlingPlant::Flavours flavour, WATCard & card );
	unsigned int * inventory() __attribute__(( warn_unused_result ));
	void restocked();
	
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;

};

#endif
