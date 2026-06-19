#include <iostream>
#include <limits>
#include "../tools/CSVReader.h"
#include "../LinkList/CRUD.cpp"

using namespace std;

class AdminDashboard
{
private:
    dataList *studentList;
    dataList *teacherList;
    dataList *courseList;
    dataList *studentTempList;
    dataList *teacherTempList;
    dataList *courseTempList;

    void loadAllData()
    {
        studentList = createDataList();
        teacherList = createDataList();
        courseList = createDataList();
        studentTempList = createDataList();
        teacherTempList = createDataList();
        courseTempList = createDataList();

        vector<Student> students = CSVReader::readStudents("DataBase/Students.csv");
        for (Student &s : students)
        {
            Student *copy = new Student(s);
            addDataNode(studentList, copy, "Student");
        }

        vector<Teacher> teachers = CSVReader::readTeachers("DataBase/Teachers.csv");
        for (Teacher &t : teachers)
        {
            Teacher *copy = new Teacher(t);
            addDataNode(teacherList, copy, "Teacher");
        }

        vector<Course> courses = CSVReader::readCourses("DataBase/Courses.csv");
        for (Course &c : courses)
        {
            Course *copy = new Course(c);
            addDataNode(courseList, copy, "Course");
        }
    }

    void clearInputBuffer()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void addStudentTemp()
    {
        Student *s = new Student();
        cout << "\n--- ADD STUDENT TEMP ---\n";
        cout << "Enter Student ID: ";
        getline(cin, s->student_id);
        cout << "Enter Name: ";
        getline(cin, s->name);
        cout << "Enter Username: ";
        getline(cin, s->username);
        cout << "Enter Email: ";
        getline(cin, s->email);
        cout << "Enter Password: ";
        getline(cin, s->password);
        cout << "Enter Status: ";
        getline(cin, s->status);
        addDataNode(studentTempList, s, "Student");
        cout << "Student temporary added to list.\n";
    }

    void updateStudentTemp()
    {
        string id;
        cout << "\n--- UPDATE STUDENT TEMP ---\n";
        cout << "Enter Student ID to update: ";
        getline(cin, id);
        cout << "Enter field to update (name/username/email/password/status): ";
        string field, value;
        getline(cin, field);
        cout << "Enter new value: ";
        getline(cin, value);
        updateNode(studentList, id, "Student", field, value);
    }

    void deleteStudentTemp()
    {
        string id;
        cout << "\n--- DELETE STUDENT TEMP ---\n";
        cout << "Enter Student ID to delete: ";
        getline(cin, id);
        deleteNode(studentList, id, "Student");
    }

    void addTeacherTemp()
    {
        Teacher *t = new Teacher();
        cout << "\n--- ADD TEACHER TEMP ---\n";
        cout << "Enter Teacher ID: ";
        getline(cin, t->teacher_id);
        cout << "Enter Name: ";
        getline(cin, t->name);
        cout << "Enter Course ID: ";
        getline(cin, t->course_id);
        addDataNode(teacherTempList, t, "Teacher");
        cout << "Teacher temporary added to list.\n";
    }

    void updateTeacherTemp()
    {
        string id;
        cout << "\n--- UPDATE TEACHER TEMP ---\n";
        cout << "Enter Teacher ID to update: ";
        getline(cin, id);
        cout << "Enter field to update (name/course_id): ";
        string field, value;
        getline(cin, field);
        cout << "Enter new value: ";
        getline(cin, value);
        updateNode(teacherList, id, "Teacher", field, value);
    }

    void deleteTeacherTemp()
    {
        string id;
        cout << "\n--- DELETE TEACHER TEMP ---\n";
        cout << "Enter Teacher ID to delete: ";
        getline(cin, id);
        deleteNode(teacherList, id, "Teacher");
    }

