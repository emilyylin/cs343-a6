#include "groupoff.h"

/*
The groupoff prints the following information
State Meaning Additional Information
S starting
D g deposit gift amount of gift g
F finished
*/

void Groupoff::main() {

    printer.print(Printer::Groupoff, 'S');

    // accepting a call from all students to obtain a future gift-card
    for (unsigned int i = 0 ; i < numStudents; i++ ) {
        _Accept (giftCard);
    }

    //loops until all the future gift-cards are assigned a real WATCard
    for (unsigned int i = 0 ; i < numStudents; i++ ) {
        
        _Accept(~Groupoff) {
            break; //or loops until call to destructor

        } _Else {

            yield(groupoffDelay);

            //assign each future giftcard a real watcard
            WATCard * card = new WATCard();

            //creates and puts a real WATCard with value SodaCost
            card->deposit(sodaCost);

            // puts into random future gift-card  
            unsigned int randStudent = prng(giftCards.size());
            printer.print(Printer::Groupoff, 'D', sodaCost);

            giftCards[randStudent].delivery(card);
            delete card;

            //remove giftcard
            giftCards.erase(giftCards.begin()+randStudent);
        }
    }

}

Groupoff::Groupoff ( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : 
    printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {
        currStudent=0;
        giftCards.resize(numStudents);
}

Groupoff::~Groupoff () {
    printer.print(Printer::Groupoff, 'F');
}


WATCard::FWATCard Groupoff::giftCard() {
    return giftCards[currStudent];
}