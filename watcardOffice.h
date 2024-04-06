#ifndef WATCARD_OFFICE_H
#define WATCARD_OFFICE_H

#include <queue>

#include "watcard.h"
#include "printer.h"
#include "bank.h"

using namespace std;

_Task WATCardOffice {

	struct Job {							// marshalled arguments and return future
		unsigned int sid, amount;
		WATCard * card;
		WATCard::FWATCard result;			// return future
		Job( unsigned int sid, unsigned int amount, WATCard* card) : sid(sid), amount(amount), card(card) {}
	};
	_Task Courier {
		unsigned int id; 
		WATCardOffice &cardOffice;
		Printer & printer;
		Bank & bank;
		void main();
		public: 
			Courier(unsigned int id, WATCardOffice &cardoffice, Printer &printer, Bank & bank);
	};					// communicates with bank

	Printer & printer;
	Bank & bank;
	unsigned int numCouriers;
	Courier** couriers;
	queue<Job*> jobs;
	void main();

  public:
	_Event Lost {};							// lost WATCard
	
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	~WATCardOffice();
	WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
	Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif