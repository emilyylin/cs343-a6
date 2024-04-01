#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
    printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {}

void VendingMachine::main(){

}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ){

}

void VendingMachine::restocked(){

}