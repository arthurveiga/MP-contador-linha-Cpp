IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -g -ftest-coverage -fprofile-arcs

ODIR=obj
LDIR =../lib

LIBS=-lm

# para vetor de int
_DEPS = contador_linha.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = contador_linha.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testa_contador_linha: testa_contador_linha.cpp $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:
	./testa_contador_linha

test:
	gdb testa_contador_linha

gcov:
	gcov testa_contador_linha.gcno -m

# clean
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
