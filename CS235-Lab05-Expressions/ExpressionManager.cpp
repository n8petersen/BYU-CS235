#include "ExpressionManager.h"

using namespace std;

// PRIVATE FUNCTIONS

ExpressionManager::ParseType ExpressionManager::parse(string s)
{
	parseValue = "";
	while (index != s.size())
	{
		switch (s.at(index))
		{
		case '(':
		case '[':
		case '{':
			parseValue = s.at(index);
			index++;
			return opener;
			break;
		case ')':
		case ']':
		case '}':
			parseValue = s.at(index);
			index++;
			return closer;
			break;


		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			parseValue += s.at(index);
			break;

		case '*':
		case '/':
		case '%':
		case '+':
		case '-':
			parseValue = s.at(index);
			index++;
			return operate;
			break;


		case ' ':
			break;

		default:
			index++;
			return illegal;
			break;
		}

		index++;

		if (parseValue.size() > 0)
		{
			// Checks if next index is a number, if it is not, return num
			if (index == s.size() || (index < s.size()
				&& (s.at(index) < '0' || s.at(index) > '9')))
			{
				return num;
			}
		}
	}
	return endline;
}

std::string ExpressionManager::prefixPrep(string s)
{
	if (checkBalance() == false)
		return "Unbalanced";

	s = "(" + s + ")";
	stack<string> stack;
	string outputString;

	ParseType parseType = parse(s);
	while (parseType != endline)
	{
		// If the scanned character is an operand (number),
		// add it to output string.
		if (parseType == num)
			outputString = outputString + parseValue + " ";

		else if (parseType == operate)
		{
			while (!stack.empty() && prefix_prec(parseValue)
				< prefix_prec(stack.top()))
			{
				outputString = outputString + stack.top() + " ";
				stack.pop();
			}
			stack.push(parseValue);
		}

		// If the scanned character is an opener
		// (, [, or { - push it to the stack.
		else if (parseType == opener)
			stack.push(parseValue);

		// If the scanned character
		// is a closer ), ], or }
		// - pop and to output string from stack
		// until an ‘(‘ is encountered.
		else if (parseType == closer)
		{
			while (stack.top() != "(" && stack.top() != "[" && stack.top() != "{")
			{
				outputString = outputString + stack.top() + " ";
				stack.pop();
			}
			stack.pop(); // Removes opener from stack
		}

		// If space, do nothing
		else if (parseValue == " ") {}

		parseType = parse(s);
	}

	// Pop all the remaining elements from the stack
	while (!stack.empty())
	{
		outputString = outputString + stack.top() + " ";
		stack.pop();
	}

	resetIndex();
	return outputString;
}

void ExpressionManager::evaluate(stack<int>&operands, stack<string>&operators)
{
	int a, b, c;
	b = operands.top();
	operands.pop();

	a = operands.top();
	operands.pop();

	switch (operators.top().at(0))
	{
	case '+':
		c = a + b;
		break;
	case '-':
		c = a - b;
		break;
	case '*':
		c = a * b;
		break;
	case '/':
		c = a / b;
		break;
	case '%':
		c = a % b;
		break;
	}
	operands.push(c);
	operators.pop();
}

bool ExpressionManager::checkBalance()
{
	string expr = "[ " + expression_ + " ]";
	stack<char> s;
	char x;

	// Traversing the Expression
	for (int i = 0; i < expr.length(); i++)
	{
		if (expr[i] == '(' || expr[i] == '['
			|| expr[i] == '{')
		{
			// Push the element in the stack
			s.push(expr[i]);
			continue;
		}

		// IF current current character is not opening
		// bracket, then it must be closing. So stack
		// cannot be empty at this point.
		if (s.empty())
			return false;

		switch (expr[i]) {
		case ')':

			// Store the top element in a
			x = s.top();
			s.pop();
			if (x == '{' || x == '[')
				return false;
			break;

		case '}':

			// Store the top element in b
			x = s.top();
			s.pop();
			if (x == '(' || x == '[')
				return false;
			break;

		case ']':

			// Store the top element in c
			x = s.top();
			s.pop();
			if (x == '(' || x == '{')
				return false;
			break;
		}
	}

	// Check Empty Stack
	return (s.empty());
}

int ExpressionManager::postfix_prec(string s)
{
	if (s == "/" || s == "*" || s == "%")
		return 2;

	else if (s == "+" || s == "-")
		return 1;

	else return -1;
}

int ExpressionManager::prefix_prec(string s)
{
	if (s == "-" || s == "+")
		return 1;

	else if (s == "*" || s == "/" || s == "%")
		return 2;

	else return 0;
}

