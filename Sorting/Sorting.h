#pragma once
#include "../tools/Models.cpp"

class Sorting {
public:
    static void mergeCourses(Course** arr, int left, int mid, int right);
    static void mergeSortCoursesRec(Course** arr, int left, int right);
    static void mergeSortCoursesByName(Course** arr, int n);

    static void mergeStudents(Student** arr, int left, int mid, int right);
    static void mergeSortStudentsRec(Student** arr, int left, int right);
    static void mergeSortStudentsByName(Student** arr, int n);

    static void insertionSortStudentsByName(Student** arr, int n);
};
