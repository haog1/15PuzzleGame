# Makefile
# Hao Gao 692216
# Aug 2015

OBJ     = idas.o main.o
OBJ2    = widas.o main.o
CC      = gcc -O3
EXE     = ida
EXE2     = wida
CFLAGS  = -Wall

ida:   $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

wida:   $(OBJ2) Makefile
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ2)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ2)
	rm -f $(OBJ) $(EXE)
	rm -f $(OBJ2) $(EXE2)

clobber: clean
	rm -f $(EXE) 
	rm -f $(EXE2)

usage: $(EXE)
	./$(EXE)

USAGE: $(EXE2)
	./$(EXE2)

main.o: ida.h Makefile
idas.o: idas.c
widas.o: widas.c