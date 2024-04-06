#include "truck.h"
#include "vendingMachine.h"

using namespace std;

/*
The truck prints the following information:
State Meaning Additional Information
S starting
P a picked up shipment total amount a of all sodas in the shipment
d v,r begin delivery to vending machine vending machine v, total amount remaining r in the shipment
U v,b unsuccessfully filled vending machine vending machine v, total number of bottles b not replenished
D v,r end delivery to vending machine vending machine v, total amount remaining r in the shipment
W wait for repair of flat tire
F finished
*/

// The truck uses this information to transfer as much of its stock as fits into the machine;
// for each kind of soda, no more than MaxStockPerFlavour per flavour can be added to a machine
// If the truck cannot top-up a particular flavour because there is insufficient stock, it transfers as many bottles as it has (which could be 0)
// After transferring new soda into the machine by directly modifying the array passed from inventory  


Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
    printer(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {

}



void Truck::main() {
    
    printer.print(Printer::Truck, 'S')

    // the truck begins by obtaining the location of each vending machine from the nameserver
    VendingMachine ** vendingMachines = nameServer.getMachineList();

    try {  
        for (;;) {
            yield(prng(1,10)); // yield to get coffee
            
            // try to get a shippment
            _Enable{
                plant.getShipment(cargo);     
            }

            //any soda still on the truck is thrown away 
            
            //vending machines are restocked in cyclic order starting at
            //the vending machine after the last machine the truck restocked
            // until there is no more soda on the truck or the truck has made a complete cycle of all the vending machines
            for (unsigned int i = 0; i < numVendingMachines; i++) {
                
            }

            


        }

    // when the plant shuts down, exit
    } catch (BottlingPlant::Shutdown &) {
    }

    _Accept(~Truck);
}