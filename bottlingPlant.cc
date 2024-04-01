#include "bottlingPlant.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
        printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
        maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), 
        timeBetweenShipments(timeBetweenShipments) {}

~BottlingPlant::BottlingPlant() {
    //TODO: print finished
}

void BottlingPlant::getShipment( unsigned int cargo[] ){
    //bottling plant closes down is there is no stock
    if(maxStockPerFlavour == 0){
        _Throw Shutdown();
    } 
    
    // else copy the shipment into the cargo
    for (int i =0; i < NUM_OF_FLAVOURS; i++){
        cargo[i] = shipment[i];
    }
}

void BottlingPlant::main(){
    //begin by creating a truck, performing a production run, and waiting for the truck to pickup the production run. 
    Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    //TODO: print START

    for(;;) {
        //bottling plant yields between production runs
        yield(timeBetweenShipments);

        //start a production run
        unsigned int produced = 0;
        for(unsigned int i =0; i < NUM_OF_FLAVOURS; i ++){
            unsigned int bottles = prng(0, maxShippedPerFlavour);
            shipment[i] = bottles;
            produced += bottles;
        }
        //TODO: print generating soda

        // don't start another run until truck picks up the current run
        _Accept(getShipment) {
            //TODO: print shipment picked up  by truck
        } or _Accept(~BottlingPlant) {
            _Accept(getShipment) {              // let truck finish
                _Resume Shutdown() _At truck;   // resume the exception at the truck which will stop when it catches it
            }
            break;
        }
    }
}