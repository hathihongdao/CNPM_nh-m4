#include "NhanVien.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// ==================== CLASS NHANVIEN ====================

// Constructor mặc định
NhanVien::NhanVien() {
    maNV = "";
    tenNV = "";
    tuoi = 0;
    chucVu = "";
    luong = 0;
}

// Constructor có tham số
NhanVien::NhanVien(string ma, string ten, int t, string cv, double l) {
    maNV = ma;
    tenNV = ten;
    tuoi = t;
    chucVu = cv;
    luong = l;
}

// Các hàm Getter
string NhanVien::getMaNV() { return maNV; }
string NhanVien::getTenNV() { return tenNV; }
int NhanVien::getTuoi() { return tuoi; }
string NhanVien::getChucVu() { return chucVu; }
double NhanVien::getLuong() { return luong; }

// Các hàm Setter
void NhanVien::setTenNV(string ten) { tenNV = ten; }
void NhanVien::setTuoi(int t) { tuoi = t; }
void NhanVien::setChucVu(string cv) { chucVu = cv; }
void NhanVien::setLuong(double l) { luong = l; }

// Hiển thị thông tin 1 nhân viên
void NhanVien::hienThi() {
    cout << "| " << left << setw(10) << maNV 
         << "| " << setw(25) << tenNV 
         << "| " << setw(6) << tuoi 
         << "| " << setw(20) << chucVu 
         << "| " << right << setw(15) << fixed << setprecision(0) << luong << " |" << endl;
}

// ==================== CLASS QUANLYNHANVIEN ====================

// Constructor
QuanLyNhanVien::QuanLyNhanVien() {
    // Đọc dữ liệu từ file khi khởi tạo
    docFile();
}

