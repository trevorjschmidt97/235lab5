#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H
#include "ExpressionManagerInterface.h"
#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

class ExpressionManager : public ExpressionManagerInterface
{
private:
	string expression_;
	string postFix;

	/**********************************************************************/
	/** THE FOLLOWING ARE "HELPER FUNCTIONS" USED THROUGHOUT THE .H FILE **/
	/**********************************************************************/

	//CHECKS TO SEE IF EXPRESSION IS BALANCED, CODE FOUND FROM CS 235 BOOK
	bool is_balanced(const string& expression)
	{
		stack<char> s;
		bool balanced = true;
		string::const_iterator iter = expression.begin();
		while (balanced && (iter != expression.end()))
		{
			char next_ch = *iter;
			if (isBeginParen(next_ch))
			{
				s.push(next_ch);
			}
			else if (isEndParen(next_ch))
			{
				if (s.empty())
				{
					balanced = false;
				}
				else
				{
					char top_ch = s.top();
					s.pop();
					balanced = matchingParen(top_ch) == next_ch;
				}
			}
			++iter;
		}
		return balanced && s.empty();
	}

	//CHECKS TO SEE IF ITEM IS A PARENTHESIS
	bool isParen(char c) //FOR CHAR
	{
		if (c == '(' || c == '[' || c == '{' || c == ')' || c == ']' || c == '}')
		{
			return true;
		}
		return false;
	} 
	bool isParen(string c) //FOR STRING
	{
		if (c == "(" || c == "[" || c == "{" || c == ")" || c == "]" || c == "}")
		{
			return true;
		}
		return false;
	}
	
	//CHECKS TO SEE IF ITEM IS AN END PARENTHESIS
	bool isEndParen(char c) //FOR CHAR
	{
		if (c == ')' || c == ']' || c == '}')
		{
			return true;
		}
		return false;
	}
	bool isEndParen(string c) //FOR STRING
	{
		if (c == ")" || c == "]" || c == "}")
		{
			return true;
		}
		return false;
	}

	//CHECKS TO SEE IF ITEM IS BEGIN PARENTHESIS
	bool isBeginParen(char c) //FOR CHAR
	{
		if (c == '(' || c == '{' || c == '[')
		{
			return true;
		}
		return false;
	}
	bool isBeginParen(string c) //FOR STRING
	{
		if (c == "(" || c == "{" || c == "[")
		{
			return true;
		}
		return false;
	}

	//RETURNS A PARENTHESIS MATCH
	char matchingParen(char c) //FOR CHAR
	{
		if (c == ')') { return '('; }
		if (c == '[') { return ']'; }
		if (c == '{') { return '}'; }
		if (c == '(') { return ')'; }
		if (c == ']') { return '['; }
		if (c == '}') { return '{'; }
		return 'f'; //indicates error
	}
	string matchingParen(string c) //FOR STRING
	{
		if (c == ")") { return "("; }
		if (c == "[") { return "]"; }
		if (c == "{") { return "}"; }
		if (c == "(") { return ")"; }
		if (c == "]") { return "["; }
		if (c == "}") { return "{"; }
		return "f"; //indicates error
	}

	//CHECKS TO SEE IF ITEM IS AN OPERATOR
	bool isOperator(char c) //FOR CHAR
	{
		if (c == '-' || c == '+' || c == '*' || c == '/' || c == '%')
		{
			return true;
		}
		return false;
	}
	bool isOperator(string c) //FOR STRING
	{
		if (c == "-" || c == "+" || c == "*" || c == "/" || c == "%")
		{
			return true;
		}
		return false;
	}