    void addCourseTemp()
    {
        Course *c = new Course();
        cout << "\n--- ADD COURSE TEMP ---\n";
        cout << "Enter Course ID: ";
        getline(cin, c->course_id);
        cout << "Enter Course Name: ";
        getline(cin, c->course_name);
        cout << "Enter Teacher ID: ";
        getline(cin, c->teacher_id);
        cout << "Enter Credits: ";
        getline(cin, c->credits);
        addDataNode(courseTempList, c, "Course");
        cout << "Course temporary added to list.\n";
    }

    void updateCourseTemp()
    {
        string id;
        cout << "\n--- UPDATE COURSE TEMP ---\n";
        cout << "Enter Course ID to update: ";
        getline(cin, id);
        cout << "Enter field to update (course_name/teacher_id/credits): ";
        string field, value;
        getline(cin, field);
        cout << "Enter new value: ";
        getline(cin, value);
        updateNode(courseList, id, "Course", field, value);
    }

    void deleteCourseTemp()
    {
        string id;
        cout << "\n--- DELETE COURSE TEMP ---\n";
        cout << "Enter Course ID to delete: ";
        getline(cin, id);
        deleteNode(courseList, id, "Course");
    }

    void showStudentMenu()
    {
        int choice;
        do
        {
            cout << "\n===== STUDENT MENU =====\n";
            cout << "1. Add Student Temp\n";
            cout << "2. Update Student Temp\n";
            cout << "3. Delete Student Temp\n";
            cout << "4. Add Student to List\n";
            cout << "5. Back\n";
            cout << "Choose: ";
            cin >> choice;
            clearInputBuffer();

            switch (choice)
            {
            case 1:
                addStudentTemp();
                break;
            case 2:
                updateStudentTemp();
                break;
            case 3:
                deleteStudentTemp();
                break;
            case 4:
                writeDataListToFiles(studentTempList);
                cout << "Student list saved to file.\n";
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }

    void showTeacherMenu()
    {
        int choice;
        do
        {
            cout << "\n===== TEACHER MENU =====\n";
            cout << "1. Add Teacher Temp\n";
            cout << "2. Update Teacher Temp\n";
            cout << "3. Delete Teacher Temp\n";
            cout << "4. Add Teacher to List\n";
            cout << "5. Back\n";
            cout << "Choose: ";
            cin >> choice;
            clearInputBuffer();

            switch (choice)
            {
            case 1:
                addTeacherTemp();
                break;
            case 2:
                updateTeacherTemp();
                break;
            case 3:
                deleteTeacherTemp();
                break;
            case 4:
                writeDataListToFiles(teacherTempList);
                cout << "Teacher list saved to file.\n";
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }

    void showCourseMenu()
    {
        int choice;
        do
        {
            cout << "\n===== COURSE MENU =====\n";
            cout << "1. Add Course Temp\n";
            cout << "2. Update Course Temp\n";
            cout << "3. Delete Course Temp\n";
            cout << "4. Add Course to List\n";
            cout << "5. Back\n";
            cout << "Choose: ";
            cin >> choice;
            clearInputBuffer();

            switch (choice)
            {
            case 1:
                addCourseTemp();
                break;
            case 2:
                updateCourseTemp();
                break;
            case 3:
                deleteCourseTemp();
                break;
            case 4:
                writeDataListToFiles(courseTempList);
                cout << "Course list saved to file.\n";
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }

public:
    AdminDashboard()
    {
        loadAllData();
    }

    void run()
    {
        int choice;
        do
        {
            cout << "\n===== ADMIN DASHBOARD =====\n";
            cout << "1. Student\n";
            cout << "2. Teacher\n";
            cout << "3. Course\n";
            cout << "4. Exit\n";
            cout << "Choose: ";
            cin >> choice;
            clearInputBuffer();

            switch (choice)
            {
            case 1:
                showStudentMenu();
                break;
            case 2:
                showTeacherMenu();
                break;
            case 3:
                showCourseMenu();
                break;
            case 4:
                cout << "Exiting admin dashboard...\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

int main()
{
    AdminDashboard admin;
    admin.run();
    return 0;
}
