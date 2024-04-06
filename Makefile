CXX = u++					# compiler
CXXFLAGS = -quiet -g -nodebug -multi -O2 -Wall -Wextra -MMD # compiler flags
# CXXFLAGS += -I/mnt/c/Users/emily/CS343/a6/uCPP/source/inc
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = soda.o bank.o bottlingPlant.o config.o groupoff.o nameServer.o parent.o printer.o student.o truck.o vendingMachine.o watcard.o watcardOffice.o
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda

#############################################################

.PHONY : all clean

all : ${EXEC}					# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}
