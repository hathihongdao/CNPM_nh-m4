#include "models/Employee.h"
#include <iostream>
#include <iomanip>

Employee::Employee(const std::string& id, const std::string& name, 
                   const std::string& birthDate, const std::string& phone,
                   EmployeeRole role, const std::string& username, 
                   const std::string& password)
    : id(id), name(name), birthDate(birthDate), phone(phone),
      role(role), username(username), password(password), isActive(true) {}

std::string Employee::getId() const { return id; }
std::string Employee::getName() const { return name; }
std::string Employee::getBirthDate() const { return birthDate; }
std::string Employee::getPhone() const { return phone; }
EmployeeRole Employee::getRole() const { return role; }
std::string Employee::getUsername() const { return username; }
bool Employee::getIsActive() const { return isActive; }

std::string Employee::getRoleString() const {
    switch(role) {
        case EmployeeRole::STAFF: return "Nhan vien";
        case EmployeeRole::MANAGER: return "Quan ly";
        case EmployeeRole::ADMIN: return "Quan tri";
        default: return "Unknown";
    }
}

bool Employee::authenticate(const std::string& inputPassword) const {
    return isActive && (password == inputPassword);
}

void Employee::setName(const std::string& name) { this->name = name; }
void Employee::setPhone(const std::string& phone) { this->phone = phone; }
void Employee::setRole(EmployeeRole role) { this->role = role; }
void Employee::setPassword(const std::string& password) { this->password = password; }
void Employee::setActive(bool active) { this->isActive = active; }

bool Employee::isManager() const {
    return role == EmployeeRole::MANAGER || role == EmployeeRole::ADMIN;
}

void Employee::display() const {
    std::cout << std::left 
              << std::setw(8) << id
              << std::setw(20) << name
              << std::setw(12) << birthDate
              << std::setw(15) << phone
              << std::setw(12) << getRoleString()
              << std::setw(10) << (isActive ? "Dang lam" : "Nghi viec") << std::endl;
}