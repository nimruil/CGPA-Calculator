#include <iostream>
#include <vector>
#include <iomanip>

#include "course.h"

int intro();
void outro();
void addCourse(std::vector<Course> &);
void printResults(std::vector<std::vector<Course>> &, std::vector<float> &);
float calculateGPA(std::vector<Course> &);
float calculateCGPA(std::vector<std::vector<Course>> &);
void receiveCourseInfo(int, std::vector<Course> &, std::vector<std::vector<Course>> &, std::vector<float> &);

int main()
{
    int semesterCount = intro();
    std::vector<std::vector<Course>> semesters(semesterCount);
    std::vector<Course> semester;
    std::vector<float> semesterGPAs(semesterCount);

    receiveCourseInfo(semesterCount, semester, semesters, semesterGPAs);
    printResults(semesters, semesterGPAs);
    outro();
    return 0;
}

void receiveCourseInfo(int semesterCount, std::vector<Course> &semester, std::vector<std::vector<Course>> &semesters, std::vector<float> &semesterGPAs)
{
    for (int i = 0; i < semesterCount; i++)
    {
        std::cout << i + 1 << ". semester:" << std::endl;
        std::cout << "How many lessons will you enter for this semester?: ";
        int lessonsVal{0};
        std::cin >> lessonsVal;
        int k{0};
        while (k++ < lessonsVal)
        {
            addCourse(semester);
        }
        semesters[i] = semester;
        semesterGPAs[i] = calculateGPA(semester);
        semester.clear();
    }
};

void addCourse(std::vector<Course> &courseVector)
{
    std::string courseName{""};
    int credits{0}, firstExam{0}, finalExam{0};
    std::cout << "Please enter the name of course: ";
    std::cin >> courseName;
    std::cout << "Enter the credits, first exam grade and final exam grades: ";
    std::cin >> credits >> firstExam >> finalExam;
    Course course{courseName, credits, firstExam, finalExam};
    courseVector.push_back(course);
}

void printResults(std::vector<std::vector<Course>> &semestersVector, std::vector<float> &semesterGPAVector)
{
    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < semestersVector.size(); i++)
    {
        std::cout << "-------------------" << std::endl;
        std::cout << i + 1 << ". Semester:" << std::endl;
        std::cout << "Name"
                  << "\t"
                  << "Grade" << std::endl;

        for (int j = 0; j < semestersVector[i].size(); j++)
        {
            Course currentCourse = semestersVector[i][j];
            std::cout << currentCourse.getCourseName()
                      << "\t" << currentCourse.getCourseGrade() << std::endl;
        }
        std::cout << "-------------------" << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << i + 1 << ". Semester GPA: " << semesterGPAVector[i] << std::endl;
    }
    std::cout << "-------------------" << std::endl;
    std::cout << "Overall CGPA: " << calculateCGPA(semestersVector) << std::endl;
}

int intro()
{
    std::cout << "How many semesters did you study? ";
    int semesterCount{0};
    std::cin >> semesterCount;
    return semesterCount;
}

void outro()
{
    char input;
    std::cout << "Press x to terminate.. ";
    std::cin >> input;
}

float calculateGPA(std::vector<Course> &semesterVector)
{
    float totalSemesterPoints{0};
    int totalCredits{0};

    for (int i = 0; i < semesterVector.size(); i++)
    {
        totalSemesterPoints += semesterVector[i].getCourseGrade() * semesterVector[i].getCredits();
        totalCredits += semesterVector[i].getCredits();
    }

    float GP = totalSemesterPoints / totalCredits;
    return GP;
}

float calculateCGPA(std::vector<std::vector<Course>> &semestersVector)
{
    float totalCoursePoints{0.0f};
    int totalCredits{0};
    for (int i = 0; i < semestersVector.size(); i++)
    {
        for (int j = 0; j < semestersVector[i].size(); j++)
        {
            Course currentCourse = semestersVector[i][j];
            totalCoursePoints += currentCourse.getCourseGrade() * currentCourse.getCredits();
            totalCredits += currentCourse.getCredits();
        }
    }
    return totalCoursePoints / totalCredits;
};
