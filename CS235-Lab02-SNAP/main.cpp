#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "StudentGrade.h"
#include "StudentSchedule.h"
#include "SNAP.h"
#include "CourseBase.h"
#include "CourseGrade.h"
#include "CourseRoom.h"
#include "CourseDayHour.h"

#ifdef _MSC_VER // Memory leak check
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;


int openInputFile(ifstream& in, int argc, char* argv[]);
int openOutputFile(ofstream& out, int argc, char* argv[]);

string getType(string line);
void input_strings(ifstream& in, ofstream& out, vector<string>& lines, vector<SNAP>& snap, vector<CourseGrade>& grades, vector<CourseRoom>& rooms, vector<CourseDayHour>& daysHours, int argc, char* argv[]);
void vectors(ifstream& in, ofstream& out, vector<string> lines);
void course_grades(ifstream& in, ofstream& out, vector<CourseGrade> grades, vector<SNAP> snaps);
void student_schedules(ifstream& in, ofstream& out, vector<SNAP> snaps, vector<CourseDayHour> daysHours, vector<CourseRoom> rooms, vector<CourseGrade> grades);


int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // Enable memory leak check

	vector<string> lines;
	vector<SNAP> snaps;
	vector<CourseGrade> grades;
	vector<CourseRoom> rooms;
	vector<CourseDayHour> daysHours;

	ifstream inputFile; // Reading Input file
	ofstream outputFile; // Writing Output File

	openOutputFile(outputFile, argc, argv);

	input_strings(inputFile, outputFile, lines, snaps, grades, rooms, daysHours, argc, argv);
	vectors(inputFile, outputFile, lines);
	course_grades(inputFile, outputFile, grades, snaps);
	student_schedules(inputFile, outputFile, snaps, daysHours, rooms, grades);

	outputFile.close();
	return 0;
}


int openInputFile(ifstream& in, int argc, char* argv[])
{
	in.open(argv[1]);
	if (in.is_open())
	{
		cout << "Input File opened successfully.\n";
		return 0;
	}
	else
	{
		cout << "Input file could not open.\n";
		return 1;
	}
}


int openOutputFile(ofstream& out, int argc, char* argv[])
{
	out.open(argv[2]);
	if (out.is_open())
	{
		cout << "Output File opened successfully.\n";
		return 0;
	}
	else
	{
		cout << "Output file could not open.\n";
		return 1;
	}
}


string getType(string line)
{
	string type = line.substr(0, line.find('('));

	return type;
}


void input_strings(ifstream& in, ofstream& out, vector<string>& lines, vector<SNAP>& snaps, vector<CourseGrade>& grades, vector<CourseRoom>& rooms, vector<CourseDayHour>& daysHours, int argc, char* argv[])
{
	openInputFile(in, argc, argv);

	out << "Input Strings:" << endl;

	for (string line; getline(in, line);)
	{
		string type = getType(line);
		try
		{
			if (type == "snap") // id, name, address, phone,
			{
				out << line << endl;
				lines.push_back(line);

				string id = line.substr(5, line.find(',') - 5);
				line = line.substr(line.find(',') + 1);
				string name = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string address = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string phone = line.substr(0, line.find(')'));
				snaps.push_back(SNAP(id, name, address, phone));

				continue;
			}
			if (type == "csg") // courseName, id, grade
			{
				out << line << endl;
				lines.push_back(line);

				string courseName = line.substr(4, line.find(',') - 4);
				line = line.substr(line.find(',') + 1);
				string id = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string grade = line.substr(0, line.find(')'));
				grades.push_back(CourseGrade(courseName, id, grade));

				continue;
			}
			if (type == "cdh") // courseName, day, hour,
			{
				out << line << endl;
				lines.push_back(line);

				string courseName = line.substr(4, line.find(',') - 4);
				line = line.substr(line.find(',') + 1);
				string day = line.substr(0, line.find(','));
				line = line.substr(line.find(',') + 1);
				string hour = line.substr(0, line.find(')'));
				daysHours.push_back(CourseDayHour(courseName, day, hour));

				continue;
			}
			if (type == "cr") // courseName, room
			{
				out << line << endl;
				lines.push_back(line);

				string courseName = line.substr(3, line.find(',') - 3);
				line = line.substr(line.find(',') + 1);
				string room = line.substr(0, line.find(')'));
				rooms.push_back(CourseRoom(courseName, room));

				continue;
			}
			throw string("*Error found!");
		}
		catch (const string& s)
		{ 
			out << "**Error: " << line << endl;
			cerr << s << endl; 
		}
	}	in.close();
}


void vectors(ifstream& in, ofstream& out, vector<string> lines) // Prints all lines in vector for part 2
{
	out << endl << "Vectors:" << endl;
	for (size_t i = 0; i < lines.size(); ++i)
	{
		lines.at(i).pop_back(); // Removes '.' at end of line
		out << lines.at(i) << endl;
	}
}


void course_grades(ifstream& in, ofstream& out, vector<CourseGrade> grades, vector<SNAP> snaps) // Prints all students' grades for part 3
{
	out << endl << "Course Grades:" << endl;
	string previous = grades[0].getCourseName();

	for (size_t i = 0; i < grades.size(); ++i)
	{
		if (grades[i].getCourseName() != previous) out << endl;
		SNAP* snap = NULL;
		for (size_t j = 0; j < snaps.size(); ++j)
		{
			if (snaps[j].getStudentID() == grades[i].getStudentID())
			{
				snap = &snaps[j];
				break;
			}
		}
		if (snap != NULL)
		{
			StudentGrade* studentGrade = new StudentGrade(snap, &grades[i]);
			out << *studentGrade;
			delete studentGrade;
		}
		previous = grades[i].getCourseName();
	}
}


void student_schedules(ifstream& in, ofstream& out, vector<SNAP> snaps, vector<CourseDayHour> daysHours, vector<CourseRoom> rooms, vector<CourseGrade> grades) // Prints all students' schedules for part 4
{
	out << endl << "Student Schedules:" << endl;
	
	for (size_t i = 0; i < snaps.size(); ++i)
	{
		out << snaps[i];
		for (size_t j = 0; j < grades.size(); ++j)
		{
			if (snaps[i].getStudentID() == grades[j].getStudentID())
			{
				string allDays = "";
				string time;
				string room;
				for (size_t k = 0; k < daysHours.size(); ++k)
				{
					if (grades[j].getCourseName() == daysHours[k].getCourseName())
					{
						allDays += daysHours[k].getDay();
						time = daysHours[k].getTime();
					}
				}
				for (size_t k = 0; k < rooms.size(); ++k)
				{
					if (grades[j].getCourseName() == rooms[k].getCourseName())
					{
						room = rooms[k].getRoom();
						break;
					}
				}
				StudentSchedule* studentScheule = new StudentSchedule(grades[j].getCourseName(), allDays, time, room);
				out << *studentScheule;
				delete studentScheule;
			}
		
		}
		out << endl;
	}
}


