CC = g++
STD = c++17
prog = main
objects = main.o radix_tree.o compressed_radix_tree.o

all: $(prog)

$(prog): $(objects)
	$(CC) -std=$(STD) -g -o $(prog) $(objects)

main.o: main.cpp radix_tree.hpp compressed_radix_tree.hpp
	$(CC) -std=$(STD) -g -c main.cpp

radix_tree.o: radix_tree.cpp radix_tree.hpp
	$(CC) -std=$(STD) -g -c radix_tree.cpp

compressed_radix_tree.o: compressed_radix_tree.cpp compressed_radix_tree.hpp
	$(CC) -std=$(STD) -g -c compressed_radix_tree.cpp

grade: $(prog)
ifeq ($(OS), Windows_NT)
	@powershell.exe -ExecutionPolicy Bypass -File .\grade.ps1
else
	@./grade.sh
endif

clean:
ifeq ($(OS), Windows_NT)
	@del /q .\*.o .\output\* 2>nul
	@del /q .\$(prog).exe 2>nul
else
	@rm -rf ./*.o ./output/* $(prog)
endif