// PUBLIC FUNCTIONS
int ExpressionManager::value()
{
	stack<int> operands;
	stack<string> operators;
	string infixString = infix();
	ParseType parseType = parse(expression_);
	while (parseType != endline)
	{
		// If the scanned character is an
		// operand (number), add it to output string.
		if (parseType == num)
		{
			operands.push(stoi(parseValue));
		}

		// If an operator is scanned
		else if (parseType == operate)
		{
			// Check that list is empty and the precedence
			// of scanned value compared to what's on top of stack
			while (!operators.empty() && postfix_prec(parseValue)
				<= postfix_prec(operators.top()))
			{
				evaluate(operands, operators);
			}
			operators.push(parseValue);
		}

		// If the scanned character is an opener
		// (, [, or { -push it to the stack.
		else if (parseType == opener)
		{
			operators.push(parseValue);
		}

		// If the scanned character is a
		// closer ), ], or } - pop and output to string
		// from the stack until an ‘(‘ is encountered.
		else if (parseType == closer)
		{
			while (operators.top() != "(" && operators.top()
				!= "[" && operators.top() != "{")
			{
				evaluate(operands, operators);
			}
			operators.pop();
		}

		// If space, do nothing
		else if (parseValue == " ") {}

		parseType = parse(expression_);
	}

	// Pop all the remaining elements from the stack
	while (!operators.empty())
	{
		evaluate(operands, operators);
	}

	resetIndex();
	return operands.top();
}

std::string ExpressionManager::infix()
{
	if (checkBalance() == false)
		return "Unbalanced";

	string infixString;
	ParseType parseType = parse(expression_);
	while (parseType != endline)
	{
		// Throws 'Illegal Operator' if it parseType returns illegal
		if (parseType == illegal)
			return "Illegal Operator";

		infixString = infixString + parseValue + " ";
		//parseType = parse(expression_);
		if (parseType == num)
		{
			// Throws 'Missing Operator' if it detects two numbers in a row
			parseType = parse(expression_);
			if (parseType == num)
				return "Missing Operator";
		}

		else if (parseType == operate)
		{
			// Throws 'Missing Operand' if it detects two operators in a row
			parseType = parse(expression_);
			if (parseType == operate || parseType == endline)
				return "Missing Operand";
		}

		else parseType = parse(expression_);
	}

	resetIndex();
	return infixString;
}

std::string ExpressionManager::postfix()
{
	if (checkBalance() == false)
		return "Unbalanced";

	stack<string> stack;
	string postfixString;
	string infixString = infix();

	ParseType parseType = parse(expression_);
	while (parseType != endline)
	{
		// If the scanned character is an 
		// operand (number), add it to output string.
		if (parseType == num)
		{
			postfixString = postfixString + parseValue + " ";
		}

		// If an operator is scanned
		else if (parseType == operate)
		{
			// Check that list is empty and the precedence 
			// of scanned value compared to what's on top of stack
			while (!stack.empty() && postfix_prec(parseValue)
				<= postfix_prec(stack.top()))
			{
				postfixString = postfixString + stack.top() + " ";
				stack.pop();
			}
			stack.push(parseValue);
		}

		// If the scanned character is an opener 
		// (, [, or { -push it to the stack.
		else if (parseType == opener)
		{
			stack.push(parseValue);
		}

		// If the scanned character is a 
		// closer ), ], or } - pop and output to string 
		// from the stack until an ‘(‘ is encountered.
		else if (parseType == closer)
		{
			while (stack.top() != "(" && stack.top()
				!= "[" && stack.top() != "{")
			{
				postfixString = postfixString + stack.top() + " ";
				stack.pop();
			}
			stack.pop();
		}

		// If space, do nothing
		else if (parseValue == " ") {}

		parseType = parse(expression_);
	}

	// Pop all the remaining elements from the stack
	while (!stack.empty())
	{
		postfixString = postfixString + stack.top() + " ";
		stack.pop();
	}

	resetIndex();
	return postfixString;
}

std::string ExpressionManager::prefix()
{
	if (checkBalance() == false)
		return "Unbalanced";

	// Creates a standardized string 'str' 
	// using infix function
	string str = infix();

	// Reverses str
	// Note: Since it gets reversed twice, numbers of 
	// multiple digits will end up normal at the end  ie. 10 -> 01 -> 10
	reverse(str.begin(), str.end());

	// Replaces braces with their
	// opposite corresponding brace
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(') { str[i] = ')'; i++; }
		else if (str[i] == ')') { str[i] = '('; i++; }

		if (str[i] == '[') { str[i] = ']'; i++; }
		else if (str[i] == ']') { str[i] = '['; i++; }

		if (str[i] == '{') { str[i] = '}'; i++; }
		else if (str[i] == '}') { str[i] = '{'; i++; }
	}

	// Runs prefixPrep function (modified postfix function)
	// on str to make prefixString
	string prefixString = prefixPrep(str);

	// Reverses prefixString 
	reverse(prefixString.begin(), prefixString.end());

	string returnString = prefixString.substr(1, prefixString.size() - 1) + " "; // Fixes white space issues
	return returnString;
}