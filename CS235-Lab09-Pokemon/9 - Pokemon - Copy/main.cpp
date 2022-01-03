#include <iostream>
#include <fstream>


#include "Set.h"
#include "HashMap.h"

using namespace std;

#ifdef _MSC_VER // Memory leak check
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

/** This is a helper function for the battle functionality **/
/* Given an int (damageAToB or damageBToA), returns a string of the effectivity */
string moveEffective(int value)
{
	if (value == -1)
	{
		return "ineffective";
	}
	else if (value == 0)
	{
		return "effective";
	}
	else if (value == 1)
	{
		return "super effective";
	}
	else
	{
		return "unknown effective";
	}
}

int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // Enable memory leak check
	if (argc < 3) // Checks if file names were set
	{
		std::cerr << "Please provide name of input and output files";
		return 1;
	}
	std::ifstream in(argv[1]); // Reading input file
	if (!in)
	{
		std::cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	else
	{
		std::cout << argv[1] << " opened successfully.\n";
	}
	std::ofstream out(argv[2]); // Reading output file
	if (!out)
	{
		in.close();
		std::cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
	else
	{
		std::cout << argv[2] << " opened successfully.\n";
	}


	//\/\/ Program Starts Here /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\
	

	HashMap<string, string> pokemons;
	HashMap<string, string> moves;
	HashMap<string, Set<string>> effectives;
	HashMap<string, Set<string>> ineffectives;

	std::string line;
	while (getline(in, line))
	{
		std::string command;

		try
		{
			if (line.size() == 0) continue;
			std::istringstream iss(line);
			iss >> command;

			if (command == "Set:")
			{
				out << line << endl;

				Set<string> set;
				string value;
				while (iss >> value)
				{
					set.insert(value);
				}
				out << "  [" << set << "]" << endl;
			}

			/** Given a Pokemon, insert what that type it is **/
			else if (command == "Pokemon:")
			{
				out << line;

				string pokemonName, pokeType;
				iss >> pokemonName >> pokeType;
				pokemons[pokemonName] = pokeType;
			}

			/** Given a move, insert what that type it is **/
			else if (command == "Move:")
			{
				out << line;

				string moveName, pokeType;
				iss >> moveName >> pokeType;
				moves[moveName] = pokeType;
			}

			/** Given a type, insert what that type is effective against **/
			else if (command == "Effective:")
			{
				out << line;
				Set<string> effectiveTypes;
				string type, value;
				iss >> type;
				while (iss >> value)
				{
					effectiveTypes.insert(value);
				}
				effectives[type] = effectiveTypes;
			}

			/** Given a type, insert what that type is ineffective against **/
			else if (command == "Ineffective:")
			{
				out << line;
				Set<string> ineffectiveTypes;
				string type, value;
				iss >> type;
				while (iss >> value)
				{
					ineffectiveTypes.insert(value);
				}
				ineffectives[type] = ineffectiveTypes;
			}

			/** Output all pokemon and their types **/
			else if (command == "Pokemon")
			{
				out << endl << line << pokemons;
			}

			/** Output all the moves and what their type **/
			else if (command == "Moves")
			{
				out << endl << line << moves;
			}

			/** Output all the types and what they're effective against **/
			else if (command == "Effectivities")
			{
				out << endl << line << effectives;
			}

			/** Output all the types and what they're ineffective against **/
			else if (command == "Ineffectivities")
			{
				out << endl << line << ineffectives;
			}

			/** Output the pokemon and move types, and the result of the battle **/
			else if (command == "Battle:")
			{
				out << endl << line << endl;

				string pokemonA, pokemonB, moveA, moveB;
				iss >> pokemonA >> moveA >> pokemonB >> moveB;

				/* Determines the effectivity of the Pokemon's moves against each other*/
				int damageAToB = effectives[moves[moveA]].count(pokemons[pokemonB])
					- ineffectives[moves[moveA]].count(pokemons[pokemonB]);
				int damageBToA = effectives[moves[moveB]].count(pokemons[pokemonA])
					- ineffectives[moves[moveB]].count(pokemons[pokemonA]);
						

				/* Output pokemon(move) and the pokemons' types */
				out << "  " << pokemonA << " (" << moveA << ")" << " vs " << pokemonB << " (" << moveB << ")" << endl;
				out << "  " << pokemonA << " is a ";
				out << pokemons[pokemonA] << " type Pokemon." << endl;

				out << "  " << pokemonB << " is a ";
				out << pokemons[pokemonB] << " type Pokemon." << endl;


				/* Output the moves' types */
				out << "  " << moveA << " is a ";
				out << moves[moveA] << " type move." << endl;

				out << "  " << moveB << " is a ";
				out << moves[moveB] << " type move." << endl;


				/* Output the types that Pokemon A's move is effective against */
				out << "  " << moveA << " is super effective against [";
				out << effectives[moves[moveA]] << "] type Pokemon." << endl;

				out << "  " << moveA << " is ineffective against [";
				out << ineffectives[moves[moveA]] << "] type Pokemon." << endl;


				/* Output the effectivity of Pokemon A's move against Pokemon B*/
				out << "  " << pokemonA << "'s " << moveA << " is ";
				out << moveEffective(damageAToB) << " against " << pokemonB << endl;

				/* Output the types that Pokemon B's move is effective against */
				out << "  " << moveB << " is super effective against [";
				out << effectives[moves[moveB]] << "] type Pokemon." << endl;

				out << "  " << moveB << " is ineffective against [";
				out << ineffectives[moves[moveB]] << "] type Pokemon." << endl;


				/* Output the effectivity of Pokemon B's move against Pokemon A*/
				out << "  " << pokemonB << "'s " << moveB << " is ";
				out << moveEffective(damageBToA) << " against " << pokemonA << endl;


				/* Outputs the winner of the battle, or if it's a tie */
				if ((damageAToB - damageBToA) == 0) // Battle is a tie
				{
					out << "  The battle between " << pokemonA;
					out << " and " << pokemonB << " is a tie." << endl;
				}
				else if ((damageAToB - damageBToA) > 0) // Pokemon A wins
				{
					out << "  In the battle between " << pokemonA << " and ";
					out << pokemonB << ", " << pokemonA << " wins!" << endl;
				}
				else if ((damageAToB - damageBToA) < 0) // Pokemon B wins
				{
					out << "  In the battle between " << pokemonA << " and ";
					out << pokemonB << ", " << pokemonB << " wins!" << endl;
				}
			}
			out << endl;
		}
		catch (std::string& error) { out << error; }
	}

	return 0;
}