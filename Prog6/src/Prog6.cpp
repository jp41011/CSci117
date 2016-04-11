/*============================================================================
Name        : Prog6.cpp
Author      : Juan Pedraza
Version     : v2 - 4/10/16
Copyright   : Your copyright notice
Description : CSci 117 - Prog6
				This programming assignment is to convert the implementation
				from using a circular list for implementing the list (class list)
				to using the non-circular method.
				In the circular version, one pointer (rear) is enough to manage the list.
				Implement the list using the non-circular method:
					New class to be named: NC_list
					* Needs two pointers, for the front and the rear cells.
					* derived classes queue and stack should use the members of the NC_list
						instead of the members of the original circular list.
============================================================================
*/

#include <iostream>
using namespace std;

/* cell class
 * Original cell implementation given in project description
 * */
class cell
{
	//by default class members are private
	int info;
	cell* next;

	// cell constructor with int to set initial value
	cell (int i){
		//cout << "cell(int i)" << endl;
		info = i;
		next = this;
	}

	// cell constructor to set cell value and next cell pointer
	cell(int i, cell* n)
	{
		info = i;
		next = n;
	}

	// list class is a friend of this class and can therefore see all of the members of this cell class
	friend class list;
	friend class NC_list;

};

/* list Class
 * Original circular list implementation given in project description
 * */
class list
{
	cell* rear;
	//int privateInt = 11;
public:
	// public list constructor
	list(){
		//cout << "list()" << endl;
		rear = new cell(0);
	}

	// public list deconstructor
	~list()
	{
		while(!empty())
			get();
	}

	// empty function returns true if this cell is the only cell in the list
	int empty(){
		return rear == rear->next;
	}

protected:
	void add(int);
	void push(int);
	int get();

};

// list push function to add a new cell to the list
// used by derived class stack
void list::push(int x)
{
	rear->next = new cell(x, rear->next);
}

// list add function to add
// used by derived class queue
void list::add(int x)
{
	rear->info = x;
	rear = rear->next = new cell(0, rear->next);
}

// list get function
// returns the value of the front most cell and deletes the node
int list::get()
{
	//cout << rear->info << endl;
	if(empty())
		return 0;

	cell* front = rear->next;
	rear->next = front->next;
	int x = front->info;
	delete front;
	return x;
}

/* NC_List class - Non-circular list implementation */
class NC_list{
	// classes by default private
	cell* head; // pointer to the head node of the list
	cell* tail; // pointer to the tail node of the list
public:
	// public constructor create empty list
	NC_list(){
		cell* newCell = new cell(0); // new empty cell
		// both head and tail point to the empty cell
		head = newCell;
		tail = newCell;
		return;
	}

	/* deconstructor delete all cells from the list. Free up memory
	~list(){
		//TODO
	}
	*/

	// check if the list is empty
	// 1 for true (empty list) 0 for false (non-empty list)
	int empty(){
		// if head and tail point to the same 0-valued cell then list is empty
		if(head == tail && head->info == 0)
			return 1;
		else
			return 0;
	}

	// function to add to the back of the list. used by queue derived class
	void add(int i){
		cell* newCell = new cell(0, NULL);
		tail->info = i; // update value of last cell
		tail->next = newCell; // previous tail node points to new tail node
		tail = newCell; // update so that the tail points to the new tail node
		return;
	}

	// function to push new node cell to the front of the list. used by the derived stack class
	void push(int i){
		cell* newCell = new cell(i, head);
		head = newCell;
		return;
	}

	// get functions
	int get(){
		if(empty())
			return 0;

		cell* tempCell = head;
		head = tempCell->next; // move head pointer to next head
		int x = tempCell->info;
		delete tempCell; // free up the memeory
		return x;
	}

};

// queue class - first in first out FIFO
//class queue : public list // derived class
class queue : public NC_list // derived class
{
public:
	queue(){
		//cout << "queue()" << endl;
		//cout << "privateInt: " << privateInt << endl;
		//cout << cell::info << endl;
	}

	int Qget()
	{
		//cout << list::rear->info << endl;
		//return list::get();
		return NC_list::get();
	}

	void Qput(int x)
	{
		add(x);
	}
};

// stack class - first in last out FILO
//class stack : private list //derived class
class stack : private NC_list //derived class
{
public:
	stack(){
		//cout << "stack()" << endl;
	}
	int Spop(){return get();}
	void Spush(int x){
		//cout << "rear: " << rear << endl;
		//list::push(x);
		NC_list::push(x);
	}
	//using list::empty; //make inherited member empty public
	using NC_list::empty;
};


/* main */
int main() {
	queue q1;
	stack s1;

	q1.Qput(3);
	q1.Qput(5);
	q1.Qput(7);
	cout << q1.Qget() << endl;
	cout << q1.Qget() << endl;
	/*
	cout << "test1" << endl;
	cout << q1.empty() << endl;
	cout << "test1" << endl;
	cout << "test3" << endl;
	//q1.list();
	cout << "test3" << endl;
	*/
	cout << q1.Qget() << endl;
	cout << q1.Qget() << endl;

	s1.Spush(2);
	s1.Spush(4);
	s1.Spush(6);
	cout << s1.Spop() << endl;
	cout << s1.Spop() << endl;
	/*
	cout << "test2" << endl;
	cout << s1.empty() << endl;
	cout << "test2" << endl;
	*/
	cout << s1.Spop() << endl;
	cout << s1.Spop() << endl;

	return 0;
}
