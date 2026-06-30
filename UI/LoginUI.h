#pragma once
#include <string>
#include "../LinkList/LinkedList.h"

using namespace std;

class LoginUI {
public:
    static bool login(LinkedList& adminList, LinkedList& studentList, LinkedList& teacherList, string& outRole, string& outUserId);
};
