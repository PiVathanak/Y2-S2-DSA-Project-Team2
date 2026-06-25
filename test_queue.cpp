#include "Queue/QueueManager.h"
#include <iostream>

int main() {
    std::cout << "=== Testing Queue (Teacher's Style) ===" << std::endl;
    
    QueueManager qm;
    
    // Load from CSV
    std::cout << "\nLoading pending enrollments..." << std::endl;
    qm.loadPendingEnrollments();
    
    // Display current pending
    std::cout << "\nCurrent pending enrollments:" << std::endl;
    qm.displayPendingEnrollments();
    
    // Add a new pending enrollment
    std::cout << "\nAdding new enrollment..." << std::endl;
    PendingEnrollment newEnroll(4, 104, 203);
    qm.addPendingEnrollment(newEnroll);
    
    // Display after adding
    std::cout << "\nAfter adding new enrollment:" << std::endl;
    qm.displayPendingEnrollments();
    
    // Approve one
    std::cout << "\nApproving next enrollment..." << std::endl;
    try {
        PendingEnrollment approved = qm.approveNext();
        std::cout << "Approved: Student " << approved.studentId 
                  << " for Course " << approved.courseId << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Display after approve
    std::cout << "\nAfter approving:" << std::endl;
    qm.displayPendingEnrollments();
    
    // Remove an enrollment (undo)
    std::cout << "\nRemoving enrollment ID 2 (simulating student undo)..." << std::endl;
    if (qm.removePendingEnrollment(2)) {
        std::cout << "Removed enrollment ID 2" << std::endl;
    } else {
        std::cout << "Enrollment ID 2 not found" << std::endl;
    }
    
    // Final display
    std::cout << "\nFinal pending enrollments:" << std::endl;
    qm.displayPendingEnrollments();
    
    std::cout << "\nQueue test complete!" << std::endl;
    
    return 0;
}