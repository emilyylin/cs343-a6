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

/*
A courier prints the following information:
S starting
t s,a start funds transfer student s requesting transfer, amount a of transfer
L s lost WATCard card student s requesting transfer
T s,a complete funds transfer student s requesting transfer, amount a of transfer
F finished
*/

void WATCardOffice::Courier::main() {

    //goes through all of the jobs in the queue
    for (;;) {
        WatCardOffice::Job * job = cardOffice.requestWork();
        if (job == nullptr) {
            break;              // break out of the for loop if no work available (blocks)
        } 

        // start funds transfer
        printer.print(Printer::Courier, id, 't', job->sid, job->amouont);

        // withdraw to transfer money for student
        bank.withdraw(job->sid, job->amount);

        // updates the student's watcard
        job->card->deposit(job->amount);
        
        // 1 in 6 chance that card is lost
        if (prng(6) == 0) {

            printer.print(Printer::Courier, id, 'L', job->sid);

            // exception WATCardOffice::Lost is inserted into the future
            job->result.exception(new Lost)

            // the current watcard is deleted
            delete job->card;

        } else {
            
            //work call complete
            printer.print(Printer::Courier, id, 'T', job->sid, job->amount);

        }

        delete job;

    } 
    
    //finish
    printer.print(Printer::Courier, id, 'F');
}

void WATCardOffice::main() {
    printer.print(Printer::WATCArdOffice, 'S');
    // complete jobs
    for (;;){
        _When (!jobs.empty()) _Accept (requestWork) { // while there are still jobs, accept work
            printer.print(Printer::WATCardOffice, 'W'); //request work call complete
        } or _Accept (~WatCardOffice()) { // finished work when jobs list is empty
            break;
        } or Accept(transfer || create);
    }
}

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) : 
    printer(printer), bank(bank), numCouriers(numCouriers){
    // initially creates a fixed size courier pool with num couriers to communicate with the bank
    couriers = new Courier* [numCouriers];
    for (unsigned int i = 0; i < numCouriers; i++){
        printer.print(Printer::Courier, i, 'S');
        couriers[i] = new Courier();
    }

}

WatCardOffice::~WatCardOffice() {
    printer.print(Printer::WATCardOffice, id, 'F');
    // delete couriers
    for (unsigned int i =0; i < numCouriers; i++){
        delete couriers[i];
    }
    delete[] couriers;
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    // create a real watcard with an initial balance
    WATCard *card = new WATCard();
    // create a new job and add to queue of jobs
    Job *job = new Job(Args(sid, amount, card));
    jobs.push(job);
    printer.print(Printer::WatCardOffice, 'C', sid, amount);
    
    // a future watcard is returned and sufficient funds are obtained from the bank via a courier 
    return job->result;
}

// a future watcard is returned and sufficient funds are obtained from the bank
// transfer funds from a student's bank account to watcard by sending a request through a courier to the bank
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    //create a new job and add to queue of jobs
    Job *job = new Job(Args(sid, amount, card))
    jobs.push(job);
    printer.print(Printer::WatCardOffice, 'T', sid, amount);
    
    // a future watcard is returned and sufficient funds are obtained from the bank via a courier 
    return job->result;
}

// called by courier task
WatCardOffice::Job * WATCardOffice::requestWork(){
    // blocks until a job request is ready and then receieves the next job request as the result of the call
    if (jobs.empty()) return nullptr;
    return jobs.pop();
}