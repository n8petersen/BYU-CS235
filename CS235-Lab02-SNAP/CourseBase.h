#ifndef COURSEBASE_H
#define COURSEBASE_H

#include <string>
#include <iostream>
#include <sstream>

class CourseBase
{
public:
	CourseBase();
	CourseBase(std::string name);

	std::string getCourseName() const;

	void setCourseName(std::string name);

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, CourseBase& courseBase);

private:
	std::string courseName;
};

#endif COURSEBASE_H