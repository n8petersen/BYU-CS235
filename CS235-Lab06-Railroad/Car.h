#ifndef CAR_H
#define CAR_H

#include <string>
#include <sstream>

struct Car
{
	Car() : numCar(0) {}
	Car(int integer) { numCar = integer; }
	~Car() {}

	unsigned int numCar;

	bool operator==(const Car car) { return this->numCar == car.numCar; }
	bool operator!=(const Car car) { return this->numCar != car.numCar; }

	// Returns the numCar as a string
	std::string toString() const
	{
		std::stringstream out;
		out << numCar;
		return out.str();
	}

	// Make insertion operator for Car
	friend std::ostream& operator<< (std::ostream& os, const Car& c) { return os << c.toString(); }
};


#endif //CAR_H