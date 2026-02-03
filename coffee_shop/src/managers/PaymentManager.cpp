#include "managers/PaymentManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>

PaymentManager::PaymentManager(std::shared_ptr<MenuManager> menuManager)
    : menuManager(menuManager), orderCounter(1) {}

std::string PaymentManager::generateOrderId() {
    time_t now = time(nullptr);
    tm localTime;
    localtime_r(&now, &localTime);
    
    std::stringstream ss;
    ss << "ORD" << (localTime.tm_year + 1900) 
       << std::setw(2) << std::setfill('0') << (localTime.tm_mon + 1)
       << std::setw(2) << std::setfill('0') << localTime.tm_mday
       << std::setw(4) << std::setfill('0') << orderCounter++;
    
    return ss.str();
}

std::shared_ptr<Order> PaymentManager::findOrderById(const std::string& orderId) {
    auto it = orderMap.find(orderId);
    if (it != orderMap.end()) {
        return it->second;
    }
    return nullptr;
}

bool PaymentManager::simulateCashPayment(double amount) {
    std::cout << "\n=== MO PHONG THANH TOAN TIEN MAT ===\n";
    std::cout << "So tien can thanh toan: " << std::fixed << std::setprecision(0) 
              << amount << " VND\n";
    
    double cashReceived;
    std::cout << "Nhap so tien nhan tu khach: ";
    std::cin >> cashReceived;
    
    if (cashReceived < amount) {
        std::cout << "Tien nhan khong du! Con thieu: " << (amount - cashReceived) 
                  << " VND\n";
        return false;
    }
    
    double change = cashReceived - amount;
    if (change > 0) {
        std::cout << "Tien thua tra khach: " << change << " VND\n";
    }
    
    std::cout << "Dang xu ly thanh toan...";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << " Thanh cong!\n";
    
    return true;
}

bool PaymentManager::simulateBankTransfer(double amount, const std::string& bankCode) {
    std::cout << "\n=== MO PHONG CHUYEN KHOAN NGAN HANG ===\n";
    std::cout << "So tien: " << std::fixed << std::setprecision(0) 
              << amount << " VND\n";
    std::cout << "Ngan hang: " << bankCode << std::endl;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    std::string transactionId = "TRX" + std::to_string(dis(gen));
    
    std::cout << "\nThong tin giao dich:\n";
    std::cout << "Ma giao dich: " << transactionId << std::endl;
    std::cout << "So tien: " << amount << " VND\n";
    
    time_t now = time(nullptr);
    char timeStr[100];
    tm timeInfo;
    localtime_r(&now, &timeInfo);
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S %d/%m/%Y", &timeInfo);
    std::cout << "Thoi gian: " << timeStr << std::endl;
    
    std::cout << "\nVui long xac nhan thanh toan trong app ngan hang...\n";
    std::cout << "Cho doi xac nhan";
    
    for (int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
    }
    std::cout << "\n";
    
    std::uniform_int_distribution<> successDis(1, 10);
    if (successDis(gen) <= 9) {
        std::cout << "✅ Chuyen khoan thanh cong!\n";
        std::cout << "Ma giao dich: " << transactionId << std::endl;
        return true;
    } else {
        std::cout << "❌ Chuyen khoan that bai! Vui long thu lai.\n";
        return false;
    }
}

