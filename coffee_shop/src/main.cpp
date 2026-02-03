#include <iostream>
#include <memory>
#include <string>
#include "managers/MenuManager.h"
#include "managers/PaymentManager.h"

using namespace std;

// Function prototypes
void showMainMenu();
void showWelcomeScreen();
void runMenuManager(shared_ptr<MenuManager> menuManager);
void runPaymentManager(shared_ptr<PaymentManager> paymentManager);
void showReports(shared_ptr<PaymentManager> paymentManager);

int main() {
    showWelcomeScreen();
    
    // Initialize managers
    auto menuManager = make_shared<MenuManager>();
    auto paymentManager = make_shared<PaymentManager>(menuManager);
    
    string employeeId = "NV001"; // Default employee ID
    int choice;
    
    do {
        showMainMenu();
        cout << "Lua chon: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                runMenuManager(menuManager);
                break;
            case 2:
                runPaymentManager(paymentManager);
                break;
            case 3:
                showReports(paymentManager);
                break;
            case 4:
                cout << "\n👤 THAY DOI TAI KHOAN NHAN VIEN\n";
                cout << "Nhap ma nhan vien (VD: NV001, NV002): ";
                cin >> employeeId;
                cout << "✅ Da chuyen sang tai khoan: " << employeeId << endl;
                break;
            case 0:
                cout << "\n👋 Thoat chuong trinh. Hen gap lai!\n";
                break;
            default:
                cout << "❌ Lua chon khong hop le! Vui long chon 0-4.\n";
        }
        
        // Clear input buffer
        cin.clear();
        cin.ignore(10000, '\n');
        
    } while (choice != 0);
    
    return 0;
}

void showWelcomeScreen() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════╗\n";
    cout << "║         ☕ QUAN CAFE NHOM 4 ☕           ║\n";
    cout << "║   HE THONG QUAN LY BAN HANG & THANH TOAN ║\n";
    cout << "╚══════════════════════════════════════════╝\n";
    cout << "🌐 Phien ban: 1.0.0 | macOS\n";
    cout << "📅 Ngay: " << __DATE__ << " | " << __TIME__ << "\n";
    cout << "👥 Nhom 4 - Quan ly Quan Cafe\n";
    cout << "════════════════════════════════════════════\n";
}

void showMainMenu() {
    cout << "\n";
    cout << "┌─────────────────────────────────────────┐\n";
    cout << "│           MENU CHINH                    │\n";
    cout << "├─────────────────────────────────────────┤\n";
    cout << "│  1. 📋 Quan ly Menu                     │\n";
    cout << "│  2. 💰 Ban hang & Thanh toan           │\n";
    cout << "│  3. 📊 Thong ke & Bao cao              │\n";
    cout << "│  4. 👤 Doi tai khoan                   │\n";
    cout << "│  0. 🚪 Thoat                           │\n";
    cout << "└─────────────────────────────────────────┘\n";
}

void runMenuManager(shared_ptr<MenuManager> menuManager) {
    cout << "\n";
    cout << "════════════════════════════════════════════\n";
    cout << "          📋 QUAN LY MENU SAN PHAM         \n";
    cout << "════════════════════════════════════════════\n";
    
    menuManager->runMenuManager();
}

void runPaymentManager(shared_ptr<PaymentManager> paymentManager) {
    string employeeId = "NV001"; // Default employee
    
    cout << "\n";
    cout << "════════════════════════════════════════════\n";
    cout << "          💰 BAN HANG & THANH TOAN         \n";
    cout << "════════════════════════════════════════════\n";
    cout << "Nhap ma nhan vien (mac dinh: NV001): ";
    
    string input;
    getline(cin, input);
    if (!input.empty()) {
        employeeId = input;
    }
    
    cout << "👤 Nhan vien hien tai: " << employeeId << endl;
    
    paymentManager->runPaymentManager(employeeId);
}

void showReports(shared_ptr<PaymentManager> paymentManager) {
    int reportChoice;
    
    do {
        cout << "\n";
        cout << "════════════════════════════════════════════\n";
        cout << "          📊 THONG KE & BAO CAO            \n";
        cout << "════════════════════════════════════════════\n";
        cout << "1. 📈 Thong ke don hang\n";
        cout << "2. 💰 Bao cao doanh thu\n";
        cout << "3. 📋 Xem tat ca don hang\n";
        cout << "4. 🔍 Tim kiem don hang\n";
        cout << "0. ↩️  Quay lai\n";
        cout << "Lua chon: ";
        cin >> reportChoice;
        
        switch(reportChoice) {
            case 1:
                cout << "\n";
                cout << "════════════════════════════════════════════\n";
                cout << "           📈 THONG KE DON HANG            \n";
                cout << "════════════════════════════════════════════\n";
                paymentManager->viewOrderStatistics();
                break;
            case 2:
                cout << "\n";
                cout << "════════════════════════════════════════════\n";
                cout << "           💰 BAO CAO DOANH THU            \n";
                cout << "════════════════════════════════════════════\n";
                paymentManager->viewRevenueReport();
                break;
            case 3:
                cout << "\n";
                cout << "════════════════════════════════════════════\n";
                cout << "           📋 TAT CA DON HANG              \n";
                cout << "════════════════════════════════════════════\n";
                paymentManager->viewAllOrders();
                break;
            case 4:
                cout << "\n";
                cout << "════════════════════════════════════════════\n";
                cout << "           🔍 TIM KIEM DON HANG            \n";
                cout << "════════════════════════════════════════════\n";
                paymentManager->searchOrder();
                break;
            case 0:
                cout << "Quay lai menu chinh...\n";
                break;
            default:
                cout << "❌ Lua chon khong hop le!\n";
        }
        
        if (reportChoice != 0) {
            cout << "\nNhan Enter de tiep tuc...";
            cin.ignore();
            cin.get();
        }
        
    } while (reportChoice != 0);
}

// Helper function to clear screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Helper function to pause execution
void pauseProgram() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}