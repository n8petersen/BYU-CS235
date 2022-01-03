#ifndef STUDENTGRADE_H
#define STUDENTGRADE_H

#include "SNAP.h"
#include "CourseGrade.h"
#include <string>

class StudentGrade
{
public:
	StudentGrade(SNAP* snap, CourseGrade* courseGrade);

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, StudentGrade& student);

private:
	SNAP* snap;
	CourseGrade* courseGrade;
};

#endif STUDENTGRADE_H