bool PaymentManager::simulateQRPayment(double amount) {
    std::cout << "\n=== MO PHONG THANH TOAN QR CODE ===\n";
    std::cout << "So tien: " << std::fixed << std::setprecision(0) 
              << amount << " VND\n";
    
    std::cout << "\n┌─────────────────────────────────────┐\n";
    std::cout << "│           MA THANH TOAN QR          │\n";
    std::cout << "│                                     │\n";
    std::cout << "│  ████████████████████████████████  │\n";
    std::cout << "│  ████████████████████████████████  │\n";
    std::cout << "│  ████  ██    ████  ████    ██████  │\n";
    std::cout << "│  ████  ██████  ██    ████  ██████  │\n";
    std::cout << "│  ████  ████      ██  ████  ██████  │\n";
    std::cout << "│  ████    ██  ████  ██    ████████  │\n";
    std::cout << "│  ████████████████████████████████  │\n";
    std::cout << "│  ████████████████████████████████  │\n";
    std::cout << "│                                     │\n";
    std::cout << "│  So tien: " << std::setw(10) << amount << " VND  │\n";
    std::cout << "│  Thoi han: 05 phut                │\n";
    std::cout << "└─────────────────────────────────────┘\n";
    
    std::cout << "\nQuet ma QR de thanh toan...\n";
    std::cout << "Cho doi xac nhan";
    
    for (int i = 0; i < 5; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
    }
    std::cout << "\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    if (dis(gen) <= 85) {
        std::cout << "✅ Thanh toan QR thanh cong!\n";
        
        std::uniform_int_distribution<> transDis(10000000, 99999999);
        std::string qrTransId = "QR" + std::to_string(transDis(gen));
        std::cout << "Ma giao dich: " << qrTransId << std::endl;
        
        return true;
    } else {
        std::cout << "❌ Thanh toan that bai! Ma QR da het han.\n";
        return false;
    }
}

std::shared_ptr<Order> PaymentManager::createNewOrder(const std::string& employeeId) {
    std::string orderId = generateOrderId();
    auto newOrder = std::make_shared<Order>(orderId, employeeId);
    
    orders.push_back(newOrder);
    orderMap[orderId] = newOrder;
    
    std::cout << "\n✅ Tao don hang moi thanh cong!\n";
    std::cout << "📋 Ma don: " << orderId << std::endl;
    std::cout << "👨‍💼 Nhan vien: " << employeeId << std::endl;
    
    return newOrder;
}

void PaymentManager::addItemToOrder(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (!order) {
        std::cout << "❌ Khong tim thay don hang!\n";
        return;
    }
    
    if (order->getStatus() != OrderStatus::PENDING && order->getStatus() != OrderStatus::CONFIRMED) {
        std::cout << "❌ Don hang khong the them mon!\n";
        return;
    }
    
    std::cout << "\n=== THEM MON VAO DON HANG ===\n";
    
    auto availableProducts = menuManager->getAvailableProducts();
    if (availableProducts.empty()) {
        std::cout << "⚠️  Khong co mon nao san sang!\n";
        return;
    }
    
    std::cout << "\n📋 Danh sach mon co san:\n";
    std::cout << std::string(85, '=') << std::endl;
    std::cout << std::left 
              << std::setw(8) << "Ma mon" 
              << std::setw(25) << "Ten mon"
              << std::setw(15) << "Danh muc"
              << std::setw(12) << "Gia (VND)"
              << std::setw(15) << "Trang thai"
              << std::setw(10) << "Ton kho" << std::endl;
    std::cout << std::string(85, '=') << std::endl;
    
    for (const auto& product : availableProducts) {
        product->display();
    }
    
    std::string productId;
    std::cout << "\n📝 Nhap ma mon muon them: ";
    std::cin >> productId;
    
    auto product = menuManager->getProductById(productId);
    if (!product || !product->isAvailable()) {
        std::cout << "❌ Mon khong ton tai hoac khong co san!\n";
        return;
    }
    
    int quantity;
    std::cout << "🔢 Nhap so luong: ";
    std::cin >> quantity;
    
    if (quantity <= 0) {
        std::cout << "❌ So luong khong hop le!\n";
        return;
    }
    
    if (quantity > product->getStock()) {
        std::cout << "❌ Khong du so luong trong kho! Chi con " 
                  << product->getStock() << "\n";
        return;
    }
    
    std::string note;
    std::cout << "📝 Nhap ghi chu (neu co): ";
    std::cin.ignore();
    std::getline(std::cin, note);
    
    order->addItem(product, quantity, note);
    std::cout << "\n✅ Da them " << quantity << " " << product->getName() 
              << " vao don hang!\n";
}

void PaymentManager::viewCurrentOrder(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (order) {
        order->displayOrder();
    } else {
        std::cout << "❌ Khong tim thay don hang!\n";
    }
}

void PaymentManager::confirmOrder(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (order) {
        order->confirmOrder();
        
        // Cập nhật tồn kho
        for (const auto& item : order->getItems()) {
            menuManager->updateProductStock(
                item->getProduct()->getId(),
                item->getQuantity()
            );
        }
        
        std::cout << "\n✅ Don hang da duoc xac nhan va cap nhat ton kho!\n";
    } else {
        std::cout << "❌ Khong tim thay don hang!\n";
    }
}

