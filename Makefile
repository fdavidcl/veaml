###############################################################################
# Makefile
###############################################################################

SHELL = /bin/bash

BIN = bin
OBJ = obj
SRCF = src
SRC = $(wildcard $(SRCF)/*.lex)
EXE = $(basename $(BIN)/$(notdir $(SRC)))

CFLAGS = -Wall -Wl,--no-as-needed
CXXFLAGS = $(CFLAGS) -std=c++0x
LDFLAGS = -ll -I/usr/include

###############################################################################

default: $(EXE)

$(BIN)/%: $(OBJ)/%.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ)/%.o: $(SRCF)/%.c
	$(CXX) -c -o $@ -x c++ $(CXXFLAGS) $<

$(SRCF)/%.c: $(SRCF)/%.lex
	$(LEX) -o $@ $<

clean:
	$(RM) -fv $(EXE) core.* *~ *.o

###############################################################################
