#ifndef PRINTER_H
#define PRINTER_H

using namespace std;
#include <map>
#include <variant>

_Monitor Printer {

	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
  public:
	
	enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
	~Printer(); // destructor
	void print( Kind kind, char state );
	void print( Kind kind, char state, unsigned int value1 );
	void print( Kind kind, char state, unsigned int value1, unsigned int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );
  private:
	
	struct StateData{
		Kind kind;
		char state;
	};
	struct StateValue1Data{
		Kind kind;
		char state;
		unsigned int lid;
		unsigned int value1;
	};
	struct StateValue2Data{
		Kind kind;
		char state;
		unsigned int lid;
		unsigned int value1;
		unsigned int value2;
	};
	map<Kind, variant<StateData, StateValue1Data, StateValue2Data>> dataBuffer;
};
#endif