void PaymentManager::markOrderAsPreparing(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (order) {
        if (order->getStatus() == OrderStatus::CONFIRMED) {
            order->startPreparing();
            std::cout << "\n✅ Don hang dang duoc pha che!\n";
        } else {
            std::cout << "❌ Don hang chua duoc xac nhan!\n";
        }
    }
}

void PaymentManager::markOrderAsCompleted(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (order) {
        if (order->getStatus() == OrderStatus::PREPARING) {
            order->completeOrder();
            std::cout << "\n✅ Don hang da hoan thanh! San sang cho thanh toan.\n";
        } else {
            std::cout << "❌ Don hang chua san sang de hoan thanh!\n";
        }
    }
}

void PaymentManager::processVirtualPayment(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (!order) {
        std::cout << "❌ Khong tim thay don hang!\n";
        return;
    }
    
    if (order->getStatus() != OrderStatus::COMPLETED) {
        std::cout << "❌ Don hang chua san sang de thanh toan!\n";
        std::cout << "Trang thai hien tai: " << order->getStatusString() << std::endl;
        return;
    }
    
    if (order->getIsPaid()) {
        std::cout << "⚠️  Don hang da duoc thanh toan truoc do!\n";
        order->displayBill();
        return;
    }
    
    double totalAmount = order->getTotalAmount();
    std::cout << "\n💰 THANH TOAN DON HANG " << orderId << "\n";
    std::cout << "Tong tien: " << std::fixed << std::setprecision(0) 
              << totalAmount << " VND\n";
    
    int paymentMethod;
    std::cout << "\n💳 Chon phuong thuc thanh toan:\n";
    std::cout << "1. Tien mat (Cash)\n";
    std::cout << "2. Chuyen khoan ngan hang\n";
    std::cout << "3. QR Code\n";
    std::cout << "0. Huy\n";
    std::cout << "Lua chon: ";
    std::cin >> paymentMethod;
    
    bool paymentSuccess = false;
    std::string methodName = "";
    
    switch (paymentMethod) {
        case 1: // Tiền mặt
            methodName = "Tien mat";
            paymentSuccess = simulateCashPayment(totalAmount);
            break;
            
        case 2: // Chuyển khoản
            methodName = "Chuyen khoan";
            {
                std::string bankCode;
                std::cout << "Nhap ma ngan hang (VD: VCB, BIDV, TCB): ";
                std::cin >> bankCode;
                paymentSuccess = simulateBankTransfer(totalAmount, bankCode);
            }
            break;
            
        case 3: // QR Code
            methodName = "QR Code";
            paymentSuccess = simulateQRPayment(totalAmount);
            break;
            
        case 0:
            std::cout << "Huy thanh toan.\n";
            return;
            
        default:
            std::cout << "Lua chon khong hop le!\n";
            return;
    }
    
    if (paymentSuccess) {
        order->processPayment(methodName);
        
        std::cout << "\n🎉 THANH TOAN THANH CONG!\n";
        std::cout << "Don hang: " << orderId << std::endl;
        std::cout << "Phuong thuc: " << methodName << std::endl;
        std::cout << "Tong tien: " << totalAmount << " VND\n";
        
        std::cout << "\n📄 HOA DON THANH TOAN:\n";
        order->displayBill();
        
        std::cout << "\n💾 Da luu thong tin thanh toán vao he thong.\n";
    } else {
        std::cout << "\n❌ THANH TOAN THAT BAI!\n";
        std::cout << "Vui long thu lai hoac chon phuong thuc khac.\n";
    }
}

