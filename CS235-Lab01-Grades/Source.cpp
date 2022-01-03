#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#ifdef _MSC_VER // Memory leak check
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

const int NUM_GRADES = 5;

int main(int argc, char* argv[])
{
	VS_MEM_CHECK               // Enable memory leak check
		ifstream inputFile; // Reading Input file
		inputFile.open(argv[1]);
		if (inputFile.is_open()) { // Checks if file opened succesfully
			cout << "Input File opened successfully.\n";
		}
		else {
			cout << "File couldn't open. Terminating.\n";
			return 1;
		}

		int numStudents;
		int numExams;
		inputFile >> numStudents >> numExams;
		inputFile.ignore(std::numeric_limits<int>::max(), '\n');

		string* arrayNames = new string[numStudents]; // Intializes Students Array
		double* arrayTotalGrade = new double[numStudents]; // Initializes Total Score Array
		double* arrayAverages = new double[numExams]; // Initializes Average Score Array
		int** arrayScores = new int* [numStudents]; // Initializes Scores Array
		for (int i = 0; i < numStudents; ++i)
		{
			arrayScores[i] = new int[numExams];
		}
		int** arrayGradeCount = new int* [numExams]; // Initializes Grade Count Array
		for (int i = 0; i < numExams; ++i)
		{
			arrayGradeCount[i] = new int[NUM_GRADES];
			for (int j = 0; j < NUM_GRADES; ++j)
			{
				arrayGradeCount[i][j] = 0;
			}
		}

		
		for (int i = 0; i < numStudents; ++i)
		{
			string line;
			string name;
			getline(inputFile, line);
			size_t p = 0;
			while (!isdigit(line[p])) ++p;	// line[p] is the location of the first digit on the line

			name = line.substr(0, p - 1); // Gets name from file, p-1 removes an extra whitespace.
			arrayNames[i] = name;
			line = line.substr(p); // Isolates scores on line
			istringstream iss(line); // Puts line (now with only scores' values) into an istringstream
			for (int j = 0; j < numExams; ++j) // Puts scores from istringstream into arrayScores onto row 'i' 
			{
				int scores;
				iss >> scores;
				arrayScores[i][j] = scores;
			}
		}

		inputFile.close();

			ofstream outputFile; // Writing to Output File
			outputFile.open(argv[2]);
			if (outputFile.is_open()) { // Checks if file opened succesfully
				cout << endl << "Output File opened successfully.\n";
			}
			else {
				cout << "File couldn't open. Terminating.\n";
				return 1;
			}

			outputFile << "Student Scores: " << endl; // Prints Students' Scores to outputFile
			for (int i = 0; i < numStudents; ++i)
			{
				if (i != 0) outputFile << endl; // Start new line except on first occurence
				outputFile << setw(20) << arrayNames[i] << " ";
				for (int j = 0; j < numExams; ++j)
				{
					outputFile << setw(6) << arrayScores[i][j];
				}
			}
			outputFile << endl;

			outputFile << "Exam Averages: " << endl; // Prints Exam Averages to outputFile
			for (int i = 0; i < numExams; ++i)
			{
				double sum = 0.0;
				for (int j = 0; j < numStudents; ++j)
				{
					sum += arrayScores[j][i];
				}

				double average = sum / numStudents;
				arrayAverages[i] = average;

				outputFile << setw(9) << "Exam " << i + 1 << " Average =";
				outputFile << setw(7) << fixed << setprecision(1) << arrayAverages[i] << '\n';
			}

			outputFile << "Student Exam Grades: " << endl; // Prints Student Exam Grades to outputFile
			for (int i = 0; i < numStudents; ++i)
			{
				if (i != 0) outputFile << endl; // Start new line except on first occurence
				outputFile << setw(21) << arrayNames[i];
				for (int j = 0; j < numExams; ++j)
				{
					string grade = "_";
					if (arrayScores[i][j] - arrayAverages[j] > 5.0 && arrayScores[i][j] - arrayAverages[j] < 15.0) // Determines student's grade based on difference between score and average score.
					{
						grade = "B";
						++arrayGradeCount[j][1];
					}
					else if(arrayScores[i][j] - arrayAverages[j] > 15.0)
					{
						grade = "A";
						++arrayGradeCount[j][0];
					}
					else if (arrayScores[i][j] - arrayAverages[j] < -5.0 && arrayScores[i][j] - arrayAverages[j] > -15.0)
					{
						grade = "D";
						++arrayGradeCount[j][3];
					}
					else if (arrayScores[i][j] - arrayAverages[j] < -15.0)
					{
						grade = "E";
						++arrayGradeCount[j][4];
					}
					else
					{
						grade = "C";
						++arrayGradeCount[j][2];
					}
					outputFile << setw(5) << arrayScores[i][j] << "(" << grade << ")";
				}
			}

			cout << arrayGradeCount[0][0];
			outputFile << endl;
			outputFile << "Exam Grades: " << endl; // Prints Exam Grades to outputFile
			for (int i = 0; i < numExams; ++i)
			{
				outputFile << setw(8) << "Exam" << setw(3) << i + 1;
				outputFile << setw(5) << arrayGradeCount[i][0] << "(A)";
				outputFile << setw(5) << arrayGradeCount[i][1] << "(B)";
				outputFile << setw(5) << arrayGradeCount[i][2] << "(C)";
				outputFile << setw(5) << arrayGradeCount[i][3] << "(D)";
				outputFile << setw(5) << arrayGradeCount[i][4] << "(E)";
				outputFile << endl;
			}
			outputFile << "Student Final Grades: " << endl; // Prints Exam Grades to outputFile

			double classSumGrade = 0.0;
			for (int i = 0; i < numStudents; ++i)
			{
				double sumGrade = 0.0;
				for (int j = 0; j < numExams; ++j)
				{
					sumGrade = sumGrade + arrayScores[i][j]; // Cauclates student's sum grade
					arrayTotalGrade[i] = sumGrade / numExams; // Calculates student's total grade
				}
				classSumGrade = classSumGrade + arrayTotalGrade[i]; // Calculates class Sum Score
			}

			double classAverage = classSumGrade / numStudents; // Calculates class average score
			for (int i = 0; i < numStudents; ++i)
			{
				string grade = "_";
				if (arrayTotalGrade[i] - classAverage > 5.0 && arrayTotalGrade[i] - classAverage < 15.0) // Determines student's grade based on difference between score and average score.
				{
					grade = "B";
				}
				else if (arrayTotalGrade[i] - classAverage > 15.0)
				{
					grade = "A";
				}
				else if (arrayTotalGrade[i] - classAverage < -5.0 && arrayTotalGrade[i] - classAverage > -15.0)
				{
					grade = "D";
				}
				else if (arrayTotalGrade[i] - classAverage < -15.0)
				{
					grade = "E";
				}
				else
				{
					grade = "C";
				}
				outputFile << setw(20) << arrayNames[i] << setw(6) << arrayTotalGrade[i] << "(" << grade << ")" << endl;
			}
			outputFile << "Class Average Score = " << classAverage;

			outputFile.close();

			// Deletes arrays to avoid memory leak
			{
				delete[] arrayNames; 
				delete[] arrayTotalGrade;
				delete[] arrayAverages;

				for (int i = 0; i < numStudents; ++i)
				{
					delete[] arrayScores[i];
				}
				delete[] arrayScores;

				for (int i = 0; i < numExams; ++i)
				{
					delete[] arrayGradeCount[i];
				}
				delete[] arrayGradeCount;

			} 
return 0;
}