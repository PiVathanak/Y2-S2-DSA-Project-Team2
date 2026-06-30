#pragma once
#include <iostream>
#include "Sorting.h"

using namespace std;

void Sorting::mergeCourses(Course** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Course** L = new Course*[n1];
    Course** R = new Course*[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->course_name <= R[j]->course_name) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { arr[k++] = L[i++]; }
    while (j < n2) { arr[k++] = R[j++]; }

    delete[] L;
    delete[] R;
}

void Sorting::mergeSortCoursesRec(Course** arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortCoursesRec(arr, left, mid);
    mergeSortCoursesRec(arr, mid + 1, right);
    mergeCourses(arr, left, mid, right);
}

void Sorting::mergeSortCoursesByName(Course** arr, int n) {
    mergeSortCoursesRec(arr, 0, n - 1);
}

void Sorting::mergeStudents(Student** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Student** L = new Student*[n1];
    Student** R = new Student*[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->name <= R[j]->name) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { arr[k++] = L[i++]; }
    while (j < n2) { arr[k++] = R[j++]; }

    delete[] L;
    delete[] R;
}

void Sorting::mergeSortStudentsRec(Student** arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortStudentsRec(arr, left, mid);
    mergeSortStudentsRec(arr, mid + 1, right);
    mergeStudents(arr, left, mid, right);
}

void Sorting::mergeSortStudentsByName(Student** arr, int n) {
    mergeSortStudentsRec(arr, 0, n - 1);
}

void Sorting::insertionSortStudentsByName(Student** arr, int n) {
    for (int i = 1; i < n; i++) {
        Student* key = arr[i];
        int j = i - 1;
        // Compare student names alphabetically
        while (j >= 0 && arr[j]->name > key->name) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
