//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef EXPRESSION_INTERFACE_H
#define EXPRESSION_INTERFACE_H
#include <string>
using namespace std;

class ExpressionManagerInterface
{
public:
	ExpressionManagerInterface(void) {};
	virtual ~ExpressionManagerInterface(void) {};
	virtual void setExpression(string exp) = 0;
	virtual int value(void) = 0;
	virtual std::string infix(void) = 0;
	virtual std::string postfix(void) = 0;
	virtual std::string prefix(void) = 0;
	//There was no use having the toString function, so I deleted it
};
#endif	// EXPRESSION_INTERFACE_H