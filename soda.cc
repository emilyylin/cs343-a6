#include <uPRNG.h>
#include <iostream>
#include <string>
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardOffice.h"
#include "groupoff.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"
#include "student.h"

using namespace std;

int main( int argc, char * argv[] ) {
	int DefaultProcessors = 1;			// global defaults
	string DefaultConfigFile = "soda.config";
	int processors = DefaultProcessors;
	string configFile = DefaultConfigFile;

	struct cmd_error {};
	try {
		switch ( argc ) {
			case 4:
				if ( strcmp( argv[3], "d" ) != 0 ) {		// default ?
					processors = convert( argv[3] );
					if ( processors <= 0 ) throw cmd_error{};		// invalid ?
				} // if
			case 3:
				if ( strcmp( argv[2], "d" ) != 0 ) {		// default ?
					int seed = convert( argv[2] );
					if ( seed <= 0 ) throw cmd_error{};		// invalid ?
					set_seed(seed);
				} // if
			case 2:
				if ( strcmp( argv[1], "d" ) != 0 ) {		// default ?
					configFile = argv[1];
				} // if
			case 1:
				break;
			default:
				throw cmd_error{};
		}
	} catch( ... ) {									// catch any
		cerr << "Usage: " << argv[0]
			 << " [ config-file | 'd' (default " << DefaultConfigFile
             << ") [ seed (> 0) | 'd' (default random"
			 << ") [ processors (> 0) | 'd' (default " << DefaultProcessors
			 << ") ] ] ]" << endl;
		exit( EXIT_FAILURE );							// TERMINATE
	} // try

	uProcessor p[processors - 1]; // create more kernel thread

	//process config file
	ConfigParms config;
	processConfigFile(configFile, config);

	//create in order: printer, bank, parent, WATCard office, groupoff, name server, vending machines, bottling plant, and students. 
	Printer printer( config.numStudents, config.numVendingMachines, config.numCouriers );		// create printer
	Bank bank(config.numStudents); 																// create bank
	
	Parent parent(printer, bank, config.numStudents, config.parentalDelay);						// create parent
	
	WATCardOffice watcardOffice(printer, bank, config.numCouriers);								// create watcardoffice
	
	Groupoff groupoff(printer, config.numStudents, config.sodaCost, config.groupoffDelay);		// create groupoff
	
	NameServer nameServer(printer, config.numVendingMachines, config.numStudents);				// create name server
	
	VendingMachine *vendingMachines[config.numVendingMachines];									// create vending machines
	for (unsigned int i = 0; i < config.numVendingMachines; i++){
		vendingMachines[i] = new VendingMachine(printer, nameServer, i, config.sodaCost);
	}

	BottlingPlant *bottlingPlant = new BottlingPlant(printer, nameServer, 						// create bottling plant
	config.numVendingMachines, config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments);

	Student *students[config.numStudents];														// create students
	for (unsigned int i = 0; i < config.numStudents; i++){
		students[i] = new Student(printer, nameServer, watcardOffice, groupoff, i, config.maxPurchases);
	}

	// terminate after students have purchased their number of bottles
	delete bottlingPlant; 											// delete bottling plant
	for (unsigned int i =0; i < config.numVendingMachines; i++){	// delete vending machines
		delete vendingMachines[i];
	}
}