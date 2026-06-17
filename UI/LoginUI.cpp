#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class LoginUI
{
private:
    string username;
    string password;

public:
    LoginUI()
    {
        username = "";
        password = "";
    }

    void displayLoginMenu()
    {
        cout << "\n=============================" << endl;
        cout << "     SYSTEM LOGIN PANEL      " << endl;
        cout << "=============================" << endl;
        cout << endl;
    }

    int getUserChoice()
    {
        displayLoginMenu();

        cout << "1. Login as Student" << endl;
        cout << "2. Login as Teacher" << endl;
        cout << "3. Exit" << endl;
        cout << "\nEnter your choice (1-3): ";

        int choice;
        cin >> choice;
        cin.ignore();

        return choice;
    }

    void getStudentLoginCredentials()
    {
        cout << "\n--- STUDENT LOGIN ---" << endl;

        cout << "Enter Student ID: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "\n[Student Login Process - Not yet connected to backend]" << endl;
        cout << "Credentials: ID=" << username << ", Password=***" << endl;
    }

    void getTeacherLoginCredentials()
    {
        cout << "\n--- TEACHER LOGIN ---" << endl;

        cout << "Enter Teacher ID: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "\n[Teacher Login Process - Not yet connected to backend]" << endl;
        cout << "Credentials: ID=" << username << ", Password=***" << endl;
    }

    void handleLogin(int choice)
    {
        switch (choice)
        {
        case 1:
            getStudentLoginCredentials();
            break;
        case 2:
            getTeacherLoginCredentials();
            break;
        case 3:
            cout << "\nExiting system..." << endl;
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
            choice = getUserChoice();
            handleLogin(choice);

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
    LoginUI login;
    login.run();
    return 0;
}
