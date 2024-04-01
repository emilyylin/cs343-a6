#include "bottlingPlant.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
        printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
        maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), 
        timeBetweenShipments(timeBetweenShipments) {}

void BottlingPlant::getShipment( unsigned int cargo[] ){
//the shipment is copied into the cargo array passed by the truck.
//propagates the exception Shutdown if the bottling plant is closing down, and no shipment is copied into the cargo array passed by the truck.
}

void BottlingPlant::main(){

    //begin by creating a truck, performing a production run, and waiting for the truck to pickup the production run. 
    Truck truck(printer, nameServer, this, numVendingMachines, maxStockPerFlavour);

    //

    //The truck then distributes these bottles to initialize the registered vending machines. 
    //To simulate a production run of soda, the bottling plant yields for TimeBetweenShipments times (not random). 
    //The bottling plant does not start another production run until the truck has picked up the current run. 

}