void PaymentManager::cancelOrderItem(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (!order) {
        std::cout << "❌ Khong tim thay don hang!\n";
        return;
    }
    
    if (order->getStatus() == OrderStatus::PREPARING) {
        std::cout << "❌ Khong the huy mon khi don dang duoc pha che!\n";
        return;
    }
    
    auto items = order->getItems();
    if (items.empty()) {
        std::cout << "📭 Don hang trong!\n";
        return;
    }
    
    std::cout << "\n=== HUY MON TRONG DON ===\n";
    
    std::cout << "\n📋 Danh sach mon trong don:\n";
    std::cout << std::string(80, '-') << std::endl;
    std::cout << std::left 
              << std::setw(8) << "Ma mon"
              << std::setw(25) << "Ten mon"
              << std::setw(8) << "SL"
              << std::setw(15) << "Ghi chu" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& item : items) {
        std::cout << std::left 
                  << std::setw(8) << item->getProduct()->getId()
                  << std::setw(25) << item->getProduct()->getName()
                  << std::setw(8) << item->getQuantity()
                  << std::setw(15) << item->getNote() << std::endl;
    }
    
    std::string productId;
    std::cout << "\nNhap ma mon can huy: ";
    std::cin >> productId;
    
    bool found = false;
    for (const auto& item : items) {
        if (item->getProduct()->getId() == productId) {
            order->removeItem(productId);
            
            // Hoàn lại tồn kho nếu đã xác nhận
            if (order->getStatus() == OrderStatus::CONFIRMED) {
                menuManager->updateProductStock(productId, -item->getQuantity());
                std::cout << "Da hoan lai " << item->getQuantity() 
                          << " " << item->getProduct()->getName() << " vao kho!\n";
            }
            
            std::cout << "✅ Da huy mon " << item->getProduct()->getName() 
                      << " khoi don hang!\n";
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "❌ Khong tim thay mon trong don hang!\n";
    }
}

void PaymentManager::cancelEntireOrder(const std::string& orderId) {
    auto order = findOrderById(orderId);
    if (!order) {
        std::cout << "❌ Khong tim thay don hang!\n";
        return;
    }
    
    if (order->getStatus() == OrderStatus::PREPARING) {
        std::cout << "❌ Khong the huy don hang dang duoc pha che!\n";
        return;
    }
    
    std::cout << "\n⚠️  XAC NHAN HUY TOAN BO DON HANG " << orderId << "\n";
    std::cout << "Tong so mon: " << order->getItems().size() << "\n";
    std::cout << "Tong tien: " << order->getTotalAmount() << " VND\n";
    
    char confirm;
    std::cout << "Ban co chac chan muon huy? (y/n): ";
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        if (order->cancelOrder()) {
            // Hoàn lại tất cả tồn kho
            for (const auto& item : order->getItems()) {
                menuManager->updateProductStock(
                    item->getProduct()->getId(),
                    -item->getQuantity()
                );
            }
            std::cout << "\n✅ Da huy don hang thanh cong!\n";
            std::cout << "Da hoan lai tat ca so luong mon vao kho.\n";
        }
    } else {
        std::cout << "Da huy thao tac.\n";
    }
}

void PaymentManager::viewAllOrders() {
    if (orders.empty()) {
        std::cout << "\n📭 Chua co don hang nao!\n";
        return;
    }
    
    std::cout << "\n📋 DANH SACH TAT CA DON HANG\n";
    std::cout << std::string(90, '=') << std::endl;
    std::cout << std::left 
              << std::setw(15) << "Ma don"
              << std::setw(15) << "Nhan vien"
              << std::setw(20) << "Thoi gian"
              << std::setw(15) << "Trang thai"
              << std::setw(15) << "Tong tien"
              << std::setw(10) << "Thanh toan" << std::endl;
    std::cout << std::string(90, '=') << std::endl;
    
    for (const auto& order : orders) {
        char timeStr[100];
        time_t orderTime = order->getCreatedTime();
        tm timeInfo;
        localtime_r(&orderTime, &timeInfo);
        strftime(timeStr, sizeof(timeStr), "%H:%M %d/%m", &timeInfo);
        
        std::cout << std::left 
                  << std::setw(15) << order->getOrderId()
                  << std::setw(15) << order->getEmployeeId()
                  << std::setw(20) << timeStr
                  << std::setw(15) << order->getStatusString()
                  << std::setw(15) << std::fixed << std::setprecision(0) 
                  << order->getTotalAmount()
                  << std::setw(10) << (order->getIsPaid() ? "✅" : "❌") 
                  << std::endl;
    }
    
    std::cout << "Tong so: " << orders.size() << " don hang\n";
}

