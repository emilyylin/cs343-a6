#include "groupoff.h"

Groupoff::Groupoff ( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : 
    printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {
        currStudent=0;
        giftCards.resize(numStudents);
} // Groupoff

void Groupoff::main() {

    printer.print(Printer::Groupoff, 'S'); // start groupoff

    // accepting a call from all students to obtain a future gift-card
    for (unsigned int i = 0 ; i < numStudents; i++ ) {
        _Accept (giftCard);
    }

    //loops until all the future gift-cards are assigned a real WATCard
    for (unsigned int i = 0 ; i < numStudents; i++ ) {
        
        _Accept(~Groupoff) {
            break; //or loops until call to destructor

        } _Else {
            // yield before assigning giftcard
            yield(groupoffDelay);

            // assign each future giftcard a real watcard
            WATCard * card = new WATCard();

            // creates and puts a real WATCard with value SodaCost
            card->deposit(sodaCost);

            // puts into random future gift-card  
            unsigned int randStudent = prng(giftCards.size());
            printer.print(Printer::Groupoff, 'D', sodaCost);

            // deliver the card and then remove it
            giftCards[randStudent].delivery(card);
            delete card;
            giftCards.erase(giftCards.begin()+randStudent);
        } // accept
    } // for
    printer.print(Printer::Groupoff, 'F'); // terminate
} // main()

WATCard::FWATCard Groupoff::giftCard() {
    return giftCards[currStudent];
} // giftcard()
