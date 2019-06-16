/* *
* Title : Balanced Search Trees , Hashing and Graphs
* Author : Munib Emre Sevilgen
* ID : 21602416
* Section : 1
* Assignment : 4
* Description : graph.cpp
*/

/** @file graph.cpp
 * An adjacency list representation of an undirected weighted graph. 
*/

#include "graph.h"
/*Do not add new libraries or files*/

Graph::Graph()
{
}  // end constructor

void Graph::addAirport(const string& airportName)
{   
    list<node> l;
    adjList.insert(pair<string, list<node> >(airportName, l));

}  // end addPerformer

void Graph::addConnection(const string& airport1, const string& airport2, int numOfPassengers)
{    
    if (airport1 != "" && airport2 != ""){ // Checks the input are valid
        map<string, list<node> >::iterator itr = adjList.find(airport1);
        
        if(itr == adjList.end()){ // If the airport1 does not exist add the airport
            addAirport(airport1);
            itr = adjList.find(airport1);
        }

        // Create the new node add the list of nodes for the airport1
        node newNode;
        newNode.airportName = airport2;
        newNode.numOfPassengers = numOfPassengers;

        itr->second.insert(itr->second.end(), newNode);

        map<string, list<node> >::iterator itr2 = adjList.find(airport2);

        if(itr2 == adjList.end()){ // If the airport2 does not exist add the airport
            addAirport(airport2);
            itr2 = adjList.find(airport2);
        }

        // Create the new node add the list of nodes for the airport2

        node newNode2;
        newNode2.airportName = airport1;
        newNode2.numOfPassengers = numOfPassengers;

        itr2->second.insert(itr2->second.end(), newNode2);


    }

}  // end addConnection

list<string> Graph::getAdjacentAirports(const string& airportName)
{
    list<string> newList;
    map<string, list<node> >::iterator itr = adjList.find(airportName); // Finds the airport
    if (itr != adjList.end()){ // If the airport exists
        for(list<node>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){ // Traverses the list of nodes and adds to the list
            newList.insert(newList.end(), itr2->airportName);
        }
    }
    return newList;
}  // end getAdjacentAirports

int Graph::getTotalPassengers(const string& airportName)
{
    int sum = 0;
    map<string, list<node> >::iterator itr = adjList.find(airportName); // Finds the airport
    if (itr != adjList.end()){ // If the airport exists
        for(list<node>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){ // Traverses the list of nodes and adds to the sum
            sum = sum + itr2->numOfPassengers;
        }
    }
    return sum;

}  // end getTotalPassengers


list<string> Graph::findShortestPath(const string& airport1, const string& airport2)
{ 
    queue<string> bfsQ;
    list<string> l;
    bfsQ.push(airport1);
    map<string, string> pre;
    pre.insert(pair<string, string>(airport1, ""));

    while (!bfsQ.empty()){
        string current = bfsQ.front();
        bfsQ.pop(); // Extract the top airport
        // Traverses the adjacent airports of the current airport
        map<string, list<node> >::iterator itrGraph = adjList.find(current);
        map<string, string>::iterator itrPre;
        for (list<node>::iterator itrList = itrGraph->second.begin(); itrList != itrGraph->second.end(); itrList++){
            string adjVertex = itrList->airportName;
            itrPre = pre.find(adjVertex);
            if (itrPre == pre.end()){ // If the vertex is not visited then push the vertex to the path and the queue
                pre.insert(pair<string, string>(adjVertex, current));
                bfsQ.push(adjVertex);
            }
            if (adjVertex == airport2){ // If the airport2 is reached then return the list
                current = adjVertex;
                while (current != ""){
                    itrPre = pre.find(current);
                    l.insert(l.begin(), current);
                    current = itrPre->second;
                } 
                return l;
            }
        }
    }
    return l;
}  // end findShortestPath

list< pair<string, string> > Graph::findMST()
{
    list< pair<string, string> > l;
    if (adjList.empty())
        return l;

    list <string> visited;
    // Min heap by the priority_queue
    priority_queue <pair<int, pair<string, string> >, vector<pair<int, pair<string, string> > >, greater<pair<int, pair<string, string> > > > edges;  
    
    map<string, list<node> >::iterator itrGraph = adjList.begin();
    visited.insert(visited.begin(), itrGraph->first);

    // Adds the edges of the first vertex
    for (list<node>::iterator itrList = itrGraph->second.begin(); itrList != itrGraph->second.end(); itrList++)
        edges.push(pair<int, pair<string, string> >(itrList->numOfPassengers, pair<string, string>(itrGraph->first, itrList->airportName)));

    while (!edges.empty()){ // While the heap is not empty
        string minEdgeR = edges.top().second.second;
        string minEdgeL = edges.top().second.first;
        edges.pop(); // Pop the minimum edge

        // Checks the other right of the edge is visited or not
        list<string>::iterator itrVisited;
        for (itrVisited = visited.begin(); itrVisited != visited.end(); ++itrVisited){
            if (minEdgeR == *itrVisited){
                break;
            }
        }

        if (itrVisited == visited.end()){ // If the right is not visited
            l.insert(l.end(), pair<string, string>(minEdgeL, minEdgeR)); // Insert the edge to the output list
            visited.insert(visited.end(), minEdgeR); // Mark the right as visited
            
            // Look for the new edges that are of the new vertex
            itrGraph = adjList.find(minEdgeR);
            for (list<node>::iterator itrList = itrGraph->second.begin(); itrList != itrGraph->second.end(); itrList++){
                // Checks the right of new edges are visited or not
                for (itrVisited = visited.begin(); itrVisited != visited.end(); ++itrVisited){
                    if (itrList->airportName == *itrVisited){
                        break;
                    }   
                }
                if (itrVisited == visited.end()){ // If the right is not visited then push it to the heap
                    edges.push(pair<int, pair<string, string> >(itrList->numOfPassengers, pair<string, string>(itrGraph->first, itrList->airportName)));
                }
            }
            
        }
    }
    return l;
}  // end findMST

void Graph::deleteAirport(const string& airportName)
{
    map<string, list<node> >::iterator prev = adjList.begin();
    for(map<string, list<node> >::iterator itr = adjList.begin(); itr != adjList.end(); itr++){ 
        
        if (itr->first != airportName){ // Search for the right of the edges to delete
            list<node>::iterator itr2 = itr->second.begin();
            for(list<node>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){
                if (itr2->airportName == airportName){
                    itr->second.erase(itr2);
                    break;
                }
                
            }
        }
        else { // Search for the left of the edges to delete
            adjList.erase(itr);
            itr = prev;
        }
        prev = itr;
    }

}  // end deleteAirport

