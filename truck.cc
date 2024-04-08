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
    
    printer.print(Printer::Truck, 'S'); // starting
    unsigned int currVM = 0; // keep track of the current vending machine
   
    // the truck begins by obtaining the location of each vending machine from the nameserver
    VendingMachine ** vendingMachines = nameServer.getMachineList();

    try {  
        //_Enable{
        for (;;) {
            yield(prng(1,10)); // yield to get coffee
            
            // try to get a shippment
            _Enable{
                plant.getShipment(cargo);     
            }

            unsigned int totalSodas = 0;        //any soda still on the truck is thrown away, set to 0 
            
            //count total sodas from shipment
            for (unsigned int i = 0; i < BottlingPlant::NUM_OF_FLAVOURS; i++){
                totalSodas += cargo[i];
            }
            printer.print(Printer::Truck, 'P', totalSodas);

            // until truck has made a complete cycle of all the vending machines
            for (unsigned int i = 0; i < numVendingMachines; i++) {
                //loop until there is no more soda
                if (totalSodas == 0) {
                    break;
                }

                //start from vending machine after last machine the truck restocked
                VendingMachine * machine = vendingMachines[currVM];

                printer.print(Printer::Truck, 'd', machine->getId(), totalSodas);

                // call inventory to get each kind of soda currently in machine
                unsigned int *currStock = machine->inventory();

                unsigned int unreplenished = 0;
                for (unsigned int j = 0; j < BottlingPlant::NUM_OF_FLAVOURS; j++) {
                    
                    //check if truck has enough stock to top up
                    unsigned int toTopUp = maxStockPerFlavour - currStock[j];

                    if (cargo[j] < toTopUp) {
                        //fill up as many bottles as it has
                        toTopUp = cargo[j];
                        unreplenished += toTopUp;
                    }

                    cargo[j]-=toTopUp;
                    currStock[j]+=toTopUp;
                    totalSodas -= toTopUp;

                } 

                // if there are more than 0 unreplenished bottles, print
                if (unreplenished > 0) {
                    printer.print(Printer::Truck, 'U', machine->getId(), unreplenished);
                }
                
                // complete the delivery and notify the machine
                printer.print(Printer::Truck, 'D', machine->getId(), totalSodas);   //todo: replace total sodas w total amt remaining
                machine->restocked();
                
                currVM = (currVM+1)%numVendingMachines; // increment next vending machine

                //flat tire 
                if (prng(1,100)==1) {
                    printer.print(Printer::Truck, 'W');
                    yield(10);
                }
            }
        }
    // when the plant shuts down, exit
    } catch (BottlingPlant::Shutdown &) {}
    printer.print(Printer::Truck, 'F'); // finish
}