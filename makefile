CC = g++

default: SearchEngine clean

SearchEngine: SearchEngine.o ReadInput.o Map.o Trienode.o Listnode.o Search.o scorelist.o Maxheap.o
	$(CC) -o SearchEngine SearchEngine.o ReadInput.o Map.o Trienode.o Listnode.o Search.o scorelist.o Maxheap.o

Maxheap.o: Maxheap.cpp Maxheap.h
	$(CC) -c Maxheap.cpp

scorelist.o: scorelist.cpp scorelist.h
	$(CC) -c scorelist.cpp

Search.o: Search.cpp Search.h
	$(CC) -c Search.cpp

Listnode.o: Listnode.cpp Listnode.h
	$(CC) -c Listnode.cpp

Trienode.o: Trienode.cpp Trienode.h
	$(CC) -c Trienode.cpp

Map.o : Map.cpp Map.h
	$(CC) -c Map.cpp

ReadInput.o: ReadInput.cpp ReadInput.h
	$(CC) -c ReadInput.cpp

SearchEngine.o: SearchEngine.cpp SearchEngine.h
	$(CC) -c SearchEngine.cpp

clean:
	rm *.o
