//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef QSINTERFACE_H_
#define QSINTERFACE_H_
#include <string>

template<typename T>
class QSInterface
{
public:
	QSInterface() {}
	virtual ~QSInterface() {}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element) = 0;

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right) = 0;

	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll() = 0;

	/** Removes all items from the QuickSort array. */
	virtual bool clear() = 0;

	/** Return size of the QuickSort array. */
	virtual size_t capacity() const = 0;

	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const = 0;

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	   middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if  1) the array is empty,
	              2) if either of the given integers is out of bounds,
	              3) or if the left index is not less than the right index.
	*/
	virtual int medianOfThree(size_t left, size_t right) = 0;

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values less than or equal to the pivot should be placed to the left of the pivot;
	the values greater than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if  1) the array is empty,
	              2) if any of the given indexes are out of bounds,
	              3) if the left index is not less than the right index.
	*/
	virtual int partition(size_t left, size_t right, size_t pivotIndex) = 0;

	/** @return: comma delimited string representation of the array. */
	virtual std::string toString() const = 0;
};

#endif /* QSINTERFACE_H_ */
