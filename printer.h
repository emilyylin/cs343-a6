#ifndef PRINTER_H
#define PRINTER_H

using namespace std;
#include <map>
#include <iostream>

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
		char state;
		unsigned int value1 = -1;
		unsigned int value2 = -1;
		StateData(char state):state(state){};
		StateData(char state,unsigned int value1):state(state),value1(value1){};
		StateData(char state,unsigned int value1,unsigned int value2):state(state),value1(value1),value2(value2){};
		void print();
	};
	map<pair<Kind,unsigned int>, StateData> dataBuffer;
	void flush(pair<Kind,unsigned int> key);
};
#endif