CC=g++
CFLAGS=--std=c++11 -lpthread
# SRC=
EXEC=bin/exo1 bin/exo2 bin/exo3 bin/exo4 bin/exo5
DIRS=bin

all: $(EXEC)

bin/exo1: src/exo1.cpp
	$(CC) -o bin/exo1 src/exo1.cpp $(CFLAGS)

bin/exo2: src/RandSqMatrix.cpp src/exo2.cpp
	$(CC) -o bin/exo2 src/RandSqMatrix.cpp src/exo2.cpp $(CFLAGS)

bin/exo3: src/exo3.cpp
	$(CC) -o bin/exo3 src/exo3.cpp $(CFLAGS)

bin/exo4: src/exo4.cpp
	$(CC) -o bin/exo4 src/exo4.cpp $(CFLAGS)

bin/exo5: src/exo5.cpp
	$(CC) -o bin/exo5 src/exo5.cpp $(CFLAGS)

clean:
	rm -rf bin

# will create all necessary directories after the Makefile is parsed
$(shell mkdir -p $(DIRS))