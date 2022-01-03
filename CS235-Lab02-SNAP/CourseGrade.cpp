#include "CourseGrade.h"
#include <iostream>
#include <sstream>

// CONSTRUCTORS
CourseGrade::CourseGrade() // Default Constructor
{
	setCourseName("none");
	studentID = "0";
	studentGrade = '_';
}
CourseGrade::CourseGrade(std::string name, std::string id, std::string grade)
{
	setCourseName(name);
	studentID = id;
	studentGrade = grade;
}


// GET FUNCTIONS
// TODO: Remove Unneeded Functions
std::string CourseGrade::getStudentID()
{
	return studentID;
}

std::string CourseGrade::getStudentGrade() const
{
	return studentGrade;
}



// TOSTRING() FUNCTION
std::string CourseGrade::toString() const
{
	std::ostringstream os;
	os << "csg(" << getCourseName() << "," << studentID << "," << studentGrade << ")." << '\n';
	return os.str();
}

// Friend << operator calls toString()
std::ostream& operator<<(std::ostream& os, CourseGrade& courseGrade)
{
	os << courseGrade.toString();
	return os;
}