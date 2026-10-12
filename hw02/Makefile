CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

PROGRAM = readings
OBJECTS = main.o reading.o stats.o histogram.o
TEST_PROGRAM = tests/test_stats

.PHONY: all clean test

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c reading.h stats.h histogram.h
	$(CC) $(CFLAGS) -c main.c -o main.o

reading.o: reading.c reading.h
	$(CC) $(CFLAGS) -c reading.c -o reading.o

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c -o stats.o

histogram.o: histogram.c histogram.h
	$(CC) $(CFLAGS) -c histogram.c -o histogram.o

tests/test_stats.o: tests/test_stats.c stats.h
	$(CC) $(CFLAGS) -c tests/test_stats.c -o tests/test_stats.o

$(TEST_PROGRAM): tests/test_stats.o stats.o
	$(CC) $(CFLAGS) -o $@ tests/test_stats.o stats.o

test: $(PROGRAM) $(TEST_PROGRAM)
	./$(TEST_PROGRAM)
	sh regress.sh

clean:
	rm -f $(OBJECTS) tests/test_stats.o $(PROGRAM) $(TEST_PROGRAM)