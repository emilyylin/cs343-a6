#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"

_Task Truck {
	Printer & printer;
	NameServer & nameServer;
	BottlingPlant & plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int cargo[BottlingPlant::Flavours::NUM_OF_FLAVOURS] = {0};
	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
	~Truck();
};