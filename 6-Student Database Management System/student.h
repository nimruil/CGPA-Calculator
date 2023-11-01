#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>

class Student
{
private:
	std::string name, surname;
	int age, grade, id;
	double gpa;

public:
	Student(std::string name = "", std::string surname = "", int age = 0, int grade = 0, double gpa = 0.0, int id = 0);
	std::string const getName();
	std::string const getSurname();
	int const getAge();
	int const getGrade();
	double const getGPA();
	int const getID();
	void setName(std::string);
	void setSurname(std::string);
	void setAge(int);
	void setGrade(int);
	void setGPA(double);
	void setID(int);
};
#endif
