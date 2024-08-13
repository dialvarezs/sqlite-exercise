CC = gcc
CFLAGS = -Wall -I. 
DEPS = database.h sqlite3.h
OBJ = main.o database.o sqlite3.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main
