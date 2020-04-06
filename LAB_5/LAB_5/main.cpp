#include "ExpressionManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	/****************************************************************************/
	// Sets us input and output files, returns error if something happens		//
	if (argc < 3)																//
	{																			//
		cerr << "Please provide name of input and output files";				//
		return 1;																//
	}																			//
	cout << "Input file: " << argv[1] << endl;									//
	ifstream in(argv[1]);														//
	if (!in)																	//
	{																			//
		cerr << "Unable to open " << argv[1] << " for input";					//
		return 2;																//
	}																			//
	cout << "Output file: " << argv[2] << endl;									//
	ofstream out(argv[2]);														//
	if (!out)																	//
	{																			//
		in.close();																//
		cerr << "Unable to open " << argv[2] << " for output";					//
		return 3;																//
	}																			//
	/****************************************************************************/

	string input; // Creates string to parse through input file
	ExpressionManager *expressionObject = new ExpressionManager;  
	//creates one instance of the expression class

	
		while (in >> input) //While there are more tokens in the input
		{
			try  
			{
				if (input == "Expression:")  //If the line is expression
				{
					out << endl << input;  // Out "Expression:"
					getline(in, input);  // Read in the full expression
					out << input;  //out expression
					expressionObject->setExpression(input);  //Then set expression in the expression manager class
				}
				if (input == "Infix:")  //If the line is prompt for infix
				{
					out << input; //Out "Infix:"
					out << expressionObject->infix(); //outs the result of infix function... if error, throws to catch
				}
				if (input == "Postfix:")  //If the line is prompt for postfix
				{
					out << input << expressionObject->postfix();  //Outs "Postfix:" and result of postfix expression
				}
				if (input == "Prefix:")  //If the line is prompt for prefix
				{
					out << input << expressionObject->prefix();  //outs "Prefix:" and result of prefix expression
				}
				if (input == "Value:")  //If the line is prompt for value
				{
					out << input << " " << expressionObject->value(); //outs "Value: " and result of value expression
				}
				out << endl;
			}

			catch (int catchedInt)  //Reads in caught erros
			{
				if (catchedInt == 11) { out << " Invalid expression" << endl; }  //Outs error if thrown from Infix function
				if (catchedInt == 21) { out << " Unbalanced"         << endl; }
				if (catchedInt == 31) { out << " Missing Operand"    << endl; }
				if (catchedInt == 41) { out << " Illegal Operator"   << endl; }
				if (catchedInt == 51) {	out << " Missing Operator"   << endl; }
			}
		}

	delete  expressionObject; //Frees the memory
	//system("pause");
	return 0;
}