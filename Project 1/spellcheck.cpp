/*
	Name:			Yacine Manseur
	Date:			09/23/2014
	Class:			DSA II
	Assignment:		Programming Assignment #1
	Description:	This program reads in a dictionary and places all the words into
				a hash function. The program then spell checks a document on whether
				or not each word is in the dictionary.
*/

#include "hash.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm> //transform

using namespace std;

hashTable dictionary(100000);

void loadDictionary(ifstream &in);
int isValid(string &word);
bool containsNumber(string &word);
void spellCheck(ifstream &in, ofstream &out);


int main(){

  string fileIn, fileOut;
  cout << "Enter name of dictionary: ";
  cin >> fileIn;
  ifstream input(fileIn.c_str());
  
  // incorrect file name
  if(!input){
    cout << "Error: Can't open " << fileIn << endl;
	  return 0;
  }
  
  clock_t t1 = clock();
  loadDictionary(input);
  clock_t t2 = clock();
  double dLoadTime = ((double)(t2-t1))/CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to load dictionary: " << dLoadTime << endl;
  
  cout << "Enter name of input file: ";
  cin >> fileIn;
  cout << "Enter name of output file: ";
  cin >> fileOut;
  
  ifstream inputDoc(fileIn.c_str());
  ofstream outputDoc(fileOut.c_str());
  
  t1 = clock();
  spellCheck(inputDoc, outputDoc);
  t2 = clock();
  double sLoadTime = ((double)(t2-t1))/CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to check document: " << sLoadTime << endl;
  
  
  
}

void loadDictionary(ifstream &in){
  string word;
  while(getline(in, word)){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
	if(isValid(word)==0)
		dictionary.insert(word);
  }
  return;
}


// Return 0 if valid
// Return 1 if too long
// Return 2 if invalid word
int isValid(string &word){
  string validChar = "abcdefghijklmnopqrstuvwxyz0123456789\'-";
  
  if(word.length() > 20)
    return 1;

  for(int i = 0; i < word.length(); i++){
    if(validChar.find(word[i])==string::npos)
	  return 2;
  }
    
  return 0;

}

// Returns true if word contains a number
// Returns false otherwise
bool containsNumber(string &word){
  string numbers = "0123456789";

  return (word.find_first_of(numbers) != string::npos);

}

void spellCheck(ifstream &in, ofstream &out){

  string word, line;
  string validChar = "abcdefghijklmnopqrstuvwxyz0123456789\'-";
  int lineNumber = 1;
  // int check = 0; //used for isValid()
  int start, end; //used for generating substrings
  
  
  while(getline(in, line)){
    transform(line.begin(), line.end(), line.begin(), ::tolower);
	
	//Skip blank lines.
	if(line==""){
	  lineNumber++;
	  continue;
	}
	
	start = line.find_first_of(validChar);
	//Iterate through line and separate words
	while( start != string::npos){
	  end = line.find_first_not_of(validChar, start);
	  word = line.substr(start, (end-start));
	  start = line.find_first_of(validChar, end);
	  
	  //ignore words that include digits
	  if(containsNumber(word))
		continue;
	  
	  if(word.length() > 20)
	    out << "Long word at line " << lineNumber << ", starts: " << word.substr(0,20) << endl;
		
	  else if(!(dictionary.contains(word))) // Check if word is in the Dictionary
	    out << "Unknown word at line " << lineNumber << ": " << word << endl;
		
	  else if (end == string::npos) // Break if the document is over
	    break;
	
	}
	
	lineNumber++;
	}
	
}
