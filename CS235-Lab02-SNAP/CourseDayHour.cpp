#include "CourseDayHour.h"
#include <iostream>
#include <sstream>

// CONSTRUCTORS
CourseDayHour::CourseDayHour() // Default Constructor
{
	setCourseName("none");
	courseDay = '_';
	courseTime = "none";
}
CourseDayHour::CourseDayHour(std::string name, std::string day, std::string hour)
{
	setCourseName(name);
	courseDay = day;
	courseTime = hour;
}


// GET FUNCTIONS
std::string CourseDayHour::getDay() const 
{
	return courseDay;
}

std::string CourseDayHour::getTime() const
{
	return courseTime;
}



// TOSTRING() FUNCTION
std::string CourseDayHour::toString() const
{
	std::ostringstream os;
	os << "cdh(" << getCourseName() << "," << courseDay << "," << courseTime << ")." << '\n';;
	return os.str();
}

std::ostream& operator<<(std::ostream& os, CourseDayHour& courseDayHour)
{
	os << courseDayHour.toString();
	return os;
}