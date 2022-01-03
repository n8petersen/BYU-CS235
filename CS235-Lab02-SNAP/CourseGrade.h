#ifndef COURSEGRADE_H
#define COURSEGRADE_H

#include "CourseBase.h"
#include <string>

class CourseGrade : public CourseBase
{
public:
	CourseGrade();
	CourseGrade(std::string name, std::string id, std::string grade);

	std::string getStudentID();
	std::string getStudentGrade() const;

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, CourseGrade& courseGrade);

private:
	std::string studentID;
	std::string studentGrade;
};

#endif COURSEGRADE_H