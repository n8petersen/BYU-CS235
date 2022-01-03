#include "CourseRoom.h"
#include <iostream>
#include <sstream>

// CONSTRUCTORS
CourseRoom::CourseRoom() // Default Constructor
{
	setCourseName("none");
	courseRoom = "none";
}
CourseRoom::CourseRoom(std::string name, std::string room)
{
	setCourseName(name);
	courseRoom = room;
}


// GET FUNCTIONS
std::string CourseRoom::getRoom() const
{
	return courseRoom;
}



// TOSTRING() FUNCTION
std::string CourseRoom::toString() const
{
	std::ostringstream os;
	os << "cr(" << getCourseName() << "," << courseRoom << ")." << '\n';;
	return os.str();
}

std::ostream& operator<<(std::ostream& os, CourseRoom& courseRoom)
{
	os << courseRoom.toString();
	return os;
}