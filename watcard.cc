#include "watcard.h"

WATCard::WATCard() {
    balance = 0; //initialize balance to 0
} //WatCard()

void WATCard::deposit( unsigned int amount ){
    balance += amount; // add the amount from the balance
} //deposit()

void WATCard::withdraw( unsigned int amount ){
    balance -= amount; // subtract the amount from the
} //withdraw()

unsigned int WATCard::getBalance(){
    return balance; // return the current balance
} //getBalance()