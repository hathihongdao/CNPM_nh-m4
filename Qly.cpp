#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// ===== STRUCT =====
struct SanPham {
    string maMon;
    string tenMon;
    double gia;
};

struct ChiTietDon {
    string maMon;
    string tenMon;
    int soLuong;
    double gia;
};

struct NhanVien {
    string user;
    string pass;
    string chucVu;
};

// ===== GLOBAL =====
vector<SanPham> menu = {
    {"CF01","Ca phe den",20000},
    {"CF02","Ca phe sua",25000},
    {"TS01","Tra sua",30000},
    {"TS02","Tra dao",28000}
};

vector<ChiTietDon> donHang;
vector<NhanVien> dsNhanVien = {
    {"admin","admin123","Quan ly"},
    {"nv1","123","Nhan vien"}
};

NhanVien nguoiDung;

// ===== UTILITY =====
void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

void cls() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ===== LOGIN =====
bool dangNhap() {
    string u,p;
    for(int i=0;i<3;i++) {
        cout<<"Ten dang nhap: ";
        cin>>u;
        cout<<"Mat khau: ";
        cin>>p;

        for(auto &nv: dsNhanVien) {
            if(nv.user==u && nv.pass==p) {
                nguoiDung = nv;
                return true;
            }
        }
        cout<<"Sai thong tin!\n";
    }
    return false;
}

// ===== MENU =====
void xemMenu() {
    cls();
    cout<<"=== MENU ===\n";
    cout<<left<<setw(10)<<"Ma"<<setw(20)<<"Ten"<<setw(10)<<"Gia\n";
    for(auto &sp: menu) {
        cout<<setw(10)<<sp.maMon<<setw(20)<<sp.tenMon<<sp.gia<<"\n";
    }
    pause();
}

void datMon() {
    string ma;
    int sl;
    cls();
    xemMenu();
    cout<<"Nhap ma mon: ";
    cin>>ma;
    cout<<"So luong: ";
    cin>>sl;

    for(auto &sp: menu) {
        if(sp.maMon==ma) {
            donHang.push_back({sp.maMon,sp.tenMon,sl,sp.gia});
            cout<<"Da them mon!\n";
            pause();
            return;
        }
    }
    cout<<"Khong tim thay mon!\n";
    pause();
}

void xemDonHang() {
    cls();
    double tong=0;
    cout<<"=== DON HANG ===\n";
    for(auto &ct: donHang) {
        double tt = ct.soLuong * ct.gia;
        cout<<ct.tenMon<<" x"<<ct.soLuong<<" = "<<tt<<"\n";
        tong += tt;
    }
    cout<<"Tong tien: "<<tong<<"\n";
    pause();
}

void thanhToan() {
    if(donHang.empty()) {
        cout<<"Khong co don hang!\n";
        pause();
        return;
    }
    xemDonHang();
    cout<<"Thanh toan thanh cong!\n";
    donHang.clear();
    pause();
}

// ===== MENU NHAN VIEN =====
void menuNhanVien() {
    int ch;
    do {
        cls();
        cout<<"=== MENU NHAN VIEN ===\n";
        cout<<"1. Xem menu\n";
        cout<<"2. Dat mon\n";
        cout<<"3. Xem don hang\n";
        cout<<"4. Thanh toan\n";
        cout<<"0. Dang xuat\n";
        cout<<"Chon: ";
        cin>>ch;
        clearInput();

        switch(ch) {
            case 1: xemMenu(); break;
            case 2: datMon(); break;
            case 3: xemDonHang(); break;
            case 4: thanhToan(); break;
        }
    } while(ch!=0);
}

// ===== MENU QUAN LY =====
void menuQuanLy() {
    int ch;
    do {
        cls();
        cout<<"=== MENU QUAN LY ===\n";
        cout<<"1. Xem menu\n";
        cout<<"2. Dat mon\n";
        cout<<"3. Xem don hang\n";
        cout<<"4. Thanh toan\n";
        cout<<"0. Dang xuat\n";
        cout<<"Chon: ";
        cin>>ch;
        clearInput();

        switch(ch) {
            case 1: xemMenu(); break;
            case 2: datMon(); break;
            case 3: xemDonHang(); break;
            case 4: thanhToan(); break;
        }
    } while(ch!=0);
}

// ===== MAIN =====
int main() {
    cout<<"HE THONG QUAN LY QUAN CA PHE\n";

    if(!dangNhap()) {
        cout<<"Dang nhap that bai!\n";
        return 0;
    }

    if(nguoiDung.chucVu=="Quan ly")
        menuQuanLy();
    else
        menuNhanVien();

    return 0;
}
