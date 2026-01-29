#include "employee.h"
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;
void employee::xemvatimkiem(){
    cout<<"== xem va tim kiem san pham =="<<endl;
    ifstream file ("menu.txt");
    if (!file.is_open) {
        cout<<"khong the mơ file menu.txt"<<endl;
        return;
    }
    vector<string> tensanpham;
    vector<double> gia;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string tensanpham, gia;
        geline(ss, tensanpham,',');
        getline(ss, gia,',');
        tensanpham.push_back(tensanpham);
        gia.push_back(stod(gia));
    }
    file.close();
    //xem san pham
    cout<<"== danh sach san pham =="<<endl;
    for(int i = 0; i< tensanpham.size(); i++){
        cout<<i+1<<"."<<tensanpham[i]<<" - "<<gia[i]<<e
    }
}
