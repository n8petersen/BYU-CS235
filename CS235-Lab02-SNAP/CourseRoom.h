#ifndef COURSEROOM_H
#define COURSEROOM_H

#include "CourseBase.h"
#include <string>

class CourseRoom : public CourseBase
{
public:
	CourseRoom();
	CourseRoom(std::string name, std::string room);

	std::string getRoom() const;

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, CourseRoom& courseRoom);

private:
	std::string courseRoom;
};

#endif COURSEROOM_H