/*
============================================================================
Name        : Prog4.cpp
Author      : Juan Pedraza
Version     : v1 - 3/9/16
Copyright   : Your copyright notice
Description : Programming Assignment 4 - CSci 117 Spring 2016
				Task: Given a data file of biological sequences in which each sequence (a string)
				 	 follows its label (a string), find duplicated sequences and rebuild the data file
				 	 with multiple labels for duplicated sequences
				 Input: data file with sequences
				 Output: file with non-dubplicated sequences
				 Environment: Eclipse (IDE) Ubuntu - Quad Core i7

============================================================================
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

typedef unordered_map<string, string> stringMap;
typedef unordered_map<string, vector<string> > stringVectorMap;

fstream inputFile;
ofstream outputFile;

int main() {

	inputFile.open("Prog4-data");
	outputFile.open("output.txt");
	stringVectorMap map1;

	string tempID = "";
	string tempSeq = "";
	while(getline(inputFile, tempID)) // first one should be number (string id)
	{
		getline(inputFile, tempSeq); // get the sequence (next line)
		if(map1.count(tempSeq) == 1 ) // found element already in map
		{ // add the id to the vector of ids that share this sequence
			map1[tempSeq].push_back(tempID); // add new id to list
		}else{ // sequence not already in map
			//add new sequence to map
			vector<string> tempVec; // create temp vector
			tempVec.push_back(tempID); // add string to vector
			map1[tempSeq] = tempVec; // add new sequence and id to map
		}
	}
	auto it = map1.begin();
	cout << it->first << endl;
	vector<string> tvec = it->second;
	for(unsigned int i=0; i<tvec.size(); i++)
		cout << tvec[i] << endl;

	cout << "map1.size() = " << map1.size() << endl;

	stringMap myMap ( { {"apple", "red"}, {"lemon", "yellow"} } );
	myMap["wo"] = "2";
	myMap["three"];
	for(auto it = myMap.begin(); it != myMap.end() ; it++)
	{
		cout << it->first << "\t" << it->second << endl;
	}

	inputFile.close();
	outputFile.close();
	return 0;
}