void PaymentManager::searchOrder() {
    std::string orderId;
    std::cout << "\n🔍 TIM KIEM DON HANG\n";
    std::cout << "Nhap ma don hang: ";
    std::cin >> orderId;
    
    auto order = findOrderById(orderId);
    if (order) {
        order->displayOrder();
        
        if (order->getIsPaid()) {
            std::cout << "\n💳 THONG TIN THANH TOAN:\n";
            std::cout << "Phuong thuc: " << order->getPaymentMethod() << std::endl;
            std::cout << "Da thanh toan: ✅\n";
        }
    } else {
        std::cout << "❌ Khong tim thay don hang voi ma: " << orderId << std::endl;
    }
}

void PaymentManager::viewOrderStatistics() {
    if (orders.empty()) {
        std::cout << "\n📊 Chua co du lieu thong ke!\n";
        return;
    }
    
    int completed = 0, cancelled = 0, pending = 0, preparing = 0, confirmed = 0;
    double totalRevenue = 0;
    
    for (const auto& order : orders) {
        switch (order->getStatus()) {
            case OrderStatus::COMPLETED: completed++; break;
            case OrderStatus::CANCELLED: cancelled++; break;
            case OrderStatus::PENDING: pending++; break;
            case OrderStatus::PREPARING: preparing++; break;
            case OrderStatus::CONFIRMED: confirmed++; break;
        }
        
        if (order->getIsPaid()) {
            totalRevenue += order->getTotalAmount();
        }
    }
    
    std::cout << "\n📊 THONG KE DON HANG\n";
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "Tong so don hang: " << orders.size() << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "📈 Da hoan thanh: " << completed << std::endl;
    std::cout << "✅ Da xac nhan: " << confirmed << std::endl;
    std::cout << "⚡ Dang pha che: " << preparing << std::endl;
    std::cout << "⏳ Cho xac nhan: " << pending << std::endl;
    std::cout << "❌ Da huy: " << cancelled << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "💰 Tong doanh thu: " << std::fixed << std::setprecision(0) 
              << totalRevenue << " VND\n";
    std::cout << "💳 Don da thanh toan: " << (completed + cancelled) << std::endl;
}

void PaymentManager::viewRevenueReport() {
    if (orders.empty()) {
        std::cout << "\n💰 Chua co du lieu doanh thu!\n";
        return;
    }
    
    time_t now = time(nullptr);
    tm todayTm;
    localtime_r(&now, &todayTm);
    
    double dailyRevenue = 0;
    double monthlyRevenue = 0;
    int dailyOrders = 0;
    int monthlyOrders = 0;
    
    for (const auto& order : orders) {
        if (!order->getIsPaid()) continue;
        
        time_t orderTimeT = order->getCreatedTime();
        tm orderTime;
        localtime_r(&orderTimeT, &orderTime);
        
        if (orderTime.tm_year == todayTm.tm_year &&
            orderTime.tm_mon == todayTm.tm_mon &&
            orderTime.tm_mday == todayTm.tm_mday) {
            dailyRevenue += order->getTotalAmount();
            dailyOrders++;
        }
        
        if (orderTime.tm_year == todayTm.tm_year &&
            orderTime.tm_mon == todayTm.tm_mon) {
            monthlyRevenue += order->getTotalAmount();
            monthlyOrders++;
        }
    }
    
    std::cout << "\n💰 BAO CAO DOANH THU\n";
    std::cout << std::string(50, '=') << std::endl;
    
    char dateStr[100];
    strftime(dateStr, sizeof(dateStr), "%A, %d/%m/%Y", &todayTm);
    
    std::cout << "Ngay: " << dateStr << std::endl;
    
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "📊 DOANH THU THEO NGAY:\n";
    std::cout << "So don hang: " << dailyOrders << std::endl;
    std::cout << "Tong doanh thu: " << std::fixed << std::setprecision(0) 
              << dailyRevenue << " VND\n";
    
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "📈 DOANH THU THEO THANG:\n";
    std::cout << "So don hang: " << monthlyOrders << std::endl;
    std::cout << "Tong doanh thu: " << std::fixed << std::setprecision(0) 
              << monthlyRevenue << " VND\n";
    
    int daysInMonth = todayTm.tm_mday;
    double avgPerDay = (daysInMonth > 0) ? monthlyRevenue / daysInMonth : 0;
    
    std::cout << "Trung binh/ngay: " << std::fixed << std::setprecision(0) 
              << avgPerDay << " VND\n";
    
    std::cout << std::string(50, '=') << std::endl;
}

