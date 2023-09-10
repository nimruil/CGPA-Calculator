#ifndef _COURSE_H_
#define _COURSE_H_

#include <string>

class Course
{
private:
    int credits;
    float firstExamRate = 0.4F;
    float finalExamRate = 0.6F;
    int firstExam, finalExam;
    float courseGrade;
    std::string courseName;

public:
    Course(std::string name, int creditsVal, int firstExamVal, int finalExamVal);
    float getCourseGrade();
    std::string getCourseName();
    int getCredits();
};

#endif //_COURSE_H_
