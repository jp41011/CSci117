/* CSci 117 - Assignment 2
 * Juan Pedraza 2/9/16
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
*/

// Advanced function declaration
int Exp(), Term(), Exp2(int), Term2(int), Fact(), Num();

//global var with file
ifstream fin;

// main
int main(int argc, char* argv[])
{

	//fin.open("input.txt"); // testing debugging file
	//fin.open("input1.txt");
	//fin.open("input2.txt");
	fin.open("input3.txt");

	cout << "**** Program Start ****" << endl;

	cout << endl << "Result = " << Exp() << endl;
	return 0;
}

int Exp()
{
	cout << "Exp()" << endl;
	return Exp2(Term()); //Exp() calls Exp2() with the value that Term() returns
}

int Term()
{
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

		}else if( a == ')'){ // if close parenthesis put char back on stream and
			cout << "\t putback: )" << endl;
			fin.putback(a);
			//result = Exp(); // not sure what to do after you get to the closing parenthesis
		}
	}
	return result;
}

// reads in one character at a time
// if next char is ^ then perform operation using the next Fact()
int Fact()
{
	cout << "Fact() - " << endl;;
	char a;
	int result = Num();
	cout << "  Fact() - " << endl;
	fin.get(a);
	cout << "\t got: " << a << endl;

	if( a == '^'){ // if read in ^ then return the result ^ Fact() ... in case Fact() could be a string of other operations
		cout << "\t result: " << result << " a: " << a << endl;
		return pow(result, Fact());
	}else{
		cout << "\t putback: " << a << endl;
		fin.putback(a);
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
	cout << "Num() - " << endl;;
	char a;
	fin.get(a);
	if(a == '('){
		cout << "\t got: (" << endl;
		return Exp(); // call Exp() and return the result of that
	}else{
		cout << "\t got: " << a << endl;
		return atoi(&a);
	}
	//cout << "\t got: " << a << endl;
	//return atoi(&a);
}
