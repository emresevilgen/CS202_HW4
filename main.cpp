/* *
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Munib Emre Sevilgen
* ID : 21602416
* Section : 1
* Assignment : 4
* Description : main.cpp
*/

/**
 * CS 202 - HW 4
 * A main file
 * Please make sure that your code compiles and runs with this main file
 */
#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 


/*You can add additional libraries here to read and process the dataset*/

using namespace std;

int main() {
    Graph g;
	string inputName = "flightDataset.txt";
	string airport1 = "";
	string airport2 = "";
	string number = "";
	int passengerNumber = 0;
	ifstream inputFile;
    inputFile.open(inputName.c_str());


	if (inputFile.is_open()){
		while (!inputFile.eof()){
			getline(inputFile, airport1, ';');
			getline(inputFile, airport2, ';');
			getline(inputFile, number);
			stringstream ss(number);
			ss >> passengerNumber;
			//passengerNumber = stoi(number);
			g.addConnection(airport1, airport2, passengerNumber);
		}
	}

	cout << "---- Displays all edges from all vertices one by one ----" << endl;
	for(map<string, list<node> >::iterator itr = g.adjList.begin(); itr != g.adjList.end(); itr++){
		for (list<node>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){
			cout << itr->first << ";" << itr2->airportName << ";" << itr2->numOfPassengers << endl;
		}
	}

	cout << "----" << endl;

	cout << "---- Displays the all adjacent airports of the NORWICH ----" << endl;

	list<string> l = g.getAdjacentAirports("NORWICH");
	for (list<string>::iterator it = l.begin(); it != l.end(); it++){
		cout << *it << endl;
	}

	cout << "----" << endl;

 	cout << "---- Displays the total passengers of the KIRKWALL ----" << endl;
	cout << g.getTotalPassengers("KIRKWALL") << endl;
  	
	cout << "----" << endl;

	cout << "---- Displays the shortest path from KIRKWALL to JERSEY ----" << endl;
	list<string> fspList = g.findShortestPath("KIRKWALL", "JERSEY");
	for(list <string>::iterator itrFspList = fspList.begin(); itrFspList != fspList.end(); itrFspList++)
		cout << *itrFspList << endl;

	cout << "----" << endl;

	cout << "---- Displays the minimum spanning tree of the graph ----" << endl;
	list <pair<string, string> > mstList = g.findMST();

	for(list <pair<string, string> >::iterator itrList = mstList.begin(); itrList != mstList.end(); itrList++){
		cout << itrList->first << " - " << itrList->second << endl;
	}

	cout << "----" << endl;

	cout << "---- Displays all edges from all vertices one by one after deleting KIRKWALL ----" << endl;
	g.deleteAirport("KIRKWALL");
	for(map<string, list<node> >::iterator itr = g.adjList.begin(); itr != g.adjList.end(); itr++){
		for (list<node>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){
			cout << itr->first << ";" << itr2->airportName << ";" << itr2->numOfPassengers << endl;
		}
	}

	return 0;
}
// End of main file
