CC=g++
CFLAGS=-c -O2 -Wall 
LDFLAGS=-lDevicePerformance
SOURCES=test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

INC_PATH = -I ./include
LIB_PATH = -L ./lib

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -g  $(OBJECTS) -o $@ $(LIB_PATH) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(INC_PATH)

clean:
	rm -rf *.o $(EXECUTABLE)

