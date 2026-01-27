#include "EmployeeManager.h"
#include <iostream>

bool EmployeeManager::isDuplicateId(string id) {
    for (auto &e : list) {
        if (e.getId() == id)
            return true;
    }
    return false;
}

void EmployeeManager::addEmployee(Employee emp) {
    if (isDuplicateId(emp.getId())) {
        cout << "Loi: Ma nhan vien bi trung!\n";
        return;
    }
    list.push_back(emp);
    cout << "Them nhan vien thanh cong!\n";
}

void EmployeeManager::updateEmployee(string id) {
    for (auto &e : list) {
        if (e.getId() == id) {
            string name, phone, birth;
            cout << "Nhap ten moi: ";
            getline(cin, name);
            cout << "Nhap so dien thoai moi: ";
            getline(cin, phone);
            cout << "Nhap ngay sinh moi: ";
            getline(cin, birth);

            e.setName(name);
            e.setPhone(phone);
            e.setBirthDate(birth);

            cout << "Cap nhat thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay nhan vien!\n";
}

void EmployeeManager::deleteEmployee(string id) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i].getId() == id) {
            list.erase(list.begin() + i);
            cout << "Xoa nhan vien thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay nhan vien!\n";
}

void EmployeeManager::displayAll() {
    if (list.empty()) {
        cout << "Danh sach nhan vien rong!\n";
        return;
    }
    for (auto &e : list) {
        e.display();
    }
}
