#ifndef COURSEDAYHOUR_H
#define COURSEDAYHOUR_H

#include "CourseBase.h"
#include <string>

class CourseDayHour : public CourseBase
{
public:
	CourseDayHour();
	CourseDayHour(std::string name, std::string day, std::string hour);

	std::string getDay() const;
	std::string getTime() const;

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, CourseDayHour& courseDayHour);

private:
	std::string courseDay;
	std::string courseTime;
};

#endif COURSEDAYHOUR_H