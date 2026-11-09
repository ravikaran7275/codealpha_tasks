#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

struct Course {
    std::string name;
    double gradePoint;
    double creditHours;
};

int main() {
    int numSemesters;
    std::cout << "Enter number of semesters: ";
    if (!(std::cin >> numSemesters) || numSemesters <= 0) return 0;

    double cumulativeGradePoints = 0.0;
    double cumulativeCredits = 0.0;

    for (int sem = 1; sem <= numSemesters; ++sem) {
        int numCourses;
        std::cout << "\n--- Semester " << sem << " ---\n";
        std::cout << "Enter number of courses: ";
        std::cin >> numCourses;

        std::vector<Course> courses(numCourses);
        double semesterGradePoints = 0.0;
        double semesterCredits = 0.0;

        for (int i = 0; i < numCourses; ++i) {
            std::cout << "\nCourse " << (i + 1) << " Name: ";
            std::cin >> courses[i].name;
            std::cout << "Grade Points (e.g., 4.0 for A, 3.0 for B): ";
            std::cin >> courses[i].gradePoint;
            std::cout << "Credit Hours: ";
            std::cin >> courses[i].creditHours;

            semesterGradePoints += (courses[i].gradePoint * courses[i].creditHours);
            semesterCredits += courses[i].creditHours;
        }

        double semesterGpa = (semesterCredits > 0) ? (semesterGradePoints / semesterCredits) : 0.0;
        cumulativeGradePoints += semesterGradePoints;
        cumulativeCredits += semesterCredits;

        std::cout << "\n--- Semester " << sem << " Results ---\n";
        std::cout << std::left << std::setw(15) << "Course" << std::setw(15) << "Grade Point" << std::setw(15) << "Credits" << "\n";
        for (const auto& c : courses) {
            std::cout << std::left << std::setw(15) << c.name << std::setw(15) << c.gradePoint << std::setw(15) << c.creditHours << "\n";
        }
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Semester GPA: " << semesterGpa << "\n";
    }

    double finalCgpa = (cumulativeCredits > 0) ? (cumulativeGradePoints / cumulativeCredits) : 0.0;
    std::cout << "\n==============================\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Credits Completed: " << cumulativeCredits << "\n";
    std::cout << "Final Overall CGPA: " << finalCgpa << "\n";
    std::cout << "==============================\n";

    return 0;
}
