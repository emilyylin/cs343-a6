#include "groupoff.h"

/*
The groupoff prints the following information
State Meaning Additional Information
S starting
D g deposit gift amount of gift g
F finished
*/

void Groupoff::main() {

    printer.print(Printer::Groupoff, 'S')

    // accepting a call from all students to obtain a future gift-card
    for (unsigned int i = 0 ; i < numStudents; i++ ) {
        _Accept (giftcard);
    }

    //loops until all the future gift-cards are assigned a real WATCard
    for (unsigned int i = 0 ; i < numStudents; i++ ) {
        
        _Accept(~Groupoff) {
            break; //or loops until call to destructor

        } _Else {

            yield(groupoffDelay);

            //assign each future giftcard a real watcard
            Watcard * card = new WATCard();

            //create a gift card from groupoff with value of sodacost
            printer.print(Printer::Groupoff, 'G', sodaCost)
            card->deposit(sodaCost);

            // periodically creates and puts a real WATCard with value SodaCost into a random future gift-card
            
            


        }
    }

}

Groupoff::Groupoff ( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : 
    printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {

}

Groupoff::~Groupoff () {

}


WATCard::FWATCard Groupoff::giftCard() {

    return giftcard;
}