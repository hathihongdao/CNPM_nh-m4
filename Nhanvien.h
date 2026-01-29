#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <string>
#include <vector>
using namespace std;

// Class đại diện cho 1 nhân viên
class NhanVien {
private:
    string maNV;        // Mã nhân viên
    string tenNV;       // Tên nhân viên
    int tuoi;           // Tuổi
    string chucVu;      // Chức vụ
    double luong;       // Lương cơ bản
    
public:
    // Constructor mặc định
    NhanVien();
    
    // Constructor có tham số
    NhanVien(string ma, string ten, int t, string cv, double l);
    
    // Getter - Lấy thông tin
    string getMaNV();
    string getTenNV();
    int getTuoi();
    string getChucVu();
    double getLuong();
    
    // Setter - Cập nhật thông tin
    void setTenNV(string ten);
    void setTuoi(int t);
    void setChucVu(string cv);
    void setLuong(double l);
    
    // Hiển thị thông tin 1 nhân viên
    void hienThi();
};

// Class quản lý danh sách nhân viên
class QuanLyNhanVien {
private:
    vector<NhanVien> danhSach;  // Danh sách nhân viên
    
public:
    // Constructor
    QuanLyNhanVien();
    
    // Thêm nhân viên mới
    void themNhanVien();
    
    // Xem danh sách tất cả nhân viên
    void xemDanhSach();
    
    // Tìm nhân viên theo mã
    int timNhanVien(string maNV);
    
    // Xóa nhân viên
    void xoaNhanVien();
    
    // Cập nhật thông tin nhân viên
    void capNhatNhanVien();
    
    // Lưu danh sách vào file
    void luuFile();
    
    // Đọc danh sách từ file
    void docFile();
    
    // Báo cáo thống kê doanh thu
    void baoCaoDoanhThu();
    
    // Lấy số lượng nhân viên
    int soLuongNhanVien();
};

#endif

