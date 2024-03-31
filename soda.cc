#include <uPRNG.h>
#include <iostream>
#include <string>

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

	//uProcessor p[processors - 1]; // create more kernel thread
}