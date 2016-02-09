/* CSci 117 - Assignment 1
 * Juan Pedraza 2/7/16
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

/*
Program description:
 Num op num op ...
 This program reads in a string of character until it reaches the end of the line
 the pattern should be number, operator, number, operator ...

 Input: String of characters from a file descripting mathematical operations (no spaces)
 Output: Evaluate the mathematical operations and will return the result.

 Compile: gcc prog1.c -o prog1
*/

// Advanced function declaration
int Exp(), Term(), Exp2(int), Term2(int), Fact(), Num();

//global var with file
ifstream fin;

// main
int main(int argc, char* argv[])
{

	fin.open("input.txt"); // file from previous lab
	//fin.open("input1.txt");
	//fin.open("input2.txt");
	//fin.open("input3.txt");

	cout << "**** Program Start ****" << endl;

	cout << endl << "Result = " << Exp() << endl;
	return 0;
}

int Exp()
{
	cout << "Exp()" << endl;
	return Exp2(Term()); //
}

int Term()
{
	cout << "Term()" << endl;
	return Term2(Fact()); // calls Fact() to get the next char
}

/*
Exp2(int inp)
	int inp: input value integer
This function will take an integer as input it will then get the next char from the input stream (or file).
If the next char is a + we add our input value inp to what we get from calling Term()
*/
int Exp2(int inp)
{
	cout << "Exp2(" << inp << ")" << endl;
	int result=inp;
	char a;
	if( fin.get(a).eof() == false)
	{
		if(a =='+') // if addition
		{
			result = Exp2(result + Term()); // return number plus next char
			cout << "\t" << inp << " + Term() = " << result << endl;
		}
		else if (a =='-') // if subtraction
		{
			result = Exp2(result - Term()); // return number minus next char
			cout << "\t" << inp << " - Term() = " << result << endl;
		}/*else if(a == ')'){
			result = Exp2(result);
			cout << "\t" << inp << " )" << result << endl;
		}*/
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
*/
int Term2(int inp)
{
	cout << "Term2(" << inp << ")" << endl;
	int result = inp;
	char a;
	if( fin.get(a).eof() == false )
	{
		if(a=='*') // if multiplication
		{
			result = Term2(result * Fact()); // return result multiplied by next char
			cout << "\t" << inp << " * Fact() = " << result << endl;
		}else if(a=='/') // if division
		{
			result = Term2(result / Fact()); // return result divided by next char
			cout << "\t" << inp << " / Fact() = " << result << endl;
		}else if(a == '+' || a=='-') // if addition or subtraction lower precedence or ')'
		{
			fin.putback(a);
			cout << "\t" << " putback: " << a << endl;
		}else if( a == ')'){
				fin.putback(a);
				cout << "\t" << "putback: " << a << endl;
				Fact();
		}
	}
	return result;
}

// reads in one character at a time
int Fact()
{
	cout << "Fact() - " << endl;;
	char a;
	int result = Num();
	cout << "Fact() - " << endl;
	fin.get(a);
	cout << "\t got: " << a << endl;
	if( a == '^'){
		cout << "\t result: " << result << " a: " << a << endl;
		return pow(result, Fact());
	}else{
		cout << "\t putback: " << a << endl;
		fin.putback(a);
		cout << "\t result: " << result << endl;
		//return Fact();
	}
	//cout << "\t got:" << a << endl;
	//return atoi(&a); // char converted to integer
	return result;
}

int Num()
{
	cout << "Num() - " << endl;;
	char a;
	fin.get(a);
	if(a == '('){
		cout << "\t got: (" << endl;
		return Num(); // not really sure what to do in the case that we read in a '('
	}else{
		cout << "\t got: " << a << endl;
		return atoi(&a);
	}
	//cout << "\t got: " << a << endl;
	//return atoi(&a);
}
