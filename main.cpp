#include "EmployeeManager.h"
#include <iostream>

int main() {
    EmployeeManager manager;

    Employee e1("NV01", "Nguyen Van A", "01/01/2000",
                "0901234567", "NhanVien",
                "nv01", "123456");

    manager.addEmployee(e1);
    manager.displayAll();

    manager.updateEmployee("NV01");
    manager.displayAll();

    manager.deleteEmployee("NV01");
    manager.displayAll();

    return 0;
}
