#include "truck.h"
#include "vendingMachine.h"

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ):
    printer(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {}

                // The truck uses this information to transfer as much of its stock as fits into the machine;
                // for each kind of soda, no more than MaxStockPerFlavour per flavour can be added to a machine
                // If the truck cannot top-up a particular flavour because there is insufficient stock, it transfers as many bottles as it has (which could be 0)
                // After transferring new soda into the machine by directly modifying the array passed from inventory  
                
void Truck::main() {
    // TODO: print start

    // the truck begins by obtaining the location of each vending machine from the nameserver
    VendingMachine ** vendingMachines = nameServer.getMachineList();

    for (;;) {
        yield(prng(1,10)); // yield to get coffee
        
        // try to get a shippment
        try {
            _Enable{
                plant.getShipment(cargo);
            }
        // when the plant shuts down, exit
        } catch (BottlingPlant::Shutdown &){
            break;
        }
    }
}