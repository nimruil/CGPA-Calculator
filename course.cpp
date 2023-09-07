#include <string>
#include <iostream>

#include "course.h"

Course::Course(std::string name, int creditsVal, int firstExamVal, int finalExamVal) : courseName{name}, credits{creditsVal}, firstExam{firstExamVal}, finalExam{finalExamVal}
{
    int score = firstExam * firstExamRate + finalExam * finalExamRate;
    
    if (score <= 29)
        courseGrade = 0.0f;
    else if (score >= 30 && score <= 39)
        courseGrade = 0.5f;
    else if (score >= 40 && score <= 49)
        courseGrade = 1.0f;
    else if (score >= 50 && score <= 59)
        courseGrade = 1.5f;
    else if (score >= 60 && score <= 69)
        courseGrade = 2.0f;
    else if (score >= 70 && score <= 74)
        courseGrade = 2.5f;
    else if (score >= 75 && score <= 79)
        courseGrade = 3.0f;
    else if (score >= 80 && score <= 89)
        courseGrade = 3.5f;
    else if (score >= 90 && score <= 100)
        courseGrade = 4.0f;
    else
    {
        std::cout << "Error in score, GP is 0" << std::endl;
        courseGrade = 0.0f;
    }
}

float Course::getCourseGrade() { return courseGrade; }

std::string Course::getCourseName() { return courseName; }
int Course::getCredits() { return credits; }
