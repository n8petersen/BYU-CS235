#include "SNAP.h"
#include <iostream>
#include <sstream>

// CONSTRUCTORS
SNAP::SNAP() // Default Constructor
{
	studentID = "0";
	studentName = "none";
	studentAddress = "none";
	studentPhone = "none";
}
SNAP::SNAP(std::string id, std::string name, std::string address, std::string phone)
{
	studentID = id;
	studentName = name;
	studentAddress = address;
	studentPhone = phone;
}


// GET FUNCTIONS
std::string SNAP::getStudentID() const
{
	return studentID;
}

std::string SNAP::getStudentName() const
{
	return studentName;
}


// TOSTRING() FUNCTION
std::string SNAP::toString() const
{
	std::ostringstream os;
	os << studentName << ", " << studentID << ", " << studentAddress << ", " << studentPhone << '\n';
	return os.str();
}


std::ostream& operator<<(std::ostream& os, SNAP& snap)
{
	os << snap.toString();
	return os;
}