#include "watcard.h"

WATCard::WATCard() {
    balance = 0; //initialize balance to 0
}

void WATCard::deposit( unsigned int amount ){
    balance += amount; // add the amount from the balance
}

void WATCard::withdraw( unsigned int amount ){
    balance -= amount; // subtract the amount from the
}

unsigned int WATCard::getBalance(){
    return balance; // return the current balance
}