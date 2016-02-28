/*============================================================================
 Name        : Prog3.cpp
 Author      : Juan Pedraza
 Version     : v3 - 2/28/16
 Copyright   : Your copyright notice
 Description : CS 117 - Prog3
 	 	 	 Task: Build an interpreter for the FresnoSP16 language that was defined.
 	 	 	 	 Should check for at least two errors for the following three error classes:
 	 	 	 	 	 Lexical -
 	 	 	 	 	 Syntax -
 	 	 	 	 	 Semantic -
 	 	 	 Input: a mini-language FresnoSP16 programming (stored in a data file)
 	 	 	 Output: Printout of execution reseult
============================================================================
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

struct symbolNode {
  string type;
  string symbol;
  int value;
};

ifstream fin; // global file
istringstream ExpStream; //global stream to be used by exp() ... etc.

vector<symbolNode> symbolTable (0); // symbolTable

bool debug1 = false; // whether to show debugging statements for assignments 1 and 2
bool debug2 = false; // whether to show debugging statements for assignments 3

// Advanced function declaration
int Exp(), Term(), Exp2(int), Term2(int), Fact(), Num();

void declaration_list();
void declaration(string);
void statement_list();
void statement(string);

void printFunc();
void assignFunc(string);

void printSymbolTable();
int getSymbolIndex(string); // takes in a symbol and returns its index in the symbolTable or -1 otherwise

int main() {

	/*
	fin.open("input1.txt"); // testing debugging file
	// Prog2 - assignment 2 main
	cout << "**** Program Start ****" << endl;
	cout << endl << "Result = " << Exp() << endl;
	*/

	fin.open("sampleInput.txt"); // sampe input file
	string tempLine = "";

	getline(fin, tempLine);

	if(tempLine == "program")
	{
		declaration_list();
		if(debug2)
			printSymbolTable();

		statement_list();
	}else{
		cout << "Syntax Error: Does not start with Program" << endl;
	}

	return 0;
}

void printSymbolTable(){
	cout << "--- Symbol Table ---" << endl;
	cout << "Type\tSymbol\tValue" << endl;
	for(unsigned int i=0; i < symbolTable.size(); i++)
	{
		cout << symbolTable[i].type << "\t";
		cout << symbolTable[i].symbol << "\t";
		cout << symbolTable[i].value << endl;
	}
	cout << "--- END ---" << endl;
}

int getSymbolIndex(string symbol)
{
	for(unsigned int i=0; i < symbolTable.size(); i++)
	{
		if(symbolTable[i].symbol == symbol) // found a match
			return i;
	}
	//could not find the symbol in table does not exists
	//cout << "Semantic Error: " << symbol << " does not exists";
	return -1;
}

void declaration_list()
{
	if(debug2)
		cout << "declaration_list()" << endl;
	string tempLine = "";
	//getline(fin, tempLine);
	//fin >> tempLine; // separated by whitespace
	while(fin >> tempLine) // whitespace delimiter
	{
		if(debug2)
			cout << "tempLine: " << tempLine << endl;
		if(tempLine == "begin"){ // no declarations
			if(debug2)
				cout << "Got to 'begin'" << endl;
			return;
		}else if(tempLine == "int"){
			declaration("int");
		}else if(tempLine == "double"){
			declaration("double");
		}else{
			//declaration_list(); // TODO Ask TA
		}
	}
}

void declaration(string type)
{
	string tempWord;
	bool foundSemiColon = false;
	if(debug2)
		cout << "declaration(" << type << ")" << endl;

	while(fin >> tempWord) //; // get next word
	{
		if(debug2)
			cout << "Word: " << tempWord << endl;

		char lastChar = tempWord[tempWord.length()-1]; // get last char ',' or ';'
		if(lastChar ==  ',') // end of line
			foundSemiColon = false;
		else if(lastChar == ';')
			foundSemiColon = true;

		tempWord = tempWord.substr(0,tempWord.length()-1); // remove the last char

		//else new var to add to symbol table
		if(debug2)
			cout << "Creating: " << type << " " << tempWord << endl;
		symbolNode tempNode;
		tempNode.type = type;
		tempNode.symbol = tempWord;
		//tempNode.value = 0 // don't have value to assign yet
		symbolTable.push_back(tempNode);

		if(foundSemiColon == true)
			break; // break out of loop
	}
	return;
}

void statement_list()
{
	if(debug2)
		cout << "statement_list()" << endl;
	string tempWord = "";
	while(fin >> tempWord)
	{
		if(tempWord == "end")
			return;
		else
			statement(tempWord);
	}

	return;
}

void statement(string inWord)
{
	if(inWord == "print")
		printFunc();
	else // id/var case
		assignFunc(inWord);
}

void printFunc()
{
	char tempChar;
	fin >> tempChar;
	if( ('a' <= tempChar && tempChar <= 'z') || ('A' <= tempChar && tempChar <= 'Z') )
	{
		string tWord = "";
		tWord = tempChar;
		int tempIndex = getSymbolIndex(tWord);
		if(tempIndex == -1)
		{
			cout << "Semantic Error: " << tempChar << " does not exists." << endl;
			//return;
		}else{
			cout << symbolTable[tempIndex].value << endl;
			//return;
		}
		fin >> tempChar; // the next char should be the ;
		if(tempChar != ';')
		{
			cout << "Syntax Error: missing ;" << endl;
		}
	}else{
		if(debug2)
			cout << "going to call Exp()" << endl;
		string inLine;
		fin >> inLine;
		inLine = tempChar + inLine.substr(0,inLine.length()-1);
		if(debug2)
			cout << "inLine: " << inLine << endl;
		ExpStream.clear();
		ExpStream.str(inLine);
		cout << Exp();
	}
	return;
}

