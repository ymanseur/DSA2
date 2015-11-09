/*
	Name:			Yacine Manseur
	Date:			09/23/2014
	Class:			DSA II

*/

#include "hash.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

hashTable::hashTable(int size) {
  capacity = getPrime(size);
  hashItem item;
  item.isOccupied = false;
  item.isDeleted = false;
  data.resize(capacity, item);
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const string &key, void *pv) {
  
  // Check if load factor of 0.5 is reached.
  // If so, it will rehash the hashtable.
  // If rehash returns false, insert() returns 2
  double loadFactor = ((double)filled)/((double)capacity);
  if (loadFactor > 0.5){
	if(!rehash()) //rehash failed
	  return 2;
	}
	
	int index = hash(key) % data.size();
	
	while(data[index].isOccupied){
	  if((data[index].key == key) && !(data[index].isDeleted)) //key already exists in hash table and has not been lazily deleted
	    return 1;
	  index = ((index+1) % data.size()); //continue linear probe
	}
	
	// insert the key and assign appropriate values
	data[index].key = key;
	data[index].isOccupied = true;
	data[index].isDeleted = false;
	data[index].pv = pv;
	
	filled = filled + 1; //iterate filled
	return 0;
  
}

bool hashTable::contains(const string &key) {
  int i = findPos(key);
  if(i==-1)
    return false;
  else
    return true;
}

  
// If the key doesn't exist, returns NULL.
// If the optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void *hashTable::getPointer(const string &key, bool *b) {
  int i = findPos(key);

  if(i==-1){
    if(b)
	  *b = false;
	return NULL;
	
  } else {
  
    if (b)
	  *b = true;
	return data[i].pv;
  }
}

// Returns 0 if successful.
// Returns 1 if the specified key is not in the hash table.
int hashTable::setPointer(const string &key, void *pv) {
  int i = findPos(key);
  
  if(i==-1)
    return 1;
  else{
	data[i].pv = pv;
	return 0;
  }
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const string &key) {
  int i = findPos(key);
  
  if(i==-1)
	return false;
  else{
	data[i].isDeleted = true;
	return true;
  }
}

// The hash function.
int hashTable::hash(const string &key) {
  int sum = 0;
  
  // function deals with ascii values
  // multiplies the current sum instead of individual values for less clashes
  for(int i = 0; i < key.size(); i++) {
    sum = sum*111 + key[i];
  }
  return sum;
}
  

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const string &key) {
  int pos = hash(key) % data.size();
  
  // If the spot is taken and the key isn't equal to the key you're looking for or
  // the item was lazily deleted, continue linear probing.
  while((data[pos].isOccupied == true && data[pos].key != key) || (data[pos].isDeleted && data[pos].key == key)) {
	pos = (pos + 1) % data.size();
  }
  
  if(data[pos].isOccupied == false)
	return -1;
  else
    return pos;  
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash() {
  capacity = getPrime(capacity);
  vector<hashItem> newHash;
  hashItem item;
  item.isOccupied = false;
  item.isDeleted = false;
  
  // Catches allocation failure and returns false instead of closing program
  try {
    newHash.resize(capacity, item);
  } catch (exception& e) {
    return false;
  }
  
  // Create temp to hold data in filled table.
  // Reset filled to 0.
  vector<hashItem> temp = data;
  data = newHash;
  filled = 0;
  
  vector<hashItem>::iterator it = temp.begin();
  for(;it != temp.end(); it++){
    if(!(it->isDeleted) && it->isOccupied)
	  insert(it->key, it->pv);
  }
  
  return true;
  
}

// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
unsigned int hashTable::getPrime(int size) {

  // numbers found at http://www.mathematical.com/primelist1to100kk.html
  // I started with a prime number a little greater than 100,000.
  // The number after is a little less than double the previous value.
  // The last number is included in the rare case that the dictionary
  // is a lot larger than 1,000,000 words.
  int primeNumbers[]={47, 79, 149, 257, 421, 773, 1489, 2671, 5011, 8663, 14563,
		26849, 51769, 100999, 199999, 388471, 773533, 1000151, 1509587};
  int * it = primeNumbers;
  
  for(int inc = 0; 19; inc++) {
    if(*it > size)
	  return *it;
	else
	  *it++;
  }
  
  // If for loop doesn't return, returns biggest prime number in list.
  return primeNumbers[18];
}










