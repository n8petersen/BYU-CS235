#ifndef HASHMAP_H
#define HASHMAP_H

#include <sstream>
#include "Pair.h"
#include "HashMapInterface.h"

using namespace std;

template<typename K, typename V>
class HashMap : public HashMapInterface<K, V>
{
private:
	size_t capacity;
	Pair<K, V>* myPairs;
	double load;
	int hashValue = HASH_CONSTANT;

	/* Reallocates the Pair Array to be twice as large */
	/* This sort of works as is, but it isn't hashing the values into the new array properly.*/
	void reallocate() 
	{
		// Creates new array of twice the size
		// Doubles current capacity
		// Swaps the old array with the new one
		Pair<K, V>* tempPairs = new Pair<K, V>[2 * capacity]; 
		capacity = 2 * capacity;	
		std::swap(myPairs, tempPairs);	

		// Moves everything from old array to new array by rehashing them.
		for (size_t i = 0; i < capacity / 2; ++i) 
		{
			if (!tempPairs[i].isEmpty())
			{
				myPairs[hash(tempPairs[i].first)].second = tempPairs[i].second;
			}
		}

		// Deletes the old array
		delete[] tempPairs;	
	}

	/* Returns a hash value based off a given key */
	int hash(const K& key)
	{
		int hashIndex = 0;
		long long sum = 0;
		size_t n = key.length();

		// Loops through the whole string
		for (size_t i = 0; i < key.length(); ++i) 
		{
			// Evaluates the exponent
			long long exponent = 1;
			n--;
			for (size_t j = 0; j < n; ++j) 
			{
				exponent *= HASH_CONSTANT;
			}

			// Adds to the running sum
			sum += key[i] * exponent; 
		}

		// Gets index based off sum and capacity
		hashIndex = sum % capacity; 

		int k = 1;

		while (1)
		{
			// If the key slot is empty, insert it there
			if (myPairs[hashIndex].first.length() == 0)
			{
				cout << " " << "Insert " << key << endl;
				myPairs[hashIndex].first = key;
				break;
			}

			// If the key already exists, don't insert again
			else if (myPairs[hashIndex].first == key)
			{
				break;
			}

			// Otherwise, where there is a collision
			cout << endl << " " << key << " collided with " << myPairs[hashIndex].first;
			
			// Add k to Index,
			// Mod the index,
			// Increment k by 2
			hashIndex = (hashIndex + k) % capacity;	
			k += 2;	
		}
		return hashIndex;
	}


public:
	HashMap() :
		capacity(DEFAULT_MAP_HASH_TABLE_SIZE),
		myPairs(new Pair<K, V>[DEFAULT_MAP_HASH_TABLE_SIZE]),
		load(0.00)  {}
		
	~HashMap() 
	{ 
		delete[] myPairs;
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key)
	{	
		// Determines if needed to reallocate by comparing current load to threshold
		load = (static_cast<double>(size()) / static_cast<double>(capacity)) * 100; 
		if (load >= LOAD_THRESHOLD) 
		{
			cout << "Time to reallocate!";
			reallocate();
		}

		int hashIndex = hash(key);
		return myPairs[hashIndex].second;
	}

	/** @return: the number of elements that match the key in the Map. */
	virtual size_t count(const K& key)
	{
		size_t numItems = 0;

		for (size_t i = 0; i < capacity; ++i)
		{
			if (myPairs[i].first == key)
			{
				numItems++;
			}
		}
		return numItems;
	}

	/** Removes all items from the Map. */
	virtual void clear()
	{
		delete[] myPairs;
		new Pair<K, V>[DEFAULT_MAP_HASH_TABLE_SIZE];
		capacity = DEFAULT_MAP_HASH_TABLE_SIZE;
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size() const
	{
		size_t numItems = 0;
		
		for (size_t i = 0; i < capacity; ++i)
		{
			if (!myPairs[i].isEmpty())
			{
				numItems++;
			}
		}
		return numItems;
	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size() const
	{
		return capacity;
	}

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString() const
	{
		stringstream os, osLoop;
		size_t numItems = 0;
		for (size_t i = 0; i < capacity; ++i)
		{
			if (!myPairs[i].isEmpty())
			{
				osLoop << endl << "  [" << i << ":" << myPairs[i].first << "->" << myPairs[i].second << "]";
				numItems++;
			}
		}
		os << ": " << numItems << "/" << capacity << osLoop.str();// << endl;
		return os.str();
	}

	/** friend << operator **/
	friend ostream& operator<<(ostream& os, HashMap& map)
	{
		return os << map.toString();
	}
};

#endif //HASHMAP_H