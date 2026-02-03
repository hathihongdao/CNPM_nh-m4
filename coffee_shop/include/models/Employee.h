#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

enum class EmployeeRole {
    STAFF,      // Nhân viên
    MANAGER,    // Quản lý
    ADMIN       // Quản trị
};

class Employee {
private:
    std::string id;
    std::string name;
    std::string birthDate;
    std::string phone;
    EmployeeRole role;
    std::string username;
    std::string password;
    bool isActive;
    
public:
    Employee(const std::string& id, const std::string& name, 
             const std::string& birthDate, const std::string& phone,
             EmployeeRole role, const std::string& username, 
             const std::string& password);
    
    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getBirthDate() const;
    std::string getPhone() const;
    EmployeeRole getRole() const;
    std::string getRoleString() const;
    std::string getUsername() const;
    bool getIsActive() const;
    
    // Authentication
    bool authenticate(const std::string& password) const;
    
    // Setters
    void setName(const std::string& name);
    void setPhone(const std::string& phone);
    void setRole(EmployeeRole role);
    void setPassword(const std::string& password);
    void setActive(bool active);
    
    void display() const;
    bool isManager() const;
};

#endif