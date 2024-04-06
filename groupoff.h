#ifndef GROUPOFF_H
#define GROUPOFF_H

#include "watcard.h"
#include "printer.h"

_Task Groupoff {
	
	Printer &printer;
	unsigned int numStudents;
	unsigned int currStudent;

	unsigned int sodaCost;
	unsigned int groupoffDelay;

	//WATCard::FWATCard* giftCards;
	vector<WATCard::FWATCard > giftCards;
	// vector<WATCard *> cards;	// list of cards assigned real WATCards

	void main();

  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	WATCard::FWATCard giftCard();
	~Groupoff();

};

#endif