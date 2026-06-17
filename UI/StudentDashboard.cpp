#include <iostream>
#include <string>
#include <vector>

using namespace std;

class StudentDashboard
{
private:
    string studentName;
    string studentID;
    string studentEmail;
    vector<string> enrolledCourses;
    vector<float> courseGrades;

public:
    StudentDashboard()
    {
        studentName = "";
        studentID = "";
        studentEmail = "";
    }

    void displayStudentHeader()
    {
        cout << "\n=====================================" << endl;
        cout << "        STUDENT DASHBOARD           " << endl;
        cout << "=====================================" << endl;
        cout << "Welcome, " << studentName << "!" << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Email: " << studentEmail << endl;
        cout << "=====================================" << endl;
        cout << endl;
    }

    void displayMainMenu()
    {
        cout << "--- DASHBOARD MENU ---" << endl;
        cout << "1. View Enrolled Courses" << endl;
        cout << "2. View Grades" << endl;
        cout << "3. View Course Details" << endl;
        cout << "4. Assignment Submission" << endl;
        cout << "5. Message Instructor" << endl;
        cout << "6. Update Profile" << endl;
        cout << "7. Logout" << endl;
        cout << "\nEnter your choice (1-7): ";
    }

    int getUserChoice()
    {
        displayStudentHeader();
        displayMainMenu();

        int choice;
        cin >> choice;
        cin.ignore();

        return choice;
    }

    void viewEnrolledCourses()
    {
        cout << "\n--- ENROLLED COURSES ---" << endl;

        if (enrolledCourses.empty())
        {
            cout << "No courses enrolled yet." << endl;
            return;
        }

        for (int i = 0; i < enrolledCourses.size(); i++)
        {
            cout << i + 1 << ". " << enrolledCourses[i] << endl;
        }
        cout << "\n[Course data - Not yet connected to backend]" << endl;
    }

    void viewGrades()
    {
        cout << "\n--- GRADES ---" << endl;

        float totalGrades = 0;
        for (int i = 0; i < enrolledCourses.size(); i++)
        {
            cout << enrolledCourses[i] << ": " << courseGrades[i] << "%" << endl;
            totalGrades += courseGrades[i];
        }

        if (enrolledCourses.size() > 0)
        {
            float average = totalGrades / enrolledCourses.size();
            cout << "\nAverage Grade: " << average << "%" << endl;
        }
        cout << "\n[Grade data - Not yet connected to database]" << endl;
    }

    void viewCourseDetails()
    {
        cout << "\n--- COURSE DETAILS ---" << endl;
        cout << "Select course to view details:" << endl;

        for (int i = 0; i < enrolledCourses.size(); i++)
        {
            cout << i + 1 << ". " << enrolledCourses[i] << endl;
        }

        cout << "Enter course number (or 0 to go back): ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= enrolledCourses.size())
        {
            cout << "\n--- " << enrolledCourses[choice - 1] << " ---" << endl;
            cout << "Instructor: [To be connected]" << endl;
            cout << "Schedule: [To be connected]" << endl;
            cout << "Materials: [To be connected]" << endl;
            cout << "Assignments: [To be connected]" << endl;
        }
    }

    void submitAssignment()
    {
        cout << "\n--- ASSIGNMENT SUBMISSION ---" << endl;
        cout << "Select course:" << endl;

        for (int i = 0; i < enrolledCourses.size(); i++)
        {
            cout << i + 1 << ". " << enrolledCourses[i] << endl;
        }

        cout << "Enter course number: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= enrolledCourses.size())
        {
            cout << "\nAvailable Assignments for " << enrolledCourses[choice - 1] << ":" << endl;
            cout << "1. Assignment 1" << endl;
            cout << "2. Assignment 2" << endl;
            cout << "\nChoose assignment to submit: ";
            cin.ignore();
            cout << "[File upload - Not yet connected to system]" << endl;
        }
    }

    void messageInstructor()
    {
        cout << "\n--- MESSAGE INSTRUCTOR ---" << endl;
        cout << "Select instructor/course:" << endl;

        for (int i = 0; i < enrolledCourses.size(); i++)
        {
            cout << i + 1 << ". " << enrolledCourses[i] << endl;
        }

        cout << "Enter course number: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice > 0 && choice <= enrolledCourses.size())
        {
            cout << "\nCompose message:" << endl;
            cout << "Subject: ";
            string subject;
            getline(cin, subject);

            cout << "Message: ";
            string message;
            getline(cin, message);

            cout << "\n[Message - Not yet connected to backend]" << endl;
            cout << "Message ready to send." << endl;
        }
    }

    void updateProfile()
    {
        cout << "\n--- UPDATE PROFILE ---" << endl;
        cout << "1. Change Email" << endl;
        cout << "2. Change Password" << endl;
        cout << "3. Update Personal Info" << endl;
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
            getline(cin, studentEmail);
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
            cout << "Enter new name: ";
            getline(cin, studentName);
            cout << "[Profile update - Not yet connected]" << endl;
            break;
        }
            
        }
    }

    void handleChoice(int choice)
    {
        switch (choice)
        {
        case 1:
            viewEnrolledCourses();
            break;
        case 2:
            viewGrades();
            break;
        case 3:
            viewCourseDetails();
            break;
        case 4:
            submitAssignment();
            break;
        case 5:
            messageInstructor();
            break;
        case 6:
            updateProfile();
            break;
        case 7:
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
            if (choice == 7)
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
    StudentDashboard dashboard;
    dashboard.run();
    return 0;
}
