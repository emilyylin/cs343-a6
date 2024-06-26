#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "watcard.h"

_Task VendingMachine {

    Printer & printer;
    NameServer & nameServer;

	unsigned int sodasInStock[BottlingPlant::NUM_OF_FLAVOURS];
	
    unsigned int id;
    unsigned int sodaCost;
	void main();

  public:

	_Exception Free {};						// free, advertisement
	_Exception Funds {};					// insufficient funds
	_Exception Stock {};					// flavour out of stock

	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );

	void buy( BottlingPlant::Flavours flavour, WATCard & card );
	unsigned int * inventory() __attribute__(( warn_unused_result ));
	void restocked();
	
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;

};

#endif
