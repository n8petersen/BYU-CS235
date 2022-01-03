#include "StudentSchedule.h"
#include <iostream>
#include <sstream>

// Constructors
StudentSchedule::StudentSchedule(std::string courseName, std::string days, std::string time, std::string room)
{
	this->courseName = courseName;
	this->days = days;
	this->time = time;
	this->room = room;
}

// TOSTRING() FUNCTION
std::string StudentSchedule::toString() const
{
	std::ostringstream os;
	os << "  " << courseName << " " << days << " " << time << ", " << room << '\n';
	return os.str();
}

// Friend << operator calls toString()
std::ostream& operator<<(std::ostream& os, StudentSchedule& schedule)
{
	os << schedule.toString();
	return os;
}