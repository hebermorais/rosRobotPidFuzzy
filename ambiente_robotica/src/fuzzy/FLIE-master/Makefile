CC=g++
CFLAGS=-I.
DEPS = fuzzyset.h lingvar.h rule.h fuzzy_control.h flie.h
OBJ = fuzzyset.o lingvar.o rule.o fuzzy_control.o flie.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

flie: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

clean: 
	$(RM) flie *.o *~