// Thêm nhân viên mới
void QuanLyNhanVien::themNhanVien() {
    system("clear");  // Dùng "cls" nếu dùng Windows
    
    cout << "\n========================================\n";
    cout << "         THEM NHAN VIEN MOI\n";
    cout << "========================================\n\n";
    
    string ma, ten, cv;
    int t;
    double l;
    
    cout << "Nhap ma nhan vien: ";
    cin.ignore();
    getline(cin, ma);
    
    // Kiểm tra mã đã tồn tại chưa
    if (timNhanVien(ma) != -1) {
        cout << "\n[LOI] Ma nhan vien da ton tai! Vui long nhap ma khac.\n";
        cout << "\nNhan Enter de tiep tuc...";
        cin.get();
        return;
    }
    
    cout << "Nhap ten nhan vien: ";
    getline(cin, ten);
    
    cout << "Nhap tuoi: ";
    cin >> t;
    
    cin.ignore();
    cout << "Nhap chuc vu: ";
    getline(cin, cv);
    
    cout << "Nhap luong: ";
    cin >> l;
    
    // Tạo đối tượng nhân viên mới và thêm vào danh sách
    NhanVien nv(ma, ten, t, cv, l);
    danhSach.push_back(nv);
    
    // Lưu vào file
    luuFile();
    
    cout << "\n[OK] Them nhan vien thanh cong!\n";
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

// Xem danh sách tất cả nhân viên
void QuanLyNhanVien::xemDanhSach() {
    system("clear");  // Dùng "cls" nếu dùng Windows
    
    cout << "\n========================================\n";
    cout << "         DANH SACH NHAN VIEN\n";
    cout << "========================================\n\n";
    
    if (danhSach.empty()) {
        cout << "[CANH BAO] Danh sach nhan vien trong!\n\n";
        cout << "Nhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();
        return;
    }
    
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| Ma NV      | Ten nhan vien             | Tuoi   | Chuc vu              | Luong           |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < danhSach.size(); i++) {
        danhSach[i].hienThi();
    }
    
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "\nTong so nhan vien: " << danhSach.size() << "\n\n";
    cout << "Nhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

// Tìm nhân viên theo mã (trả về vị trí trong vector)
int QuanLyNhanVien::timNhanVien(string maNV) {
    for (int i = 0; i < danhSach.size(); i++) {
        if (danhSach[i].getMaNV() == maNV) {
            return i;  // Trả về vị trí tìm thấy
        }
    }
    return -1;  // Không tìm thấy
}

// Xóa nhân viên
void QuanLyNhanVien::xoaNhanVien() {
    system("clear");  // Dùng "cls" nếu dùng Windows
    
    cout << "\n========================================\n";
    cout << "            XOA NHAN VIEN\n";
    cout << "========================================\n\n";
    
    if (danhSach.empty()) {
        cout << "[CANH BAO] Danh sach nhan vien trong!\n\n";
        cout << "Nhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();
        return;
    }
    
    string ma;
    cout << "Nhap ma nhan vien can xoa: ";
    cin.ignore();
    getline(cin, ma);
    
    int viTri = timNhanVien(ma);
    
    if (viTri == -1) {
        cout << "\n[LOI] Khong tim thay nhan vien co ma: " << ma << "\n";
    } else {
        cout << "\nThong tin nhan vien se xoa:\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";
        cout << "| Ma NV      | Ten nhan vien             | Tuoi   | Chuc vu              | Luong           |\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";
        danhSach[viTri].hienThi();
        cout << "--------------------------------------------------------------------------------------------------------\n";
        
        char xacNhan;
        cout << "\nBan co chac chan muon xoa? (y/n): ";
        cin >> xacNhan;
        
        if (xacNhan == 'y' || xacNhan == 'Y') {
            danhSach.erase(danhSach.begin() + viTri);
            luuFile();
            cout << "\n[OK] Xoa nhan vien thanh cong!\n";
        } else {
            cout << "\n[HUY] Da huy thao tac xoa.\n";
        }
    }
    
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

// Cập nhật thông tin nhân viên
void QuanLyNhanVien::capNhatNhanVien() {
    system("clear");  // Dùng "cls" nếu dùng Windows
    
    cout << "\n========================================\n";
    cout << "      CAP NHAT THONG TIN NHAN VIEN\n";
    cout << "========================================\n\n";
    
    if (danhSach.empty()) {
        cout << "[CANH BAO] Danh sach nhan vien trong!\n\n";
        cout << "Nhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();
        return;
    }
    
    string ma;
    cout << "Nhap ma nhan vien can cap nhat: ";
    cin.ignore();
    getline(cin, ma);
    
    int viTri = timNhanVien(ma);
    
    if (viTri == -1) {
        cout << "\n[LOI] Khong tim thay nhan vien co ma: " << ma << "\n";
    } else {
        cout << "\nThong tin hien tai:\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";
        cout << "| Ma NV      | Ten nhan vien             | Tuoi   | Chuc vu              | Luong           |\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";
        danhSach[viTri].hienThi();
        cout << "--------------------------------------------------------------------------------------------------------\n\n";
        
        cout << "Nhap thong tin moi (Enter de giu nguyen):\n\n";
        
        string ten, cv;
        int t;
        double l;
        
        cout << "Ten moi: ";
        getline(cin, ten);
        if (!ten.empty()) {
            danhSach[viTri].setTenNV(ten);
        }
        
        cout << "Tuoi moi: ";
        string tuoiStr;
        getline(cin, tuoiStr);
        if (!tuoiStr.empty()) {
            t = stoi(tuoiStr);
            danhSach[viTri].setTuoi(t);
        }
        
        cout << "Chuc vu moi: ";
        getline(cin, cv);
        if (!cv.empty()) {
            danhSach[viTri].setChucVu(cv);
        }
        
        cout << "Luong moi: ";
        string luongStr;
        getline(cin, luongStr);
        if (!luongStr.empty()) {
            l = stod(luongStr);
            danhSach[viTri].setLuong(l);
        }
        
        luuFile();
        cout << "\n[OK] Cap nhat thong tin thanh cong!\n";
    }
    
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

// Lưu danh sách vào file
void QuanLyNhanVien::luuFile() {
    ofstream file("nhanvien.txt");
    
    if (!file.is_open()) {
        cout << "[LOI] Khong the mo file de ghi!\n";
        return;
    }
    
    // Ghi số lượng nhân viên
    file << danhSach.size() << endl;
    
    // Ghi thông tin từng nhân viên
    for (int i = 0; i < danhSach.size(); i++) {
        file << danhSach[i].getMaNV() << endl;
        file << danhSach[i].getTenNV() << endl;
        file << danhSach[i].getTuoi() << endl;
        file << danhSach[i].getChucVu() << endl;
        file << danhSach[i].getLuong() << endl;
    }
    
    file.close();
}

// Đọc danh sách từ file
void QuanLyNhanVien::docFile() {
    ifstream file("nhanvien.txt");
    
    if (!file.is_open()) {
        // File chưa tồn tại, tạo dữ liệu mẫu
        return;
    }
    
    danhSach.clear();  // Xóa danh sách cũ
    
    int soLuong;
    file >> soLuong;
    file.ignore();  // Bỏ qua ký tự xuống dòng
    
    for (int i = 0; i < soLuong; i++) {
        string ma, ten, cv;
        int t;
        double l;
        
        getline(file, ma);
        getline(file, ten);
        file >> t;
        file.ignore();
        getline(file, cv);
        file >> l;
        file.ignore();
        
        NhanVien nv(ma, ten, t, cv, l);
        danhSach.push_back(nv);
    }
    
    file.close();
}

// Báo cáo thống kê doanh thu
void QuanLyNhanVien::baoCaoDoanhThu() {
    system("clear");  // Dùng "cls" nếu dùng Windows
    
    cout << "\n========================================\n";
    cout << "     BAO CAO VA THONG KE DOANH THU\n";
    cout << "========================================\n\n";
    
    if (danhSach.empty()) {
        cout << "[CANH BAO] Khong co du lieu de thong ke!\n\n";
        cout << "Nhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();
        return;
    }
    
    // Tính tổng lương phải trả
    double tongLuong = 0;
    double luongCaoNhat = 0;
    double luongThapNhat = danhSach[0].getLuong();
    
    for (int i = 0; i < danhSach.size(); i++) {
        double luong = danhSach[i].getLuong();
        tongLuong += luong;
        
        if (luong > luongCaoNhat) {
            luongCaoNhat = luong;
        }
        if (luong < luongThapNhat) {
            luongThapNhat = luong;
        }
    }
    
    double luongTrungBinh = tongLuong / danhSach.size();
    
    cout << "========================================\n";
    cout << "         THONG KE TONG QUAN\n";
    cout << "========================================\n";
    cout << "Tong so nhan vien:      " << left << setw(31) << danhSach.size() << "\n";
    cout << "Tong quy luong/thang:   " << setw(25) << fixed << setprecision(0) << tongLuong << " VND\n";
    cout << "Luong trung binh:       " << setw(25) << luongTrungBinh << " VND\n";
    cout << "Luong cao nhat:         " << setw(25) << luongCaoNhat << " VND\n";
    cout << "Luong thap nhat:        " << setw(25) << luongThapNhat << " VND\n";
    cout << "========================================\n\n";
    
    // Thống kê theo chức vụ
    cout << "========================================\n";
    cout << "       THONG KE THEO CHUC VU\n";
    cout << "========================================\n";
    
    // Đếm số nhân viên theo chức vụ (cách đơn giản)
    vector<string> chucVuDaThongKe;
    
    for (int i = 0; i < danhSach.size(); i++) {
        string cv = danhSach[i].getChucVu();
        
        // Kiểm tra chức vụ đã thống kê chưa
        bool daTonTai = false;
        for (int j = 0; j < chucVuDaThongKe.size(); j++) {
            if (chucVuDaThongKe[j] == cv) {
                daTonTai = true;
                break;
            }
        }
        
        if (!daTonTai) {
            chucVuDaThongKe.push_back(cv);
            
            // Đếm số nhân viên và tính tổng lương của chức vụ này
            int dem = 0;
            double tongLuongCV = 0;
            
            for (int j = 0; j < danhSach.size(); j++) {
                if (danhSach[j].getChucVu() == cv) {
                    dem++;
                    tongLuongCV += danhSach[j].getLuong();
                }
            }
            
            cout << "  " << left << setw(20) << cv << ": " 
                 << right << setw(3) << dem << " nguoi - "
                 << setw(15) << fixed << setprecision(0) << tongLuongCV << " VND\n";
        }
    }
    
    cout << "========================================\n\n";
    
    // Dự báo chi phí
    cout << "========================================\n";
    cout << "           DU BAO CHI PHI\n";
    cout << "========================================\n";
    cout << "Chi phi quy (3 thang):  " << setw(25) << (tongLuong * 3) << " VND\n";
    cout << "Chi phi nam (12 thang): " << setw(25) << (tongLuong * 12) << " VND\n";
    cout << "========================================\n\n";
    
    cout << "Nhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

// Lấy số lượng nhân viên
int QuanLyNhanVien::soLuongNhanVien() {
    return danhSach.size();
}