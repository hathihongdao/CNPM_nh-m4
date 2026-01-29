#include "NhanVien.h"
#include <iostream>
using namespace std;

// Hàm hiển thị menu chính
void hienThiMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "  HE THONG QUAN LY NHAN VIEN & DOANH THU\n";
    cout << "========================================\n";
    cout << "\n";
    cout << "  7. QUAN LY THONG TIN NHAN VIEN\n";
    cout << "     1. Xem danh sach nhan vien\n";
    cout << "     2. Them nhan vien moi\n";
    cout << "     3. Xoa nhan vien\n";
    cout << "     4. Cap nhat thong tin nhan vien\n";
    cout << "\n";
    cout << "  8. BAO CAO VA THONG KE DOANH THU\n";
    cout << "     5. Xem bao cao thong ke\n";
    cout << "\n";
    cout << "  0. Thoat chuong trinh\n";
    cout << "\n";
    cout << "========================================\n";
}

// Hàm hiển thị header đẹp
void hienThiHeader() {
    system("clear");  // Dùng "cls" nếu dùng Windows
    
    cout << "\n";
    cout << "========================================\n";
    cout << "                                        \n";
    cout << "       HE THONG QUAN LY NHAN VIEN       \n";
    cout << "          VA THONG KE DOANH THU         \n";
    cout << "                                        \n";
    cout << "          Phien ban 1.0 - 2025          \n";
    cout << "                                        \n";
    cout << "========================================\n";
}

int main() {
    QuanLyNhanVien qlnv;
    int luaChon;
    
    // Hiển thị header khi khởi động
    hienThiHeader();
    
    cout << "\n";
    cout << "  Dang tai du lieu...\n\n";
    
    if (qlnv.soLuongNhanVien() > 0) {
        cout << "  [OK] Da tai " << qlnv.soLuongNhanVien() << " nhan vien tu file.\n";
    } else {
        cout << "  [INFO] Chua co du lieu. Hay them nhan vien moi!\n";
    }
    
    cout << "\n  Nhan Enter de tiep tuc...";
    cin.get();
    
    do {
        system("clear");  // Dùng "cls" nếu dùng Windows
        hienThiMenu();
        
        cout << "\n========================================\n";
        cout << "  Nhap lua chon cua ban: ";
        cin >> luaChon;
        cout << "========================================\n";
        
        switch(luaChon) {
            case 1:
                qlnv.xemDanhSach();
                break;
                
            case 2:
                qlnv.themNhanVien();
                break;
                
            case 3:
                qlnv.xoaNhanVien();
                break;
                
            case 4:
                qlnv.capNhatNhanVien();
                break;
                
            case 5:
                qlnv.baoCaoDoanhThu();
                break;
                
            case 0:
                system("clear");  // Dùng "cls" nếu dùng Windows
                cout << "\n";
                cout << "========================================\n";
                cout << "\n";
                cout << "       CAM ON BAN DA SU DUNG!\n";
                cout << "\n";
                cout << "   Chuc ban mot ngay lam viec hieu qua!\n";
                cout << "\n";
                cout << "========================================\n\n";
                break;
                
            default:
                cout << "\n[LOI] Lua chon khong hop le! Vui long chon tu 0-5.\n";
                cout << "\nNhan Enter de tiep tuc...";
                cin.ignore();
                cin.get();
        }
        
    } while(luaChon != 0);
    
    return 0;
}