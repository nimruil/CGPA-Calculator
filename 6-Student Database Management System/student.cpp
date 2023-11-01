#include "student.h"

Student::Student(std::string nameVal, std::string surnameVal, int ageVal, int gradeVal, double gpaVal, int idVal)
	:name{ nameVal }, surname{ surnameVal }, age{ ageVal }, grade{ gradeVal }, gpa{ gpaVal }, id{ idVal } {}

std::string const Student::getName() { return name; }
std::string const Student::getSurname() { return surname; }
int const Student::getAge() { return age; }
int const Student::getGrade() { return grade; }
int const Student::getID() { return id; }
double const Student::getGPA() { return gpa; }
void Student::setName(std::string nameVal) { name = nameVal; }
void Student::setSurname(std::string surnameVal) { surname = surnameVal; }
void Student::setAge(int ageVal) { age = ageVal; }
void Student::setGrade(int gradeVal) { grade = gradeVal; }
void Student::setGPA(double gpaVal) { gpa = gpaVal; }
void Student::setID(int idVal) { id = idVal; }
