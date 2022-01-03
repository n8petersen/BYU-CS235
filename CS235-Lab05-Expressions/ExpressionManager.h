#ifndef EXPRESSION_MANAGER
#define EXPRESSION_MANAGER

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include "ExpressionManagerInterface.h"

using namespace std;

class ExpressionManager :
    public ExpressionManagerInterface
{
private:
	string expression_;
	int index = 0;
	enum ParseType { opener, closer, num, operate, endline, illegal };
	string parseValue = "";

	ParseType parse(string s);

	std::string prefixPrep(string s);

	void evaluate(stack<int>& operands, stack<string>& operators);

	void resetIndex() { index = 0; }

	bool checkBalance();

	int postfix_prec(string s);

	int prefix_prec(string s);

public:
	ExpressionManager() {}
	ExpressionManager(string inputExpression) { expression_ = inputExpression; }
	~ExpressionManager() {}

	/** Return the integer value of the infix expression */
	int value();

	/** Return the infix items from the expression
		Throw an error if not a valid infix expression as follows:
		First check to see if the expression is balanced ("Unbalanced"),
		then throw the appropriate error immediately when an error is found
		(ie., "Missing Operand", "Illegal Operator", "Missing Operator") */
	std::string infix();
	
	/** Return a postfix representation of the infix expression */
	std::string postfix();
	
	/** Return a prefix representation of the infix expression */
	std::string prefix();
	
	/** Return the infix vector'd expression items */
	string toString() const
	{
		std::ostringstream os;
		os << expression_;
		return os.str();
	}

    friend ostream& operator<<(ostream& os, ExpressionManager& expression)
    {
		return os << expression.toString();
    }

};

#endif //EXPRESSION_MANAGER