#include <iostream>
#include "printer.h" 

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) :
    numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers){
    // print headers
    cout << "Parent" << "\t";
    cout << "Gropoff" << "\t"; // there's a typo in the assignment description
    cout << "WATOff" << "\t";
    cout << "Names" << "\t";
    cout << "Truck" << "\t";
    cout << "Plant";

    // print students
    for(unsigned int i =0; i < numStudents; i++){
        cout << "\t" << "Stud" << i;
    }
    // print vending machiines
    for (unsigned int i = 0; i < numVendingMachines; i++){
        cout << "\t" << "Mach" << i;
    }
    //print couriers
    for (unsigned int i=0; i < numCouriers; i++){
        cout << "\t" << "Cour" << i;
    }
    cout << endl;

    //print separators
    int totalSeparators = 6 + numStudents+numVendingMachines+numCouriers;
    cout << "*******";
    for(int i =0; i < totalSeparators; i++){
        cout << "\t" << "*******";
    }
    cout << endl;
}

Printer::~Printer() {
    //print ending header
    cout << "***********************";
}

void Printer::StateData::print(){
    cout << state; 
    if (value1!=-1) {cout << value1;} 
    if (value2!=-1) {cout << "," << value2;}
}


void Printer::print( Kind kind, char state ){
    pair<Kind, unsigned int> key = make_pair(kind,0);
    flush(key);
    dataBuffer.insert({key, StateData(state)});
}

void Printer::print( Kind kind, char state, unsigned int value1 ){

}

void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ){

}

void Printer::print( Kind kind, unsigned int lid, char state ){

}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ){

}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ){
}


void Printer::flush(pair<Kind,unsigned int> key){
    //check for existence in buffer
    if(!dataBuffer.count(key)){return;}

    // flush from parent to bottling plant (0 to 5)
    for (unsigned int kind = 0; kind < 5; kind++){
        //check if the kind exists in the map
    }

    // flush the data with lids
    unsigned int studentKind = 6;
    for (unsigned int lid = 0; lid < numStudents; lid++){
        // first check if the student kind is in the buffer
    }
}