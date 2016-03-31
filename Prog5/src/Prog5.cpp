/*============================================================================
Name        : Prog5.cpp - CSci 117
Author      : Juan Pedraza
Version     : v2 - 3/30/16
Copyright   : Your copyright notice
Description : CSci 117 - Prog5 assignment
			Practice for cynamic memmory allocation/deallocation (garbage collection).
			Will use the lazy garbage collection mechanism, mark and sweep phases.
			Size of the simulated dynamic memory is 10 cells and each cell contains three fields:
			key, next, mark_bit (init w/ 0)


============================================================================
*/


#include <iostream>
#include <vector>

using namespace std;

class Cell{
public:
	int key;
	int next;
	bool mark_bit;

	Cell(int newKey = -1, int newNext = -1, bool newMark = false){
		key = newKey;
		next = newNext;
		mark_bit = newMark;
	}

	// getter functions
	int getKey(){return key;}
	int getNext(){return next;}
	bool isMarked(){return mark_bit;}

	// setter functions
	void setKey(int newKey){key=newKey;}
	void setNext(int newNext){next=newNext;}
	void mark(){mark_bit=true;}

};



void intro_options(); // main intro options for user
void print_memory(); // print summary of memory contents
void myInsert();  // insert key into a given list
void myDelete(); // delete key from given list
void garbage_collect(); // use mark and sweep method to free up memory
void init_memory(); // initialize memory
void insertion(int head, int value); // does the actual insertion

vector<Cell> memory;

int head1; // head pointer for list 1
int head2; // head pointer for list 2
int headFree; // head pointer for free list

int main() {
	//init head pointers
	head1 = -1;
	head2 = -1;
	headFree = 0;

	init_memory(); // initialize

	intro_options(); // user input loop

	return 0;
}

// show the user options
void intro_options(){
	string input; // store user input

	cout << "==== User Options ====" << endl;
	cout << "1. Insert" << endl;
	cout << "2. Delete" << endl;
	cout << "3. Garbage Collection" << endl;
	cout << "4. Print Memory" << endl;
	cout << "5. Quit" << endl;
	cout << "==== ====" << endl;
	cout << "Command: ";

	cin >> input;
	if(input == "1"){
		myInsert();
	}else if(input == "2"){
		//myDelete();
	}else if(input == "3"){
		//garbage_collect();
	}else if(input == "4"){ // print memory
		print_memory();
	}else if(input == "5"){ // exit for break out of this
		cout << "[Exit]" << endl;
		return;
	}


	intro_options(); // repeat
}

// print current status of the memory space
void print_memory(){

	// first row
	cout << "\t";
	for(unsigned int i=0; i < memory.size(); i++)
	{
		cout << "[" << i << "]" << "\t";
	}
	cout << endl;

	// second row
	cout << "Key:\t";
	for(unsigned int i=0; i < memory.size(); i++)
	{
		cout << memory[i].getKey() << "\t";
	}
	cout << endl;

	// third row
	cout << "Next:\t";
	for(unsigned int i=0; i < memory.size(); i++)
	{
		cout << memory[i].getNext() << "\t";
	}
	cout << endl;

	// fourth row
	cout << "Mark:\t";
	for(unsigned int i=0; i < memory.size(); i++)
	{
		cout << (memory[i].isMarked() ? "1" : "0") << "\t";
	}
	cout << endl << endl;
	cout << "head1: " << head1 << "\t" << "head2: " << head2 << "\t" << "headFree: " << headFree << endl;

	return;
}

// initialize the memeory spance
void init_memory(){
	int size = 10; // size of memory
	for(int i = 0 ; i< size; i++)
	{
		Cell tempCell (-1, i+1, false);
		memory.push_back(tempCell);
	}
	memory[memory.size()-1].setNext(-1); // set last next value to -1
}

// my insert user gives list and insert value
void myInsert(){
	string userList; // list users requests
	int userValue; // value user want to enter
	cout << "==== Insert ====" << endl;
	cout << "Enter 1 for List1 and 2 for List2: ";
	cin >> userList;
	cout << "Enter value (int): ";
	cin >> userValue;

	if(userList == "1"){ // list1
		insertion(head1, userValue);
	}else if(userList == "2"){ // list2
		insertion(head2, userValue);
	}

	cout << "==== Insert End ====" << endl;
	return;
}

// insertion does the actual insertion give list head pointer and insert value
void insertion(int head, int value){

	if(head == -1){ // need to get from headFree

	}
}
