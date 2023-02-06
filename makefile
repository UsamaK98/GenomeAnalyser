CC=g++
CFLAGS=-Wall -std=c++11
EXECUTABLE=main
SOURCES=main.cpp

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
