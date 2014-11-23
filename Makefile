###############################################################################
# Makefile
###############################################################################

SHELL = /bin/bash

BIN = .
SRC = $(wildcard *.l)
EXE = $(basename $(BIN)/$(SRC))

CFLAGS = -Wall -Wl,--no-as-needed
CXXFLAGS = $(CFLAGS) -std=c++0x
LDFLAGS = -ll -I/usr/include

###############################################################################

default: $(EXE)

$(BIN)/%: %.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CXX) -c -x c++ $(CXXFLAGS) $<

%.c: %.l
	$(LEX) -o $@ $<

clean:
	$(RM) -fv $(EXE) core.* *~ *.o

###############################################################################
