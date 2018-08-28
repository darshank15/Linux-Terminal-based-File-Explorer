CC = g++
CFLAGS = -Wall 
DEPS = myheader.h 
OBJ = mydirectoryfunction.o navigate.o scrolling.o commandmode.o create_dir.o delete_dir.o create_delete_files.o extra_utility.o copycommand.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *o main