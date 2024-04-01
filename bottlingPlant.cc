#include "bottlingPlant.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
        printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
        maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), 
        timeBetweenShipments(timeBetweenShipments) {}

BottlingPlant::~BottlingPlant() {
    printer.print(Printer::BottlingPlant, 'F');
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

    //start
    printer.print(Printer::BottlingPlant, 'S');

    for(;;) {
        //bottling plant yields between production runs
        yield(timeBetweenShipments);

        //start a production run
        unsigned int produced = 0;
        for(unsigned int i =0; i < NUM_OF_FLAVOURS; i ++){
            //generate soda
            unsigned int bottles = prng(0, maxShippedPerFlavour);
            shipment[i] = bottles;
            produced += bottles;
        }
        printer.print(Printer::BottlingPlant, 'G', produced);   // print bottles generated in production

        // don't start another run until truck picks up the current run
        _Accept(getShipment) {
            //shipment picked up  by truck
            printer.print(Printer::BottlingPlant, 'P');
        } or _Accept(~BottlingPlant) {
            _Accept(getShipment) {              // let truck finish
                _Resume Shutdown() _At truck;   // resume the exception at the truck which will stop when it catches it
            }
            break;
        }
    }
}