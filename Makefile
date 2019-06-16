# Title : Balanced Search Trees , Hashing and Graphs
# Author : Munib Emre Sevilgen
# ID: 21602416
# Section : 1
# Assignment : 4
# Description : makefile

hw4: main.o graph.o 
	g++ main.o graph.o -o hw4
	rm *.o

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

clean:
	rm hw4
	
