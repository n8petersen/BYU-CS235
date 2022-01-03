#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/** Hash Function Objects Template */
template<typename Key_Type>
struct myHash {};

/** Pair Function Objects Template */
template<typename T1, typename T2>
struct Pair {};

template<typename T2>
struct Pair<string, T2>
{
	string first;
	T2 second;
	friend ostream& operator<<(ostream& os, const Pair& p)
	{
		os << p.first << " => " << p.second;
		return os;
	}
};


/** Map Function Objects Template */
template<typename KEY, typename VALUE>
class HashMap {};

/** Specialzed Map Function Objects Template */
#define DEFAULT_CAPACITY	5

template<typename VALUE>
class HashMap<string, VALUE>
{
private:
	size_t capacity;
	Pair<string, VALUE>* myPairs;
public:
	HashMap() : capacity(DEFAULT_CAPACITY),
		myPairs(new Pair<string,VALUE>[DEFAULT_CAPACITY]) {}
	~HashMap() = default;

	VALUE& operator[](const string& key)
	{
		size_t hashIndex = key[0] % capacity;
		// check load factor...  resize if needed
		while (1)
		{
			if (myPairs[hashIndex].first.length() == 0)
			{
				cout << endl << " " << "Insert " << key;
				myPairs[hashIndex].first = key;
				break;
			}
			if (myPairs[hashIndex].first == key) break;
			cout << endl << " " << key << " collided with " << myPairs[hashIndex].first;
			hashIndex = (hashIndex + 1) % capacity;
		}
		return myPairs[hashIndex].second;
	}
	friend ostream& operator<<(ostream& os, const HashMap& hm)
	{
		for (size_t i = 0; i < hm.capacity; ++i)
		{
			os << endl << " [" << i << ":";
			if (hm.myPairs[i].first != "") os << hm.myPairs[i];
			os << "]";
		}
		return os;
	}
};


int main()
{
	HashMap<string, string> pokemon;
	pokemon["Sharmander"] = "fire";
	pokemon["Squirtle"] = "water";
	cout << endl << "pokemon:" << pokemon;

	cout << endl << "pokemon[\"Sharmander\"] = " << pokemon["Sharmander"];
	cout << endl << "pokemon[\"DogFace\"] = " << pokemon["DogFace"];

	cout << endl << "map DogFace to dog food";
	pokemon["DogFace"] = "dog food";
	cout << endl << "pokemon:" << pokemon;

	return 0;
}