	//CHECKS TO SEE IF ITEM IS A DIGIT
	bool isDigit(char c) //FOR INDIVIDUAL CHAR
	{
		if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
			c == '6' || c == '7' || c == '8' || c == '9' || c == '0')
		{
			return true;
		}
		return false;
	}
	bool isDigit(string s) //FOR STRING
	{
		for (size_t i = 0; i < s.length(); ++i)
		{
			if (!isdigit(s[i]))
			{
				return false;
			}
		}
		return true;
	}

	//RETURNS PRESEDENCE FOR DIFFERENT OPERATORS OR PARENTHESIS
	int getWeight(char c) //FOR CHAR
	{
		if (c == '*' || c == '/' || c == '%') { return 2; }
		if (c == '-' || c == '+') { return 1; }
		if (c == '(' || c == '[' || c == '{') { return 0; }
		return 999; // Indicates error
	}
	int getWeight(string c) //FOR STRING
	{
		if (c == "*" || c == "/" || c == "%") { return 2; }
		if (c == "-" || c == "+") { return 1; }
		if (c == "(" || c == "[" || c == "{") { return 0; }
		return 999; // Indicates error
	}

	//RETURNS THE ANSWER TO AN OPPERATION
	int applyOp(int a, int b, char op) //FOR CHAR
	{
		if (op == '+') { return a + b; }
		else if (op == '-') { return a - b; }
		else if (op == '*') { return a * b; }
		else if (op == '/' && b != 0) { return a / b; }
		else if (op == '%' && b != 0) { return a % b; }
		else { return 0; }
	}
	int applyOp(int a, int b, string op) //FOR STRING
	{
		if (op == "+") { return a + b; }
		else if (op == "-") { return a - b; }
		else if (op == "*") { return a * b; }
		else if (op == "/" && b != 0) { return a / b; }
		else if (op == "%" && b != 0) {	return a % b; }
		else { return 0; }
	}

