#include "Employee.h"
#include <iostream>

Employee::Employee() {
    id = "";
    name = "";
    birthDate = "";
    phone = "";
    role = "NhanVien";
    username = "";
    password = "";
}

Employee::Employee(string id, string name, string birthDate,
                   string phone, string role,
                   string username, string password) {
    this->id = id;
    this->name = name;
    this->birthDate = birthDate;
    this->phone = phone;
    this->role = role;
    this->username = username;
    this->password = password;
}

// Getter
string Employee::getId() { return id; }
string Employee::getName() { return name; }
string Employee::getBirthDate() { return birthDate; }
string Employee::getPhone() { return phone; }
string Employee::getRole() { return role; }
string Employee::getUsername() { return username; }

// Setter
void Employee::setName(string name) { this->name = name; }
void Employee::setBirthDate(string birthDate) { this->birthDate = birthDate; }
void Employee::setPhone(string phone) { this->phone = phone; }
void Employee::setRole(string role) { this->role = role; }
void Employee::setPassword(string password) { this->password = password; }

// Hiển thị
void Employee::display() {
    cout << "ID: " << id
         << " | Ten: " << name
         << " | Ngay sinh: " << birthDate
         << " | SDT: " << phone
         << " | Vai tro: " << role << endl;
}
