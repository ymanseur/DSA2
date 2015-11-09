/*
	Name: 		  Yacine Manseur
	Date: 		  12/6/2014
	Class: 		  DSA II
	Description:  Programming Project 4
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int mergeMatrix[1001][1001] = {0};

int main() {

	string fileIn, fileOut;
	string A = "", B ="", C = "";
	
	int sizeA, sizeB, sizeC;
	
	cout << "Enter name of input file: ";
	cin >> fileIn;
	cout << "Enter name of output file: ";
	cin >> fileOut;
	
	ifstream in(fileIn.c_str());
	ofstream out(fileOut.c_str());
	
	while(getline(in,A) && getline(in,B) && getline(in,C)){
		// Initialize matrix
		for(int i=0; i<1001; i++){
			for(int j=0; j<1001; j++){
				mergeMatrix[i][j] = 0;
			}
		}
		
		mergeMatrix[0][0] = 1;

		sizeA = A.length();
		sizeB = B.length();
		sizeC = C.length();
		
		if(sizeC != sizeA + sizeB){
			out << "*** NOT A MERGE ***" << endl;
			continue;
		}
		
		// Create path for merged words
		for(int i=0; i<=sizeA; i++){
			for(int j=0; j<=sizeB; j++){
				if(mergeMatrix[i][j] == 1){
					if(C[i+j] == A[i])
						mergeMatrix[i+1][j] = 1;
					if(C[i+j] == B[j])
						mergeMatrix[i][j+1] = 1;
				}
			}
		}

		// Print to output
		if(mergeMatrix[sizeA][sizeB] == 1){
			int i = sizeA;
			int j = sizeB;
			while(i>0 && j>=0){
				if(mergeMatrix[i][j] == 1 && (j == 0 || mergeMatrix[i][j-1] == 0)){
					C[i+j-1] = toupper(C[i+j-1]);
					i--;
				} else { 
					j--;
				}
			}
			out << C << endl;
		} else {
			out << "*** NOT A MERGE ***" << endl;
		}
	}
}
