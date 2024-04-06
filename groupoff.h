#ifndef GROUPOFF_H
#define GROUPOFF_H

#include "watcard.h"
#include "printer.h"

_Task Groupoff {
	void main();

  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	WATCard::FWATCard giftCard();
	~Groupoff();

};

#endif GROUPOFF_H