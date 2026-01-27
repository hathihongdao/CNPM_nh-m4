#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include "Employee.h"
#include <vector>

class EmployeeManager {
private:
    vector<Employee> list;

public:
    bool isDuplicateId(string id);

    void addEmployee(Employee emp);
    void updateEmployee(string id);
    void deleteEmployee(string id);
    void displayAll();
};

#endif
