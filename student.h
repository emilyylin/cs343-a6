#ifndef STUDENT_H
#define STUDENT_H

#include "printer.h"
#include "nameServer.h"
#include "watcard.h"
#include "groupoff.h"
#include "vendingMachine.h"
#include "watcardOffice.h"

_Task Student {
	Printer & printer;
	NameServer & nameServer;
	WATCardOffice &cardOffice;
	Groupoff & groupoff;
	unsigned int id;
	unsigned int maxPurchases;
	void main();
  public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif
