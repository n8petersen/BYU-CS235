//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef HASH_MAP_INTERFACE_H
#define HASH_MAP_INTERFACE_H
#include <string>

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

template <typename K, typename V>
class HashMapInterface
{
public:
	HashMapInterface() {}
	virtual ~HashMapInterface() {}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key) = 0;

	/** @return: the number of elements that match the key in the Map. */
	virtual size_t count(const K& key) = 0;

	/** Removes all items from the Map. */
	virtual void clear(void) = 0;

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size(void) const = 0;

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size(void) const = 0;

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString(void) const = 0;
};
#endif // HASH_MAP_INTERFACE_H