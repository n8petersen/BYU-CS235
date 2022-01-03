#ifndef STUDENTSCHEDULE_H
#define STUDENTSCHEDULE_H

#include "CourseRoom.h"
#include "CourseDayHour.h"
#include <string>

class StudentSchedule
{
public:
	StudentSchedule(std::string courseName, std::string days, std::string time, std::string room);

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, StudentSchedule& student);

private:
	std::string courseName;
	std::string days;
	std::string time;
	std::string room;
};

#endif STUDENTSCHEDULE_H