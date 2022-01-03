#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class SNAP
{
public:
	SNAP();
	SNAP(std::string id, std::string name, std::string address, std::string phone);

	std::string getStudentID() const;
	std::string getStudentName() const;

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, SNAP& snap);
private:
	std::string studentID;
	std::string studentName;
	std::string studentAddress;
	std::string studentPhone;

};

#endif STUDENT_H