#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TeacherDashboard
{
private:
    string teacherName;
    string teacherID;
    string teacherEmail;
    string department;
    vector<string> teachingCourses;
    vector<int> studentCounts;

public:
    TeacherDashboard()
    {
        teacherName = "";
        teacherID = "";
        teacherEmail = "";
        department = "";
    }

    void displayTeacherHeader()
    {
        cout << "\n=====================================" << endl;
        cout << "       TEACHER DASHBOARD            " << endl;
        cout << "=====================================" << endl;
        cout << "Welcome, " << teacherName << "!" << endl;
        cout << "Teacher ID: " << teacherID << endl;
        cout << "Department: " << department << endl;
        cout << "Email: " << teacherEmail << endl;
        cout << "=====================================" << endl;
        cout << endl;
    }

    void displayMainMenu()
    {
        cout << "--- DASHBOARD MENU ---" << endl;
        cout << "1. View Teaching Courses" << endl;
        cout << "2. Manage Course" << endl;
        cout << "3. Grade Management" << endl;
        cout << "4. Student Attendance" << endl;
        cout << "5. Create/Upload Assignment" << endl;
        cout << "6. View Student Messages" << endl;
        cout << "7. Class Analytics" << endl;
        cout << "8. Update Profile" << endl;
        cout << "9. Logout" << endl;
        cout << "\nEnter your choice (1-9): ";
    }

    int getUserChoice()
    {
        displayTeacherHeader();
        displayMainMenu();

        int choice;
        cin >> choice;
        cin.ignore();

        return choice;
    }

    void viewTeachingCourses()
    {
        cout << "\n--- TEACHING COURSES ---" << endl;

        if (teachingCourses.empty())
        {
            cout << "No courses assigned." << endl;
            return;
        }

        for (int i = 0; i < teachingCourses.size(); i++)
        {
            cout << i + 1 << ". " << teachingCourses[i]
                 << " (" << studentCounts[i] << " students)" << endl;
        }
        cout << "\n[Course data - Not yet connected to backend]" << endl;
    }

    void manageCourse()
    {
        cout << "\n--- MANAGE COURSE ---" << endl;
        cout << "Select course:" << endl;

        for (int i = 0; i < teachingCourses.size(); i++)
        {
            cout << i + 1 << ". " << teachingCourses[i] << endl;
        }

        cout << "Enter course number: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= teachingCourses.size())
        {
            cout << "\n--- Managing: " << teachingCourses[choice - 1] << " ---" << endl;
            cout << "1. Update Course Info" << endl;
            cout << "2. Add/Remove Student" << endl;
            cout << "3. Upload Course Materials" << endl;
            cout << "4. View Student List" << endl;
            cout << "5. Back" << endl;

            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            cout << "[Course management - Not yet connected to system]" << endl;
        }
    }

    void gradeManagement()
    {
        cout << "\n--- GRADE MANAGEMENT ---" << endl;
        cout << "Select course:" << endl;

        for (int i = 0; i < teachingCourses.size(); i++)
        {
            cout << i + 1 << ". " << teachingCourses[i] << endl;
        }

        cout << "Enter course number: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= teachingCourses.size())
        {
            cout << "\n--- Grade Management: " << teachingCourses[choice - 1] << " ---" << endl;
            cout << "1. Enter Student Grades" << endl;
            cout << "2. View Grade Distribution" << endl;
            cout << "3. Generate Grade Report" << endl;
            cout << "4. Adjust Grades" << endl;

            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            cout << "[Grade data - Not yet connected to database]" << endl;
        }
    }

    void studentAttendance()
    {
        cout << "\n--- STUDENT ATTENDANCE ---" << endl;
        cout << "Select course:" << endl;

        for (int i = 0; i < teachingCourses.size(); i++)
        {
            cout << i + 1 << ". " << teachingCourses[i]
                 << " (" << studentCounts[i] << " students)" << endl;
        }

        cout << "Enter course number: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= teachingCourses.size())
        {
            cout << "\n--- Attendance Tracking: " << teachingCourses[choice - 1] << " ---" << endl;
            cout << "Date: [Select Date]" << endl;
            cout << "1. Mark Attendance" << endl;
            cout << "2. View Attendance Report" << endl;
            cout << "3. Generate Attendance Summary" << endl;

            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            cout << "[Attendance data - Not yet connected]" << endl;
        }
    }

    void createAssignment()
    {
        cout << "\n--- CREATE/UPLOAD ASSIGNMENT ---" << endl;
        cout << "Select course:" << endl;

        for (int i = 0; i < teachingCourses.size(); i++)
        {
            cout << i + 1 << ". " << teachingCourses[i] << endl;
        }

        cout << "Enter course number: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= teachingCourses.size())
        {
            cout << "\nAssignment Title: ";
            string title;
            getline(cin, title);

            cout << "Description: ";
            string description;
            getline(cin, description);

            cout << "Due Date (DD/MM/YYYY): ";
            string dueDate;
            getline(cin, dueDate);

            cout << "\n[Assignment created - Not yet connected to system]" << endl;
            cout << "Ready to upload to: " << teachingCourses[choice - 1] << endl;
        }
    }

    void viewMessages()
    {
        cout << "\n--- STUDENT MESSAGES ---" << endl;
        cout << "Unread Messages: 5" << endl;
        cout << "\n1. From STU001 - Subject: Project Help" << endl;
        cout << "2. From STU005 - Subject: Extension Request" << endl;
        cout << "3. From STU012 - Subject: Clarification Needed" << endl;
        cout << "\n[Messages - Not yet connected to backend]" << endl;
    }

    void classAnalytics()
    {
        cout << "\n--- CLASS ANALYTICS ---" << endl;
        cout << "Select course:" << endl;

        for (int i = 0; i < teachingCourses.size(); i++)
        {
            cout << i + 1 << ". " << teachingCourses[i] << endl;
        }

        cout << "Enter course number: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= teachingCourses.size())
        {
            cout << "\n--- Analytics: " << teachingCourses[choice - 1] << " ---" << endl;
            cout << "Total Students: " << studentCounts[choice - 1] << endl;
            cout << "Average Grade: [To be calculated]" << endl;
            cout << "Attendance Rate: [To be calculated]" << endl;
            cout << "Assignment Submission Rate: [To be calculated]" << endl;
            cout << "\n[Analytics data - Not yet connected to database]" << endl;
        }
    }

    void updateProfile()
    {
        cout << "\n--- UPDATE PROFILE ---" << endl;
        cout << "1. Change Email" << endl;
        cout << "2. Change Password" << endl;
        cout << "3. Update Office Hours" << endl;
        cout << "4. Back" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            cout << "Enter new email: ";
            string newEmail;
            getline(cin, newEmail);
            teacherEmail = newEmail;
            cout << "[Email update - Not yet connected]" << endl;
            break;
        }
        case 2:
        {
            cout << "Enter new password: ";
            string newPass;
            getline(cin, newPass);
            cout << "[Password update - Not yet connected]" << endl;
            break;
        }
        case 3:
        {
            cout << "Enter office hours: ";
            string officeHours;
            getline(cin, officeHours);
            cout << "[Office hours update - Not yet connected]" << endl;
            break;
        }
        }
    }

    void handleChoice(int choice)
    {
        switch (choice)
        {
        case 1:
            viewTeachingCourses();
            break;
        case 2:
            manageCourse();
            break;
        case 3:
            gradeManagement();
            break;
        case 4:
            studentAttendance();
            break;
        case 5:
            createAssignment();
            break;
        case 6:
            viewMessages();
            break;
        case 7:
            classAnalytics();
            break;
        case 8:
            updateProfile();
            break;
        case 9:
            cout << "\nLogging out..." << endl;
            return;
        default:
            cout << "Invalid choice! Try again." << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }

    void run()
    {
        int choice;
        bool running = true;

        while (running)
        {
            choice = getUserChoice();
            if (choice == 9)
            {
                handleChoice(choice);
                running = false;
            }
            else
            {
                handleChoice(choice);
            }
        }
    }
};

// Main function for testing
int main()
{
    TeacherDashboard dashboard;
    dashboard.run();
    return 0;
}