void PaymentManager::runPaymentManager(const std::string& employeeId) {
    std::string currentOrderId = "";
    int choice;
    
    do {
        std::cout << "\n💳 HE THONG BAN HANG & THANH TOAN\n";
        std::cout << "Nhan vien: " << employeeId << std::endl;
        
        if (!currentOrderId.empty()) {
            auto order = findOrderById(currentOrderId);
            if (order) {
                std::cout << "📋 Don hien tai: " << currentOrderId;
                std::cout << " (" << order->getStatusString() << ")";
                std::cout << " - " << order->getItems().size() << " mon\n";
            }
        }
        
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "1. Tao don hang moi\n";
        std::cout << "2. Them mon vao don\n";
        std::cout << "3. Xem don hang hien tai\n";
        std::cout << "4. Xac nhan don hang\n";
        std::cout << "5. Danh dau dang pha che\n";
        std::cout << "6. Danh dau da hoan thanh\n";
        std::cout << "7. Thanh toan don hang\n";
        std::cout << "8. Huy mon trong don\n";
        std::cout << "9. Huy toan bo don\n";
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "a. Xem tat ca don hang\n";
        std::cout << "b. Tim kiem don hang\n";
        std::cout << "c. Thong ke don hang\n";
        std::cout << "d. Bao cao doanh thu\n";
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "0. Quay lai\n";
        std::cout << "Lua chon: ";
        
        char input;
        std::cin >> input;
        
        if (isdigit(input)) {
            choice = input - '0';
        } else {
            choice = input;
        }
        
        switch (choice) {
            case 1: {
                auto newOrder = createNewOrder(employeeId);
                currentOrderId = newOrder->getOrderId();
                break;
            }
            case 2: {
                if (currentOrderId.empty()) {
                    std::cout << "⚠️  Vui long tao don hang truoc!\n";
                } else {
                    addItemToOrder(currentOrderId);
                }
                break;
            }
            case 3: {
                if (currentOrderId.empty()) {
                    std::cout << "📭 Chua co don hang nao!\n";
                } else {
                    viewCurrentOrder(currentOrderId);
                }
                break;
            }
            case 4: {
                if (currentOrderId.empty()) {
                    std::cout << "⚠️  Vui long tao don hang truoc!\n";
                } else {
                    confirmOrder(currentOrderId);
                }
                break;
            }
            case 5: {
                if (currentOrderId.empty()) {
                    std::cout << "⚠️  Vui long tao don hang truoc!\n";
                } else {
                    markOrderAsPreparing(currentOrderId);
                }
                break;
            }
            case 6: {
                if (currentOrderId.empty()) {
                    std::cout << "⚠️  Vui long tao don hang truoc!\n";
                } else {
                    markOrderAsCompleted(currentOrderId);
                }
                break;
            }
            case 7: {
                if (currentOrderId.empty()) {
                    std::cout << "⚠️  Vui long tao don hang truoc!\n";
                } else {
                    processVirtualPayment(currentOrderId);
                }
                break;
            }
            case 8: {
                if (currentOrderId.empty()) {
                    std::cout << "⚠️  Vui long tao don hang truoc!\n";
                } else {
                    cancelOrderItem(currentOrderId);
                }
                break;
            }
            case 9: {
                if (currentOrderId.empty()) {
                    std::cout << "⚠️  Vui long tao don hang truoc!\n";
                } else {
                    cancelEntireOrder(currentOrderId);
                }
                break;
            }
            case 'a':
            case 'A':
                viewAllOrders();
                break;
            case 'b':
            case 'B':
                searchOrder();
                break;
            case 'c':
            case 'C':
                viewOrderStatistics();
                break;
            case 'd':
            case 'D':
                viewRevenueReport();
                break;
            case 0:
                std::cout << "Quay lai menu chinh...\n";
                break;
            default:
                std::cout << "❌ Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}