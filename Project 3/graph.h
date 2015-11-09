/*
	Name:			Yacine Manseur
	Date:			11/15/2014
	Class:			DSA II
	Description:	Programming Project 3
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include "heap.h"
#include "hash.h"

#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class graph {

	public:
	
	/*	
		Constructor:
		
		Initialize the size of the Graph.
	*/
	graph(int capacity);
	
	/* 
		insertVertex:
	
		Inserts a vertex labeled id into the graph
	
		Returns true if successful
		Returns false otherwise
	*/
	bool insertVertex(std::string id);
	
	/*
		hasVertex:
	
		Checks if a vertex is already in the graph
	
		Returns true if vertex is already in the graph
		Returns false otherwise
	*/
	bool hasVertex(std::string id);
	
	/*
		insertEdge:
	
		Inserts an edge between two verticies with a given cost
	
		Returns true if successful
		Returns false otherwise
	*/
	bool insertEdge(std::string start, std::string end, int cost = 0);
	
	/*
		Dijkstra:
	
		Runs Dijkstra's Algorithm
	*/
	void Dijkstra(std::string source);
	
	/*
		print:
	
		Prints the shortest path to fileName.txt
	*/
	void print(std::string fileName = "output");	
	
	private:
		class Vertex;
		class Edge;
	
		class Edge{
			public:
			int cost;
			Vertex *destination;
		};
	
		class Vertex{
			public:
			std::string id;	//Name of the vertex
			std::list<Edge *> adj;	//Adjacency list
			bool known;
			int dist;
			Vertex *path;	//Vertex before it
		};
		
		std::list<Vertex *> vertices;
		hashTable *map;

};

#endif //_GRAPH_H
