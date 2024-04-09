#include "student.h"

using namespace std;

/*
State Meaning Additional Information
S f,b starting favourite soda f, number of bottles b to purchase
V v selecting vending machine vending machine v selected
G f,b gift-card soda soda flavour f purchased, giftcard balance b
B f,b bought soda soda flavour f purchased, WATCard balance b
a f,b free soda, advertisement soda flavour f purchased, giftcard balance b
A f,b free soda, advertisement soda flavour f purchased, WATCard balance b
X did not watch advertisement
L WATCard lost
F finished
*/

void Student::main () {
    // start by selecting a random number of bottles to purchase
    unsigned int numBottles = prng(1,maxPurchases);
    // select a random favourite flavour
    BottlingPlant::Flavours faveFlavour = static_cast<BottlingPlant::Flavours>(prng(4));

    printer.print(Printer::Student, id, 'S', faveFlavour, numBottles);

    // create a watcard from watcardoffice with a $5 balance
    WATCard::FWATCard watcard = cardOffice.create(id, 5);
    //create a gift card from groupoff with value of sodacost
    WATCard::FWATCard giftcard = groupoff.giftCard();

    //card used to make the payment
    WATCard* card = nullptr;

    //obtain location of a vending machine from the nameserver
    VendingMachine * v = nameServer.getMachine(id);
    printer.print(Printer::Student, id, 'V', v->getId());
    
    //terminate after purchasing selected random number of bottles of fave flavour
    for(unsigned int i =0; i < numBottles; i++){
        // before each attempt to purchase a soda, yield
        yield(prng(1,10));

        for(;;){ // keep looping until a successful purchase
            // wait for money to be transferred from either watcard or giftcard
            try{
                _Select(giftcard){ // use giftcard first
                    try{
                        card = giftcard();
                        v->buy(faveFlavour,*card);
                        printer.print(Printer::Student, id, 'G', faveFlavour, card->getBalance());
                        // reset to prevent further usage
                        giftcard.reset();
                        //delete giftcard(); // this breaks the code
                        break; // break out of the for loop, start next purchase
                    } catch (VendingMachine::Free &){
                        printer.print(Printer::Student, id, 'a', faveFlavour, card->getBalance());
                        throw VendingMachine::Free();
                    } //try

                } or _Select(watcard){
                    try {
                        card = watcard();
                        v->buy(faveFlavour,*card);
                        printer.print(Printer::Student, id, 'B', faveFlavour, card->getBalance());
                        break;  // break out of the for loop, start next purchase
                    } catch (VendingMachine::Free &) {
                        printer.print(Printer::Student, id, 'A', faveFlavour, card->getBalance());
                        throw VendingMachine::Free();
                    } //try
                } //_select      
            } catch(WATCardOffice::Lost &){
                printer.print(Printer::Student, id, 'L');
                watcard.reset();
                //create a new WATCard from the WATCardOffice with a $5 balance
                watcard = cardOffice.create(id, 5);
                //d re-attempt to purchase a soda without yielding as a purchase has not occurred

            } catch(VendingMachine::Free &){
                //there is a 50% chance the student watches add
                if (prng(2)==1) {
                    //yields 4 times
                    yield(4);
                } else {
                    printer.print(Printer::Student, id, 'X');
                }
                break;

            // transfers the current vending-machine soda-cost plus $5 to their WATCard via the WATCard office
            } catch(VendingMachine::Funds &){
                watcard = cardOffice.transfer(id, v->cost()+5, watcard());
                break;

            // obtain a new vending machine from the name server and attempt another purchase
            } catch (VendingMachine::Stock &){
                v = nameServer.getMachine(id);
                printer.print(Printer::Student, id, 'V', v->getId());
            } //try

        } // for(;;)
    } // for(i<numBottles)

    printer.print(Printer::Student, id, 'F');

    // delete watcard
    try{
        delete watcard();
    } catch (WATCardOffice:: Lost&){
        printer.print(Printer::Student, id, 'L');
    } // try

} // main


// id in the range [0, NumStudents) for identification.
Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff, unsigned int id, unsigned int maxPurchases ) : 
printer(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases){}

