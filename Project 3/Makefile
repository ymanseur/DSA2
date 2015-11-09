shortestPath.exe: shortestPath.o graph.o heap.o hash.o
	g++ -o shortestPath.exe shortestPath.o graph.o heap.o hash.o

shortestPath.o: shortestPath.cpp
	g++ -c shortestPath.cpp
	
graph.o: graph.cpp graph.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o shortestPathDebug.exe shortestPath.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups