#include "CourseBase.h"

// CONSTRUCTORS
CourseBase:: CourseBase() // Default Constructor
{
	courseName = "none";
}
CourseBase::CourseBase(std::string name)
{
	courseName = name;
}


// GET FUNCTION
std::string CourseBase::getCourseName() const
{
	return courseName;
}


// SET FUNCTION
void CourseBase::setCourseName(std::string name)
{
	courseName = name;
}



// TOSTRING() FUNCTION
std::string CourseBase::toString() const
{
	std::ostringstream os;
	os << courseName;
	return os.str();
}

// Friend << operator calls toString()
std::ostream& operator<<(std::ostream& os, CourseBase& courseBase)
{
	os << courseBase.toString();
	return os;
}