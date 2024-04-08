#ifndef BOTTLING_PLANT_H
#define BOTTLING_PLANT_H

#include "printer.h"
#include "nameServer.h"

_Task BottlingPlant {
    Printer & printer;
    NameServer & nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
	void main();
  public:
	enum Flavours { BLUES_BLACK_CHERRY, CLASSIC_CREAM_SODA, ROCK_ROOT_BEER, JAZZ_LIME, NUM_OF_FLAVOURS };	// flavours of soda
	_Exception Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
    ~BottlingPlant(); // destructor
	void getShipment( unsigned int cargo[] );
  private:
    unsigned int shipment[NUM_OF_FLAVOURS] = {0};
};
#endif
