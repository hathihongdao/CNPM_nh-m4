#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

class Employee {
private:
    string id;
    string name;
    string birthDate;
    string phone;
    string role;        // "NhanVien" hoặc "QuanLy"
    string username;
    string password;

public:
    Employee();
    Employee(string id, string name, string birthDate,
             string phone, string role,
             string username, string password);

    // Getter
    string getId();
    string getName();
    string getBirthDate();
    string getPhone();
    string getRole();
    string getUsername();

    // Setter
    void setName(string name);
    void setBirthDate(string birthDate);
    void setPhone(string phone);
    void setRole(string role);
    void setPassword(string password);

    // Hiển thị thông tin
    void display();
};

#endif
