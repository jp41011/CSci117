#include <iostream>
#include <fstream>
#include <stdlib.h>

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
int Exp(), Term(), Exp2(int), Term2(int), Fact();

//global var with file
ifstream fin;

// main
int main(int argc, char* argv[])
{
	//printf("**** Program Start ****\n");
	//printf("result=%d\n", Exp());

	// have to open file and save as global var
	//fin.open(argv[1]);
	fin.open("p1.data");


	cout << "**** Program Start ****" << endl;
	/*
	for(int i=0; i < argc; i++)
		cout << argv[i] << " - ";
	*/
	cout << endl << "Result = " << Exp() << endl;
	return 0;
}

int Exp()
{
	//printf("Exp()\n");
	cout << "Exp()" << endl;
	return Exp2(Term()); //
}

int Term()
{
	//printf("Term()\n");
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
	//printf("Exp2(%d)\n", inp);
	cout << "Exp2(" << inp << ")" << endl;
	int result=inp;
	char a;
	//if((a = getchar()) != '\n') // not at the end of the line
	if( fin.get(a).eof() == false)
	{
		if(a =='+') // if addition
		{
			result = Exp2(result + Term()); // return number plus next char
			//printf("%d + Term() = %d\n", inp, result);
			cout << inp << " + Term() = " << result << endl;
		}
		else if (a =='-') // if subtraction
		{
			result = Exp2(result - Term()); // return number minus next char
			//printf("%d - Term() = %d\n", inp, result);
			cout << inp << " - Term() = " << result << endl;
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
*/
int Term2(int inp)
{
	//printf("Term2(%d)\n", inp);
	cout << "Term2(" << inp << ")" << endl;
	int result = inp;
	char a;
	//if((a=getchar()) != '\n') // if not equal to new lin
	if( fin.get(a).eof() == false )
	{
		if(a=='*') // if multiplication
		{
			result = Term2(result * Fact()); // return result multiplied by next char
			//printf("%d * Fact() = %d\n", inp, result);
			cout << inp << " * Fact() = " << result << endl;
		}
		else if(a=='/') // if division
		{
			result = Term2(result / Fact()); // return result divided by next char
			//printf("%d / Fact() = %d\n", inp, result);
			cout << inp << " / Fact() = " << result << endl;
		}
		else if(a == '+' || a=='-') // if addition or subtraction lower precedence
		{
			//ungetc(a, stdin); // do what? put char back ... say what?
			fin.putback(a);
			cout << "putback(" << a << ")" << endl;
		}
	}
	return result;
}

// reads in one character at a time
int Fact()
{
	//char a = getchar();
	//printf("Fact(%c)\n", a); // debug

	char a;
	//int result;
	fin.get(a);
	cout << "Fact(" << a << ")" << endl;
	return atoi(&a); // char converted to integer
	//stringstream ss(a);
	//ss >> result;
	//return result;
}
