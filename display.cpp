#include"display.h"
#include <iostream>
#include <role.h>
using namespace std;
display::display(){}
display::~display(){}
role display::login(){
    string tendangnhap, matkhau;
    cout<<"== Coffee shop management app =="<<endl;
    cout<<"ten dang nhap: ";
    cin>>tendangnhap;
    cout<<"mat khau: ";
    cin>>matkhau;
    if(tendangnhap == "quanli" && matkhau == "0702"){
        cout<<" he thong quan li"<<endl;
        return role::quanli;
    }
    else if(tendangnhap == "nhanvien" && matkhau == "0702")
    {
        cout<<" he thong nhan vien" <<endl;
        return role::nhanvien;
    }
    else{
        cout<<"dang nhap that bai" <<endl;
        return role::exit;
    }
}
void display::MenuManager(){
    cout<<"==== menu quan li ==="<<endl;
    cout<<"0. thoat"<<endl;
    cout<<"1. quan li menu"<<endl;
    cout<<"2.quan li don"<<endl;
    cout<<"3.quan li nhan vieen"<<endl;
    cout<<"4.thong ke"<<endl;
    cout<<"\n choice: ";
}
void display::MenuEmployee(){
    cout<<"==== menu nhan vien ==="<<endl;
    cout<<"0. thoat"<<endl;
    cout<<"1.xem va tim kiem san pham"<<endl;
    cout<<"2. dat mon"<<endl;
    cout<<"3. huy don"<<endl;
    cout<<"4. thanh toan"<<endl;
    cout<<"\n choice: ";
}
