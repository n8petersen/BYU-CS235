#include <fstream>
#include "ExpressionManager.h"

using namespace std;

#ifdef _MSC_VER // Memory leak check
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // Enable memory leak check

	if (argc < 3) // Checks if file names were set
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	ifstream in(argv[1]); // Reading input file
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	else
	{
		cout << argv[1] << " opened successfully.\n";
	}
	ofstream out(argv[2]); // Reading output file
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
	else
	{
		cout << argv[2] << " opened successfully.\n";
	}

	// process input strings
	string line, command, expression;
	ExpressionManager exp;
	while (getline(in, line))
	{
		try
		{
			if (line.size() == 0) continue;
			istringstream iss(line);
			iss >> command;
			if (command == "Expression:") { out << endl; } // Creates a new line if the command is "Expression:"
			out << command << " ";

			if (command == "Expression:")
			{
				expression = line.substr(line.find(": ") + 2, line.size() - 1);
				exp = ExpressionManager(expression);
				out << exp.toString() << endl;
				continue;
			}

			else if (command == "Infix:")
			{
				out << exp.infix() << endl;
				continue;
			}

			else if (command == "Postfix:")
			{
				out << exp.postfix() << endl;
				continue;
			}

			else if (command == "Prefix:")
			{
				out << exp.prefix() << endl;
				continue;
			}

			else if (command == "Value:")
			{
				out << exp.value() << endl;
				continue;
			}

		}
		catch (std::exception&)
		{
			out << "Unexpected command: " << command << endl;
		}
		
	}

	return 0;
}