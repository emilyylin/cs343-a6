#include "watcardOffice.h"

using namespace std;

/*
The WATCard office prints the following information:
State Meaning Additional Information
S starting
W request work call complete
C s,a create call complete student s, transfer amount a
T s,a transfer call complete student s, transfer amount a
F finished
*/


void WATCardOffice::Courier::main(WatCardOffice &cardOffice) {

    // wait for job
    for (;;) {
        WatCardOffice::Job * job = cardOffice.requestWork();
        
        if (job == NULL) {
            break;
            
        } else {
            
        }
    } 

    // ass soon as the request is satisfied (money is obtained), courier updates the student's watcard
    // there is a 1 in 6 chance (prng(6) == 0) a courier losts a student's watcard after the update
    // when the card is lost, exception WATCardOffice::Lost is inserted into the future
    // rather than making the future available, and the current watcard is deleted
    



    printer.print(Printer::Courier, id, 'S');

}

void WATCardOffice::main() {
    // complete jobs
    for (;;){
        _When (!jobs.empty()) _Accept (requestWork) { // while there are still jobs, accept work

        } or _Accept (~WatCardOffice())
    }
}

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) : 
    printer(printer), bank(bank), numCouriers(numCouriers){
    // initially creates a fixed size courier pool with num couriers to communicate with the bank
    couriers = new Courier* [numCouriers];
    
}

WatCardOffice::~WatCardOffice() {
    printer.print(Printer::Courier, id, 'F');
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    // create a real watcard with an initial balance
    WATCard *card = new WATCard();
    // create a new job and add to queue of jobs
    Job *job = new Job(Args(sid, amount, card));
    jobs.push(job);
    printer.print(Printer::Courier, id, 'C', sid, amount);
    
    // a future watcard is returned and sufficient funds are obtained from the bank via a courier 
    return job->result;
}

// called by student when their watcard indicates insufficient funds
// a future watcard is returned and sufficient funds are obtained from the bank
// transfer funds from a student's bank account to watcard by sending a request through a courier to the bank
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    //create a new job and add to queue of jobs
    Job *job = new Job(Args(sid, amount, card))
    jobs.push(job);
    printer.print(Printer::Courier, id, 'T', sid, amount);
    
    // a future watcard is returned and sufficient funds are obtained from the bank via a courier 
    return job->result;

}

// called by courier task
WatCardOffice::Job * WATCardOffice::requestWork(){
    // blocks until a job request is ready and then receieves the next job request as the result of the call
    if (jobs.empty()) return nullptr;
}