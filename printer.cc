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
    pair<Kind, unsigned int> key = make_pair(kind,0);           //set lid=0 by default
    flush(key);                                                 // flush the current buffer
    dataBuffer.insert({key, StateData(state)});                 // insert the data
}

void Printer::print( Kind kind, char state, unsigned int value1 ){
    pair<Kind, unsigned int> key = make_pair(kind,0);           //set lid=0 by default
    flush(key);                                                 // flush the current buffer
    dataBuffer.insert({key, StateData(state,value1)});          // insert the data
}

void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ){
    pair<Kind, unsigned int> key = make_pair(kind,0);           //set lid=0 by default
    flush(key);                                                 // flush the current buffer
    dataBuffer.insert({key, StateData(state,value1,value2)});   // insert the data
}

void Printer::print( Kind kind, unsigned int lid, char state ){
    pair<Kind, unsigned int> key = make_pair(kind,lid);         // make a key with the kind and lid
    flush(key);                                                 // flush the current buffer
    dataBuffer.insert({key, StateData(state)});                 // insert the data
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ){
    pair<Kind, unsigned int> key = make_pair(kind,lid);          // make a key with the kind and lid
    flush(key);                                                  // flush the current buffer
    dataBuffer.insert({key, StateData(state,value1)});           // insert the data
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ){
    pair<Kind, unsigned int> key = make_pair(kind,lid);         // make a key with the kind and lid
    flush(key);                                                 // flush the current buffer
    dataBuffer.insert({key, StateData(state,value1,value2)});   // insert the data
}

void Printer::flush(pair<Kind,unsigned int> keyCheck){
    //check for existence in buffer, if it doesn't exist, return
    if(!dataBuffer.count(keyCheck)){return;}

    // flush from parent to bottling plant (0 to 5)
    for (unsigned int kind = 0; kind < 5; kind++){
        //check if the kind exists in the map
        pair<Kind, unsigned int> key = make_pair(static_cast<Kind>(kind),0);
        if(dataBuffer.count(key)>0){
            dataBuffer[key].print();
        }
        if (kind!=4){cout << "\t";} // print a tab if not last column
    }

    // flush the data with lids
    for (unsigned int lid = 0; lid < numStudents; lid++){
        // make a key with the student kind and lid
        pair<Kind, unsigned int> key = make_pair(Student,lid);
        //check for the key existence in the buffer, if it exists, print the information
        if(dataBuffer.count(key)>0){
            dataBuffer[key].print();
        }
        if(lid!=numStudents-1){cout<<"\t";} // print a tab if not last column
    }

    for(unsigned int lid =0; lid < numVendingMachines; lid++){
        // make a key with the vending kind and lid
        pair<Kind, unsigned int> key = make_pair(Vending,lid);
        //check for the key existence in the buffer, if it exists, print the information
        if(dataBuffer.count(key)>0){
            dataBuffer[key].print();
        }
        if(lid!=numVendingMachines-1){cout<<"\t";} // print a tab if not last column
    }

    for(unsigned int lid =0; lid < numCouriers; lid++){
        // make a key with the courier kind and lid
        pair<Kind, unsigned int> key = make_pair(Courier,lid);
        //check for the key existence in the buffer, if it exists, print the information
        if(dataBuffer.count(key)>0){
            dataBuffer[key].print();
        }
        if(lid!=numCouriers-1){cout<<"\t";} // print a tab if not last column
    }
    cout << endl;
    //clear the buffer
    dataBuffer.clear();
}