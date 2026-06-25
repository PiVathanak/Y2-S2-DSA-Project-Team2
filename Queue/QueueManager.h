#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include "Queue.h"
#include <string>
#include <vector>

class QueueManager {
private:
    Queue* pendingQueue;
    std::string pendingCSVPath;
    std::string enrollmentsCSVPath;
    
    // Helper functions
    std::vector<std::string> splitCSVLine(const std::string& line) const;
    PendingEnrollment parseCSVToEnrollment(const std::string& line) const;
    bool writePendingEnrollments() const;
    bool moveToApproved(const PendingEnrollment& enrollment);
    
public:
    QueueManager();
    QueueManager(const std::string& pendingPath, const std::string& enrollPath);
    ~QueueManager();
    
    bool loadPendingEnrollments();
    void addPendingEnrollment(const PendingEnrollment& enrollment);
    PendingEnrollment approveNext();
    PendingEnrollment rejectNext();
    bool approveAll();
    bool removePendingEnrollment(int enrollmentId);
    bool isEnrollmentPending(int enrollmentId) const;
    
    std::vector<PendingEnrollment> getPendingEnrollments() const;
    void displayPendingEnrollments() const;
    int getPendingCount() const;
};

#endif