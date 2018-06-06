CC = g++
CPPFLAG = -Wall -I include

main: $(OBJS)
	$(CC) -c -o build/pipeline.o src/pipeline.cpp $(CPPFLAG)
	$(CC) -c -o build/main.o src/main.cpp $(CPPFLAG)
	$(CC) -o bin/main build/main.o build/pipeline.o $(CPPFLAG) 
