#include "truck.h"
#include "vendingMachine.h"

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