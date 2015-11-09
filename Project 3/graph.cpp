/*
	Name:			Yacine Manseur
	Date:			11/15/2014
	Class:			DSA II
	Description:	Programming Project 3
*/

#include "graph.h"

#define INFINITY 1000000	//All edge costs will be less than one million

using namespace std;

graph::graph(int capacity){

	map = new hashTable(capacity);
}

bool graph::insertVertex(string id){

	if(this->hasVertex(id))
		return false;
	
	Vertex *v = new Vertex();
	v->id = id;
	map->insert(id, v);
	vertices.push_back(v);
	return true;
}

bool graph::hasVertex(string id){

	return (map->contains(id));
}
	
bool graph::insertEdge(string start, string end, int cost){

	this->insertVertex(start);
	this->insertVertex(end);
	
	bool b = true;
	Vertex *destination = static_cast<Vertex *> (map->getPointer(end, &b));
	Vertex *source = static_cast<Vertex *> (map->getPointer(start, &b));

	Edge *e = new Edge();
	e->cost = cost;
	e->destination = destination;
	source->adj.push_back(e);
}
	
void graph::Dijkstra(string source){
	
	//Priority Queue to hold vertices
	//	Corresponding keys will be its distance from the source
	heap Q(vertices.size()); 
	
	Vertex *v;
	Edge *e;
	//Loop through all the vertices, setting initial distances
	list<Vertex *>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it++){
		v = (*it);
		if(v->id == source)
			v->dist = 0;
		else
			v->dist = INFINITY;
		//initialize variables for vertices and insert it into the heap
		v->known = false;
		v->path = NULL;
		Q.insert(v->id, v->dist, v);
	}
	
	//Loop till heap is empty, removing the vertex with the smallest node
	while(Q.deleteMin(NULL,NULL, &v) != 1){
		v->known = true;	//v is removed from heap and marked as known
		list<Edge *>::iterator it;
		//loop each outgoing edge from v using the adjacency list
		for(it=v->adj.begin(); it!=v->adj.end(); it++){
			e = (*it);
			//dv is the distance along the edges from the adjacency list
			int dv = v->dist + e->cost;
			if(dv < e->destination->dist){
				//Overwrite the key and previous vertex for the given ending vertex
				e->destination->dist = dv;
				Q.setKey(e->destination->id,dv);
				e->destination->path = v;
			}
		}
	}
}

void graph::print(string fileName){

	ofstream fileOut(fileName.c_str());
	string path;	//interesting... if I initialize path I get "Aborted (core dumped)
	list<Vertex *>::iterator it;
	Vertex *v;
	//loop through all the vertices
	for(it = vertices.begin(); it != vertices.end(); it++){
		v = (*it);
		fileOut << v->id << ": ";
		
		if(v->dist == INFINITY)
			fileOut << "NO PATH" << endl;
		else if(v->dist == 0)
			fileOut << v->dist << " [" << v->id << "]" << endl;
		else {
			fileOut << v-> dist << " [";
			path = v->id;
			//follow the path to the source, but add it to the string in reverse
			while(v->path != NULL){
				path = v->path->id + ", " + path;
				v = v->path;
			}
			fileOut << path << "]" << endl;
		}
	}
}
