CC=gcc
CFLAGS=-Wall -lpthread

sudoku_validator: main.o validator.o utils.o
	$(CC) -o sudoku_validator main.o validator.o utils.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c

validator.o: validator.c
	$(CC) -c validator.c

utils.o: utils.c
	$(CC) -c utils.c

clean:
	rm -f *.o sudoku_validator
