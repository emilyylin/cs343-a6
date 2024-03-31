#include "printer.h"
#include "bank.h"

_Task Parent {
    Printer & printer;
    Bank & bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Parent(); //destructor
};