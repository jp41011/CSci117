/*============================================================================
Name        : Prog5.cpp - CSci 117
Author      : Juan Pedraza
Version     : v3 - 3/31/16
Copyright   : Your copyright notice
Description : CSci 117 - Prog5 assignment
			Practice for dynamic memmory allocation/deallocation (garbage collection).
			Will use the lazy garbage collection mechanism, mark and sweep phases.
			Size of the simulated dynamic memory is 10 cells and each cell contains three fields:
			key, next, mark_bit (init w/ 0)
			Memory will be represented as a vector of Cell. Where Cell is a custom class that has
			3 main information:
				* key: cell value
				* next: next cell index
				* mark_bit: whether this cell has been marked by the garbage collection function

============================================================================
*/


#include <iostream>
#include <vector>

using namespace std;

//definition of the Cell class
class Cell{
public:
	int key;
	int next;
	bool mark_bit;

	Cell(int newKey = -1, int newNext = -1, bool newMark = false)
	{
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
	void unMark(){mark_bit=false;}

};



void intro_options(); // main intro options for user
void init_memory(); // initialize memory
void print_memory(); // print summary of memory contents

void myInsert();  // insert key into a given list
void insertion(int& , int); // does the actual insertion

void deleteIntro(); // get information to delete
void myDelete(int&, int); // delete key from given list
void addToFreeList(int); // index of cell to be added to the free list

void garbage_collect(int, int); // use mark and sweep method to free up memory

void printListIntro();
void printList(int); // iterate and print list values

// global variables
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
	cout << "5. Print List" << endl;
	cout << "6. Quit" << endl;
	cout << "==== ====" << endl;
	cout << "Command: ";
	
	cin >> input;
	if(input == "1"){ // insert
		myInsert();
	}else if(input == "2"){ // delete
		deleteIntro();
	}else if(input == "3"){
		garbage_collect(head1, head2);
	}else if(input == "4"){ // print memory
		print_memory();
	}else if(input == "5"){
		printListIntro();
	}else if(input == "6"){ // exit for break out of this
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

	if(headFree < 10){ // if there is still at least one free cell
		memory[headFree].setKey(userValue); // user next free cell and set value
		memory[headFree].setNext(-1); // just make sure it points to nothing (end of list)

	}else{ // no free cells so have to clear memory and then add value
		//todo
	}

	headFree++; // move free pointer to next cell
	if(userList == "1")
		insertion(head1, headFree-1);
	else
		insertion(head2, headFree-1);

	cout << "==== Insert End ====" << endl;
	return;
}

// insertion does the actual insertion give list head pointer and inserted index
// does the sorting (insertion sort)
void insertion(int& head, int newIndex){
	if(head == -1){ // empty list
		head = newIndex;
		return;
	}
	//non empty list
	int curIndex = head; // current index
	int prevIndex = 0; // keep track of the previous index
	bool isInserted = false; // flag
	while(isInserted == false)
	{
		if(memory[newIndex].getKey() < memory[curIndex].getKey()) // insert into front of list
		{
			memory[newIndex].setNext(curIndex);
			if(curIndex == head) // its the start of the list (head)
			{
				head = newIndex; // update to the new start of the list
			}else{ // not the front of the list but somewhere in the middle
				memory[prevIndex].setNext(newIndex); // update last pointer to point to new intermidate cell
			}
			isInserted = true;
		}else if(memory[curIndex].getNext() == -1){ // reached the end of the list
			//memory[prevIndex].setNext(newIndex); // update last pointer to point to new intermidate cell
			memory[curIndex].setNext(newIndex);
			isInserted = true;
		}else{ //
			prevIndex = curIndex;
			curIndex = memory[curIndex].getNext();
		}
	}
}

// intro to print list function. get list which has to be printed
void printListIntro()
{
	cout << "Enter (1)-List1 or (2)-List2 or (3)-Free List: ";
	int list;
	cin >> list;
	if(list == 1)
		printList(head1);
	else if(list == 2)
		printList(head2);
	else
		printList(headFree);
}

// given a head index this will iterate through the list and print out the values
void printList(int head)
{
	cout << "List: ";
	int curIndex = head;
	while(true){
		if(curIndex == -1) // reached end
			break;
		cout << memory[curIndex].getKey() << " ";
		curIndex = memory[curIndex].getNext();
	}
	cout << endl;
}

// get info about what to delete from user and then call delete function
void deleteIntro()
{
	cout << "Enter (1): List1 or (2): List2: ";
	int list;
	cin >> list;
	cout << "Enter value to delete: ";
	int value;
	cin >> value;
	
	if(list == 1)
		myDelete(head1, value);
	else if (list == 2)
		myDelete(head2, value);
	
	return;
}

// do the actual delete here TODO
void myDelete(int& head, int val)
{
	/*
	if(memory[head].getKey() == val) // if head has the value to be removed
	{
		head = memory[head].getNext();
		return;
	}
	*/

	int curIndex = head;
	int prevIndex = 0;
	bool finishedDelete = false;

	while(finishedDelete == false)
	{
		
		if(memory[curIndex].getKey() == val) // found value to remove
		{
			if(curIndex == head) // if this node is the head of the list
			{
				head = memory[curIndex].getNext(); // update head of list to new head
				//addToFreeList(curIndex); // add back to free list more active approach
				finishedDelete = true;
				return;
			}
			int tempNext = memory[curIndex].getNext();
			memory[prevIndex].setNext(tempNext);
			//addToFreeList(curIndex); // add back to free list more active approach
			finishedDelete = true;
			return;
			
		}else{ // this cell is not a match
			prevIndex = curIndex;
			curIndex = memory[curIndex].getNext();
			if(curIndex == -1)
			{
				cout << "Delete: " << val << " NOT found in list" << endl;
				return;
			}
		}
	}

}

// add the given index to the front of the free list
void addToFreeList(int index)
{
	memory[index].setNext(headFree); // update this new free cell to point to the previous free head pointer
	headFree = index; // update free head pointer
	return;
}

/*function to do garbage collection via the 2 phase mark and sweep method
inputs:
h1: head1 starting index
h2: head2 starting index
*/
void garbage_collect(int h1, int h2)
{
	// first go through list and mark all accessible cells
	int curIndex = h1;
	while(curIndex != -1) // mark all those in list 1
	{
		memory[curIndex].mark();
		curIndex = memory[curIndex].getNext();
	}

	curIndex = h2; // reset starting index
	while(curIndex != -1)
	{
		memory[curIndex].mark();
		curIndex = memory[curIndex].getNext();
	}

	for(unsigned int i=0; i < memory.size(); i++)
	{
		if(memory[i].isMarked() == false) // not marked therefore needs to be added for free list
		{
			addToFreeList(i);
		}
	}

	return;
}
