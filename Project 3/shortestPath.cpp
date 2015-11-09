/*
	Name:			Yacine Manseur
	Date:			11/15/2014
	Class:			DSA II
	Description:	Programming Project 3
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "graph.h"

using namespace std;

void loadGraph(graph &G, ifstream &in);

int main(){

	string fileIn, fileOut, startVertex;
	bool validVertex = false;
	
	cout << "Enter name of graph file: ";
	cin >> fileIn;
	ifstream input(fileIn.c_str());
	
	graph G(100);
	loadGraph(G, input);
	
	while(!validVertex){
		cout << "Enter a valid vertex id for the starting vertex: ";
		cin >> startVertex;
		
		if(G.hasVertex(startVertex))
			validVertex = true;
		else
			cout << "Vertex " << startVertex << " is not a valid vertex." << endl;
	}
	
	clock_t t1 = clock();
	G.Dijkstra(startVertex);
	clock_t t2 = clock();
	double LoadTime = ((double)(t2-t1))/CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << LoadTime << endl;
	
	cout << "Enter name of output file: ";
	cin >> fileOut;

	G.print(fileOut);
	
	input.close();
	
	return 0;
	
}

void loadGraph(graph &G, ifstream &in){
	string line, start, end;
	int cost;
	
	while(getline(in, line)){
		istringstream iss(line);
		iss >> start >> end >> cost;
		G.insertEdge(start, end, cost);
	}

}
