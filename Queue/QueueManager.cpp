#include "QueueManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

QueueManager::QueueManager() 
    : pendingCSVPath("DataBase/PendingEnrollment.csv"), 
      enrollmentsCSVPath("DataBase/Enrollments.csv") {
    pendingQueue = createQueue();
}

QueueManager::QueueManager(const std::string& pendingPath, const std::string& enrollPath)
    : pendingCSVPath(pendingPath), enrollmentsCSVPath(enrollPath) {
    pendingQueue = createQueue();
}

QueueManager::~QueueManager() {
    writePendingEnrollments();
    deleteQueue(pendingQueue);
}

std::vector<std::string> QueueManager::splitCSVLine(const std::string& line) const {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string cell;
    
    while (std::getline(ss, cell, ',')) {
        result.push_back(cell);
    }
    return result;
}

PendingEnrollment QueueManager::parseCSVToEnrollment(const std::string& line) const {
    auto parts = splitCSVLine(line);
    if (parts.size() >= 3) {
        int enrollmentId = std::stoi(parts[0]);
        int studentId = std::stoi(parts[1]);
        int courseId = std::stoi(parts[2]);
        return PendingEnrollment(enrollmentId, studentId, courseId, "pending");
    }
    return PendingEnrollment();
}

bool QueueManager::writePendingEnrollments() const {
    std::ofstream file(pendingCSVPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << pendingCSVPath << " for writing" << std::endl;
        return false;
    }
    
    // Write header first
    file << "enrollment_id,student_id,course_id" << std::endl;
    
    // Then write data
    Element* current = pendingQueue->front;
    while (current != nullptr) {
        file << current->data.toCSV() << std::endl;
        current = current->next;
    }
    
    file.close();
    return true;
}

bool QueueManager::loadPendingEnrollments() {
    std::ifstream file(pendingCSVPath);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << pendingCSVPath << std::endl;
        return false;
    }
    
    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            PendingEnrollment enrollment = parseCSVToEnrollment(line);
            if (enrollment.enrollmentId != 0) {
                enqueue(pendingQueue, enrollment);
            }
        }
    }
    
    file.close();
    std::cout << "Loaded " << getSize(pendingQueue) << " pending enrollments" << std::endl;
    return true;
}

void QueueManager::addPendingEnrollment(const PendingEnrollment& enrollment) {
    enqueue(pendingQueue, enrollment);
    writePendingEnrollments();
}

PendingEnrollment QueueManager::approveNext() {
    if (isEmpty(pendingQueue)) {
        throw std::runtime_error("No pending enrollments to approve");
    }
    
    PendingEnrollment enrollment = dequeue(pendingQueue);
    enrollment.status = "approved";
    
    moveToApproved(enrollment);
    writePendingEnrollments();
    
    return enrollment;
}

PendingEnrollment QueueManager::rejectNext() {
    if (isEmpty(pendingQueue)) {
        throw std::runtime_error("No pending enrollments to reject");
    }
    
    PendingEnrollment enrollment = dequeue(pendingQueue);
    enrollment.status = "rejected";
    
    writePendingEnrollments();
    
    return enrollment;
}

bool QueueManager::approveAll() {
    if (isEmpty(pendingQueue)) {
        return false;
    }
    
    int approved = 0;
    while (!isEmpty(pendingQueue)) {
        PendingEnrollment enrollment = dequeue(pendingQueue);
        enrollment.status = "approved";
        moveToApproved(enrollment);
        approved++;
    }
    
    writePendingEnrollments();
    std::cout << "Approved " << approved << " enrollments" << std::endl;
    return true;
}

bool QueueManager::removePendingEnrollment(int enrollmentId) {
    if (isEmpty(pendingQueue)) {
        return false;
    }
    
    // Build new queue without the enrollment
    Queue* newQueue = createQueue();
    Element* current = pendingQueue->front;
    
    while (current != nullptr) {
        if (current->data.enrollmentId != enrollmentId) {
            enqueue(newQueue, current->data);
        }
        current = current->next;
    }
    
    // Replace old queue with new one
    deleteQueue(pendingQueue);
    pendingQueue = newQueue;
    
    writePendingEnrollments();
    return true;
}

bool QueueManager::isEnrollmentPending(int enrollmentId) const {
    Element* current = pendingQueue->front;
    while (current != nullptr) {
        if (current->data.enrollmentId == enrollmentId) {
            return true;
        }
        current = current->next;
    }
    return false;
}

std::vector<PendingEnrollment> QueueManager::getPendingEnrollments() const {
    std::vector<PendingEnrollment> result;
    Element* current = pendingQueue->front;
    while (current != nullptr) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

void QueueManager::displayPendingEnrollments() const {
    displayQueue(pendingQueue);
}

int QueueManager::getPendingCount() const {
    return getSize(pendingQueue);
}

bool QueueManager::moveToApproved(const PendingEnrollment& enrollment) {
    std::ofstream file(enrollmentsCSVPath, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << enrollmentsCSVPath << " for writing" << std::endl;
        return false;
    }
    
    file << enrollment.enrollmentId << ","
         << enrollment.studentId << ","
         << enrollment.courseId << ","
         << "approved" << std::endl;
    file.close();
    
    std::cout << "Enrollment " << enrollment.enrollmentId << " approved!" << std::endl;
    return true;
}