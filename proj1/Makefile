###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Daniel Plotkin


CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS  = -g3

CalcYouLater: DatumStack.o Datum.o parser.o RPNCalc.o testRPNCalc.o
	${CXX} ${LDFLAGS} -o CalcYouLater DatumStack.o Datum.o RPNCalc.o testRPNCalc.o \
												main.cpp

testRPNCalc.o: testRPNCalc.cpp RPNCalc.h DatumStack.h Datum.h
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
RPNCalc.o: RPNCalc.cpp RPNCalc.h

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c -o $@ $<
##
## Put your variables and rules here.  You can use previous Makefiles
## as examples, and you can refer to the "make" documentation on the
## course Reference page.
##  --- Delete this comment and put appropriate comments in ---
clean:
	rm -f datumStack *.o *.dSYM

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

provide:
	provide comp15 proj1 DatumStack.h DatumStack.cpp README parser.cpp \
								 testDatumStack.cpp Makefile RPNCalc.cpp RPNCalc.h file.cylc \
								 testRPNCalc.cpp main.cpp
