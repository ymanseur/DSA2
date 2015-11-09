/*
	Name:			Yacine Manseur
	Date:			10/15/2014
	Class:			DSA II
	Description:	Programming Project 2
*/

#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
heap::heap(int capacity){
	this->capacity = capacity;
	currentSize = 0;
	data.resize(capacity+1);
	mapping = new hashTable(capacity*2);
}

// insert - Inserts a new node into the binary heap
//
// Inserts a node with the specified id string, key,
// and optionally a pointer. They key is used to
// determine the final position of the new node.
//
// Returns:
//   0 on success
//   1 if the heap is already filled to capacity
//   2 if a node with the given id already exists (but the heap
//     is not filled to capacity)
int heap::insert(const string &id, int key, void *pv){
	//Check if heap is already filled to capacity
	if (capacity == currentSize)
		return 1;
		
	//Check if node with given id already exists
	else if (currentSize < capacity && mapping->contains(id))
		return 2;
		
	//Insert the node
	else {
		//Insert node at the end of the heap
		currentSize++;
		data[currentSize].id = id;
		data[currentSize].key = key;
		data[currentSize].pData = pv;
		
		//Insert the node into the hashtable
		mapping->insert(id,&data[currentSize]);
		
		percolateUp(currentSize);
		
		return 0;
	}
}

// setKey - set the key of the specified node to the specified value
//
// I have decided that the class should provide this member function
// instead of two separate increaseKey and decreaseKey functions.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
int heap::setKey(const string &id, int key){
	bool b = false; //checker if the node exists
	node *pn = static_cast<node *> (mapping->getPointer(id, &b));
	//getPointer will change b to true if the node exists
	
	if(!b)
		return 1;
	
	int index = getPos(pn);	//index of the specified node
	data[index].key = key;	//overwrites old key with new key
	
	//Heap order property:	the value of the key of any node must be less than or
	//						equal to the values of the keys of its children
	
	//Need to percolate up or down if changing the key violates the heap order property
	
	// case 1: compares key to left child
	// case 2: compares key to right child
	bool case1 = ((index*2 <= currentSize) && (data[index].key > data[index*2].key));
	bool case2 = (((index*2+1) <= currentSize) && (data[index].key > data[(index*2+1)].key));
	
	bool percDown = case1 || case2;
	bool percUp = (index != 1 && data[index].key < data[(index/2)].key);
	
	if(percDown)
		percolateDown(index);
	else if (percUp)
		percolateUp(index);
	
	return 0;	
}

// deleteMin - return the data associated with the smallest key
//             and delete that node from the binary heap
//
// If pId is supplied (i.e., it is not NULL), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
//   0 on success
//   1 if the heap is empty
int heap::deleteMin(string *pId, int *pKey, void *ppData){
	//Check if the heap is empty
	if(currentSize == 0)
		return 1;
	
	//Set pointers to the root if supplied
	if(pId)
		*pId = data[1].id;
	if(pKey)
		*pKey = data[1].key;
	if(ppData)
		*(static_cast<void **> (ppData)) = data[1].pData;
	
	//remove the id from the hashtable
	mapping->remove(data[1].id);
	
	//move the last item to the root and percolate down from the root
	data[1] = data[currentSize];
	currentSize--;
	percolateDown(1);
	return 0;
}

// remove - delete the node with the specified id from the binary heap
//
// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
int heap::remove(const string &id, int *pKey, void *ppData){
	bool b = false; //checker if the node exists
	node *pn = static_cast<node *> (mapping->getPointer(id, &b));
	//getPointer will change b to true if the node exists
	
	if(!b)
		return 1;

	int index = getPos(pn);
		
		//Set pointers to the root if supplied
	if(pKey)
		*pKey = data[index].key;
	if(ppData)
		*(static_cast<void **> (ppData)) = data[index].pData;
	
	//remove the id from the hashtable
	mapping->remove(id);
	
	//move the last item in the heap to the position of the deleted node
	data[index] = data[currentSize];
	mapping->setPointer(data[index].id, &data[index]);
	currentSize--;
	
	//Check if the heap order property has been violated
	//I will just do copy/paste from the setKey() function
	
	// case 1: compares key to left child's key
	// case 2: compares key to right child's key
	bool case1 = ((index*2 <= currentSize) && (data[index].key > data[index*2].key));
	bool case2 = (((index*2+1) <= currentSize) && (data[index].key > data[(index*2+1)].key));
	
	bool percDown = case1 || case2;
	bool percUp = (data[index].key < data[(index/2)].key);
	
	if(percDown)
		percolateDown(index);
	else if (percUp)
		percolateUp(index);
	
	return 0;
}

// Percolate Up function
// Compares the node with its parent and swaps them if its key is smaller
// Moves the hole up until either it is the root or it satisfies the heap order property
void heap::percolateUp(int posCur){
	int hole = posCur;
	node temp = data[posCur];
	
	// Loops till the hole is either the root or its key is bigger than its parent's key
	for( ; hole > 1 && temp.key < data[hole/2].key; hole = (hole/2)){
		data[hole] = data[hole/2];
		mapping->setPointer(data[hole].id, &data[hole]);
	}
	
	data[hole] = temp; //hole is the correct index for the given node
	mapping->setPointer(data[hole].id, &data[hole]);
}

// Percolate Down function
// Compares the given node's key with both of its children's keys
// Keep moving the hole down until it satisfies the heap order property
void heap::percolateDown(int posCur){
	int child;
	int hole = posCur;
	node temp = data[posCur];
	
	//Loops till the hole has no children or its children both have bigger keys
	//Every iteration, the hole keeps moving down to the child with the smaller key
	for( ; (hole * 2) <= currentSize; hole = child){
		child = hole * 2; //left child
		
		//choose the child of the hole with the smallest key
		if((child != currentSize) && (data[(child+1)].key < data[child].key))
			child++; //becomes right child if true
		if(data[child].key < temp.key){
			//swap the parent(hole) with the child that has the smallest key
			data[hole] = data[child];
			mapping->setPointer(data[hole].id, &data[hole]);
		}else
			break;	//the parent's key is smaller than both of its children's keys
	}
	
	//hole is now the position in the heap that either has no children or has 
	//a key smaller than its children
	data[hole] = temp;
	mapping->setPointer(data[hole].id, &data[hole]);	
}

//	returns the index of the node in the binary heap
int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}










