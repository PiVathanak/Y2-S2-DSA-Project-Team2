#ifndef PENDINGENROLLMENT_H
#define PENDINGENROLLMENT_H

#include <string>

struct PendingEnrollment {
    int enrollmentId;
    int studentId;
    int courseId;
    std::string status;
    
    PendingEnrollment() : enrollmentId(0), studentId(0), courseId(0), status("pending") {}
    PendingEnrollment(int id, int sId, int cId, const std::string& stat = "pending")
        : enrollmentId(id), studentId(sId), courseId(cId), status(stat) {}
    
    bool operator==(const PendingEnrollment& other) const {
        return enrollmentId == other.enrollmentId;
    }
    
    std::string toCSV() const {
        return std::to_string(enrollmentId) + "," + 
               std::to_string(studentId) + "," + 
               std::to_string(courseId);
    }
};

#endif