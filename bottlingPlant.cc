#include <uPRNG.h>
#include "bottlingPlant.h"
#include "truck.h"

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
	unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
        printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), 
        maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), 
        timeBetweenShipments(timeBetweenShipments) {}

BottlingPlant::~BottlingPlant() {
    printer.print(Printer::BottlingPlant, 'F');
} // ~BottlingPlant

void BottlingPlant::getShipment( unsigned int cargo[] ){
    // copy the shipment into the cargo
    for (int i =0; i < NUM_OF_FLAVOURS; i++){
        cargo[i] = shipment[i];
    } // for
} // getshipment

void BottlingPlant::main(){
    //begin by creating a truck, performing a production run, and waiting for the truck to pickup the production run. 
    Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    printer.print(Printer::BottlingPlant, 'S');  //start bottling plant

    for(;;) {
        yield(timeBetweenShipments); //bottling plant yields between production runs

        //start a production run
        unsigned int produced = 0;
        for(unsigned int i =0; i < NUM_OF_FLAVOURS; i ++){
            //generate soda
            unsigned int bottles = prng(0, maxShippedPerFlavour);

            // add to the shipment and update the number of bottles produced
            shipment[i] = bottles;
            produced += bottles;
        } // for
        printer.print(Printer::BottlingPlant, 'G', produced);   // print bottles generated in production

        // don't start another run until truck picks up the current run
        _Accept(getShipment) {
            printer.print(Printer::BottlingPlant, 'P');  //shipment picked up  by truck
        } or _Accept(~BottlingPlant) {
            _Accept(getShipment) {_Resume Shutdown() _At truck;}   // resume the exception at the truck which will stop when it catches it
            break;
        } // accept
    } // for
} // main