public:
	//Constructors / Destructors
	ExpressionManager() { }
	~ExpressionManager() { }

	// Sets the expression later if the constructor is called with no parameters
	virtual void setExpression(string exp)
	{
		this->expression_ = exp;
	}

	/** Return the integer value of the infix expression */
	virtual int value(void)
	{
		stack<int> S;  // Creates value stack of Ints
		for (size_t i = 0; i < postFix.length(); i++) {
			if (postFix[i] == ' ') { continue; }  // If its a space, go past
			else if (isOperator(postFix[i])) // If its an operator
			{
				int operand2 = S.top(); S.pop(); // pop the last two digits off the stack
				int operand1 = S.top(); S.pop();
				int result = applyOp(operand1, operand2, postFix[i]); // evaluate the mini expression
				S.push(result);  // And push it back to the stack
			}
			else if (isDigit(postFix[i])) {  // unless its a digit
				int operand = 0;
				while (i < postFix.length() && isDigit(postFix[i])) // then ifs it a multi digit number
				{
					operand = (operand * 10) + (postFix[i] - '0'); //do this stuff
					i++;
				}
				i--;
				S.push(operand); // then push it to the value stack
			}
		} 
		return S.top();  // At the end, there will only be one value on the stack, return it
	}

	/** Return the infix items from the expression
	Throw an error if the expression
	1) is not balanced.
	2) the number of operators IS NOT one less than the number of operands.
	3) there are adjacent operators. */
	virtual string infix(void)
	{
		stringstream s(expression_); //Create stringstream of infix expression
		string errorCheck; //Create string to be able to parse through stringstream
		stack<string> parenStack;  //Create stack of parenthesis


		//These bools show what the last token was while parsing through the stringstream
		bool pastDigit = false;
		bool pastOperator = false;
		bool pastEndParen = false;
		bool pastOpenParen = false;

		if (expression_ == "")
		{
			throw 11;   // "Invalid Expression"
		}

		else if (!is_balanced(expression_))
		{
			throw 21;    // "Unbalanced"
		}

		while (s >> errorCheck)
		{
			if (isOperator(errorCheck)) //If the token is an operator
			{
				if (pastOperator) { throw 31; } //And the last token was a operator, throw missing operand
				else if (pastOpenParen) { throw 31; }  //And the last token was a open parenthesis, throw a missing operand
				else if (!pastOpenParen && !pastDigit && !pastEndParen && !pastOpenParen) // or if it was the first token
				{
					throw 31; //Throw missing operand
				}

				//reset the bools for the next loop
				pastOperator = true;
				pastDigit = false;
				pastEndParen = false;
				pastOpenParen = false;
			}

			else if (isEndParen(errorCheck)) //If the token is an end parenthesis
			{
				if (pastOperator) { throw 31; }  //And the last token was a operator, throw missing operand
				else if (parenStack.empty() || parenStack.top() != matchingParen(errorCheck)) //And there wasnt an open parenthesis 
				{                                                                             //Or the last parenthesis doesn't match
					throw 21; //throw unbalanced
				}
				else { parenStack.pop(); }  // Or take the matching parenthesis off the stack

				//reset the bools for the next loop
				pastOperator = false;
				pastDigit = false;
				pastEndParen = true;
				pastOpenParen = false;
			}

			else if (isDigit(errorCheck)) //If the token is a digit
			{
				if (pastDigit) { throw 51; } //And the last token was a digit, throw missing operator
				else if (pastEndParen) { throw 51; } //And the last token was an end parenthesis, throw missing operator

				//reset the bools for the next loop
				pastOperator = false;
				pastDigit = true;
				pastEndParen = false;
				pastOpenParen = false;
			}

			else if (isBeginParen(errorCheck))  //If the token is a begining parenthesis
			{
				if (pastDigit) { throw 51; }  //And the last token was a digit, throw missing operator
				else if (pastEndParen) { throw 51; }  //And the last token was a end parenthesis, throw missing operator

				parenStack.push(errorCheck); //Push the parenthesis onto the stack

				//Reset the bools for the next loop
				pastOperator = false;
				pastDigit = false;
				pastEndParen = false;
				pastOpenParen = true;
			}

			else if (!isParen(errorCheck) && !isOperator(errorCheck) && !isDigit(errorCheck)) 
			{                                              //If the token is not any of the 4
				throw 41;  // Throw an illegal operator

				//Reset the bools for the next loop
				pastOperator = false;
				pastDigit = false;
				pastEndParen = false;
				pastOpenParen = false;
			}
		}
		if (pastOperator) { throw 31; } // If the last token was an operator, throw missing operands

		return expression_;  //If no error was thrown, returns the infix expression
	}

	/* Return a postfix representation of the infix expression */
	virtual string postfix(void)
	{
		postFix = " ";  //Initialize postfix to empty string, we will concationate to fill the postfix
		stack<string> operatorStack;   //Initialize the operator stack to an empty stack
		stringstream s(expression_);   //Create stringstream of infix expression
		string input;  //Create string to parse through stringstream
		bool success = true;  //Bool to show success of infix to postfix expression
		                      //Will change to false if something goes bad

		while (s >> input && success) // While there are tokens left, and there has not been a problem
		{
			if (!isParen(input) && !isOperator(input)) //If the token is not a parenthesis or an input
			{                                                                           //(is a digit)
				postFix += input + " "; //Add the token to the postfix with a space
			}

			else if (operatorStack.empty()) //Or if there is no operators on the stack
			{
				operatorStack.push(input);  //Push the token onto the stack
			}

			else if (isBeginParen(input))  //Or if the token is a begining parenthesis
			{
				operatorStack.push(input); //Push the parenthesis onto the stack
			}

			else if (isEndParen(input))  //If the token is an end parenthesis
			{
				while (operatorStack.top() != matchingParen(input) || operatorStack.empty()) //If the stacks not empty and
				{                                                      //while the top operator isnt the parenthesis match
					postFix += operatorStack.top() + " ";  //Add each operator to the postfix
					operatorStack.pop();  //And pop it off the stack
				}
				if (operatorStack.empty() || operatorStack.top() != matchingParen(input))  //If there wasnt a parenthesis match
				{
					success = false;  //Then there was an error in the expression
				}
				else //Of else
				{
					operatorStack.pop();  //Just pop off the matching parenthesis
				}
			}

			else if (isOperator(input))  //If the token is an operator
			{
				while (!operatorStack.empty() && getWeight(input) <= getWeight(operatorStack.top())) //As long as the stack isnt empty
				{                                                                 //And the top of the stack has higher presidence
					postFix += operatorStack.top() + " ";  //append the top of the stack to the postfix
					operatorStack.pop();  // Then pop the stack and continue checking the stack
				}
				operatorStack.push(input);  //Finally push the token to the stack
			}

			else //If the token is an illegal operator
			{
				success = false;  //There was an error in the expression
			}
		}

		while (!operatorStack.empty())  //While there are still operators on the stack
		{
			postFix += operatorStack.top() + " ";  //Append the operator to the postfix
			operatorStack.pop();  //Then pop it off the stack
		}

		return postFix;  //Return the full postfix string
	}

	/** (BONUS) Return a prefix representation of the infix expression */
	virtual string prefix(void)
	{

		/********************************************************/
		//The prefix function is interesting
		//It follows the same pattern as postfix
		//However first, you must reverse the string, then change the parenthesis
		//Then run the postfix function with one small change (shown below in the code)
		//Then reverse the full prefix string and return it
		/*******************************************************/


		reverse(expression_.begin(), expression_.end()); //Reverses the expression

		//Following for loop checks each char and flips the parenthesis
		for (size_t i = 0; i < expression_.length(); i++)
		{
			if (isBeginParen(expression_[i]))
			{
				expression_[i] = matchingParen(expression_[i]);
			}

			else if (isEndParen(expression_[i]))
			{
				expression_[i] = matchingParen(expression_[i]);
			}
		}


		/************************************************************************************************************/
		// This is the same code as the postFix above, however, with one change										//
																													//
		string preFix = " ";																						//
		stack<string> operatorStack;																				//
		stringstream s(expression_);																				//
		string input;																								//
		bool success = true;																						//
																													//
		while (s >> input && success)																				//
		{																											//
			if (!isParen(input) && !isOperator(input))																//
			{																										//
				preFix += input + " ";																				//
			}																										//
																													//
			else if (operatorStack.empty())																			//
			{																										//
				operatorStack.push(input);																			//
			}																										//
																													//
			else if (isBeginParen(input))																			//
			{																										//
				operatorStack.push(input);																			//
			}																										//
																													//
			else if (isEndParen(input))																				//
			{																										//
				while (operatorStack.top() != matchingParen(input) || operatorStack.empty())						//
				{																									//
					preFix += operatorStack.top() + " ";															//
					operatorStack.pop();																			//
				}																									//
				if (operatorStack.empty() || operatorStack.top() != matchingParen(input))							//
				{																									//
					success = false;																				//
				}																									//
				else																								//
				{																									//
					operatorStack.pop();																			//
				}																									//
			}																										//
																													//
			else if (isOperator(input))																				//
			{																										//
				while (!operatorStack.empty() && getWeight(input) < getWeight(operatorStack.top()))					//
				{			// The presendence may be the same	  ^													//
					preFix += operatorStack.top() + " ";															//
					operatorStack.pop();																			//
				}																									//
				operatorStack.push(input);																			//
			}																										//
																													//
			else																									//
			{																										//
				success = false;																					//
			}																										//
		}																											//
																													//
		while (!operatorStack.empty())																				//
		{																											//
			preFix += operatorStack.top() + " ";																	//
			operatorStack.pop();																					//
		}																											//
		/************************************************************************************************************/

		// Then go through and flip the parenthesis back on the expression string
		for (size_t i = 0; i < expression_.length(); i++)
		{
			if (isEndParen(expression_[i]))
			{
				expression_[i] = matchingParen(expression_[i]);
			}

			else if (isBeginParen(expression_[i]))
			{
				expression_[i] = matchingParen(expression_[i]);
			}
		}
		reverse(expression_.begin(), expression_.end()); //And finally fix the expression string back to normal

		reverse(preFix.begin(), preFix.end());  //Then reverse the preFix string
		return preFix;  //And return it
	}


};
#endif // EXPRESSION_MANAGER_H
