#include "StudentGrade.h"
#include <iostream>

// Constructors
StudentGrade::StudentGrade(SNAP* snap, CourseGrade* courseGrade)
{
	this->snap = snap;
	this->courseGrade = courseGrade;
}

std::string StudentGrade::toString() const 
{
	std::ostringstream os;
	os << courseGrade->getCourseName() << "," << snap->getStudentName() << "," << courseGrade->getStudentGrade() << '\n';
	return os.str();
}

// Friend << operator calls toString()
std::ostream& operator<<(std::ostream& os, StudentGrade& student)
{
	os << student.toString();
	return os;
}