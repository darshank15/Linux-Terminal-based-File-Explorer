CC = g++
CFLAGS = -Wall 
DEPS = myheader.h 
OBJ = mydirectoryfunction.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

