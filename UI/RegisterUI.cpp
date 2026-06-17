#include <iostream>
#include <string>
#include <regex>

using namespace std;

class RegisterUI
{
private:
    string fullName;
    string email;
    string studentID;
    string password;
    string confirmPassword;
    string userType;

public:
    RegisterUI()
    {
        fullName = "";
        email = "";
        studentID = "";
        password = "";
        confirmPassword = "";
        userType = "";
    }

    void displayRegisterMenu()
    {
        cout << "\n=============================" << endl;
        cout << "   SYSTEM REGISTRATION      " << endl;
        cout << "=============================" << endl;
        cout << endl;
    }

    int getRegistrationType()
    {
        displayRegisterMenu();

        cout << "1. Register as Student" << endl;
        cout << "2. Register as Teacher" << endl;
        cout << "3. Go Back to Main Menu" << endl;
        cout << "\nEnter your choice (1-3): ";

        int choice;
        cin >> choice;
        cin.ignore();

        return choice;
    }

    void registerStudent()
    {
        cout << "\n--- STUDENT REGISTRATION ---" << endl;

        cout << "Enter Full Name: ";
        getline(cin, fullName);

        cout << "Enter Student ID: ";
        getline(cin, studentID);

        cout << "Enter Email Address: ";
        getline(cin, email);

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "Confirm Password: ";
        getline(cin, confirmPassword);

        displayRegistrationSummary("STUDENT");
    }

    void registerTeacher()
    {
        cout << "\n--- TEACHER REGISTRATION ---" << endl;

        cout << "Enter Full Name: ";
        getline(cin, fullName);

        cout << "Enter Teacher ID: ";
        getline(cin, studentID);

        cout << "Enter Email Address: ";
        getline(cin, email);

        cout << "Enter Department: ";
        string department;
        getline(cin, department);

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "Confirm Password: ";
        getline(cin, confirmPassword);

        displayRegistrationSummary("TEACHER");
    }

    void displayRegistrationSummary(string type)
    {
        cout << "\n--- REGISTRATION SUMMARY ---" << endl;
        cout << "Type: " << type << endl;
        cout << "Full Name: " << fullName << endl;
        cout << "ID: " << studentID << endl;
        cout << "Email: " << email << endl;
        cout << "Password: ***" << endl;

        if (password == confirmPassword)
        {
            cout << "\n✓ Passwords match" << endl;
            cout << "[Registration Data - Not yet connected to database]" << endl;
            cout << "Status: Ready to submit" << endl;
        }
        else
        {
            cout << "\n✗ Passwords do not match!" << endl;
            cout << "Please try again." << endl;
        }
    }

    void handleRegistration(int choice)
    {
        switch (choice)
        {
        case 1:
            registerStudent();
            break;
        case 2:
            registerTeacher();
            break;
        case 3:
            cout << "\nReturning to main menu..." << endl;
            break;
        default:
            cout << "\nInvalid choice! Please try again." << endl;
        }
    }

    void run()
    {
        int choice;
        bool running = true;

        while (running)
        {
            choice = getRegistrationType();
            handleRegistration(choice);

            if (choice == 3)
            {
                running = false;
            }
        }
    }
};

// Main function for testing
int main()
{
    RegisterUI registration;
    registration.run();
    return 0;
}