void assignFunc(string inWord)
{
	if(debug2)
		cout << "assignFucnt(" << inWord << ")" << endl;

	int tempIndex = getSymbolIndex(inWord);
	if(tempIndex == -1){
		cout << "Semantic Error: " << inWord << " does not exists." << endl;
		//return;
	}

	char tempWord;
	fin >> tempWord; // get next char ... should be '='
	if(tempWord != '='){
		cout << "Syntax Error: missing '='" << endl;
		//return;
	}
	//else it is an expression so evaluate it and assign
	string tempLine;
	getline(fin, tempLine);
	//cout << tempLine << endl;
	if(tempLine.find(';') == string::npos){
		cout << "Syntax Error: missing ;" << endl;
	}
	//cout << tempLine << " (1)..." << endl;
	tempLine = tempLine.substr(1,tempLine.length()-2); // remove the space at the front and semilcolon from the end
	if(debug2)
		cout << tempLine << endl;
	ExpStream.clear(); // clear out stream
	ExpStream.str(tempLine); // set string/line/expression as a stream for Exp() and the other functions to use.
	symbolTable[tempIndex].value = Exp(); // evalutate expression and store into the variable
	if(debug2)
		printSymbolTable();
	/*
	char tc;
	cin >> tc;
	*/
}

int Exp()
{
	if(debug1)
		cout << "Exp()" << endl;
	return Exp2(Term()); //Exp() calls Exp2() with the value that Term() returns
}

int Term()
{
	if(debug1)
		cout << "Term()" << endl;
	return Term2(Fact()); // Term() calls Term2() with the value returned from Fact()
}

/*
Exp2(int inp)
	int inp: input value integer
This function will take an integer as input it will then get the next char from the input stream (or file).
If the next char is a + or - we do the respective operations with the current result input and what we get from calling Term()
*/
int Exp2(int inp)
{
	if(debug1)
		cout << "Exp2(" << inp << ")" << endl;
	int result=inp;
	char a;
	if( ExpStream.get(a).eof() == false)
	{
		if(a =='+') // if addition
		{
			result = Exp2(result + Term()); // return number plus next char
			if(debug1)
				cout << "\t" << inp << " + Term() = " << result << endl;
		}
		else if (a =='-') // if subtraction
		{
			result = Exp2(result - Term()); // return number minus next char
			if(debug1)
				cout << "\t" << inp << " - Term() = " << result << endl;
		}
	}
	return result;
}

/*
 Term2(int inp)
 	int inp: input value
This fucntion will take in a number and will then get the next char from the input stream
It will check if the next char (should be operation) is either * or /  and then check
IF it is + or / since * and / has a higher precedence.
	If it is * or / then we call Fact()  to  get the next char which will be the 2nd number.
	Then we either * or / and return the result.
If the next char is + or - then we put the char back ...
If next char is ) then we also put the char back and return current result
*/
int Term2(int inp)
{
	if(debug1)
		cout << "Term2(" << inp << ")" << endl;
	int result = inp;
	char a;
	if( ExpStream.get(a).eof() == false )
	{
		if(a=='*') // if multiplication
		{
			result = Term2(result * Fact()); // return result multiplied by next char
			if(debug1)
				cout << "\t" << inp << " * Fact() = " << result << endl;

		}else if(a=='/') // if division
		{
			result = Term2(result / Fact()); // return result divided by next char
			if(debug1)
				cout << "\t" << inp << " / Fact() = " << result << endl;

		}else if(a == '+' || a=='-') // if addition or subtraction lower precedence or ')'
		{
			ExpStream.putback(a);
			if(debug1)
				cout << "\t" << " putback: " << a << endl;

		}else if( a == ')'){ // if close parenthesis put char back on stream and
			if(debug1)
				cout << "\t putback: )" << endl;
			ExpStream.putback(a);
			//result = Exp(); // not sure what to do after you get to the closing parenthesis
		}
	}
	return result;
}

// reads in one character at a time
// if next char is ^ then perform operation using the next Fact()
int Fact()
{
	if(debug1)
		cout << "Fact() - " << endl;;
	char a;
	int result = Num();
	if(debug1)
		cout << "  Fact() - " << endl;
	ExpStream.get(a);
	if(debug1)
		cout << "\t got: " << a << endl;

	if( a == '^'){ // if read in ^ then return the result ^ Fact() ... in case Fact() could be a string of other operations
		if(debug1)
			cout << "\t result: " << result << " a: " << a << endl;
		return pow(result, Fact());
	}else{
		if(debug1)
			cout << "\t putback: " << a << endl;
		ExpStream.putback(a);
		if(debug1)
			cout << "\t result: " << result << endl; // show current result
		//return Fact();
	}
	//cout << "\t got:" << a << endl;
	//return atoi(&a); // char converted to integer
	return result;
}
/*Num()
 * reads in the next char
 * if next char is ( then the following will be an expression so call Exp()
 * else then it is a terminal so conver from char to int and return that
 */
int Num()
{
	if(debug1)
		cout << "Num() - " << endl;;
	char a;
	ExpStream.get(a);
	if(a == '('){
		if(debug1)
			cout << "\t got: (" << endl;
		return Exp(); // call Exp() and return the result of that
	}else{
		if(debug1)
			cout << "\t got: " << a << endl;
		return atoi(&a);
	}
	//cout << "\t got: " << a << endl;
	//return atoi(&a);
}
