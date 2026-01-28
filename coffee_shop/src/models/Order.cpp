#include "models/Order.h"
#include "models/Product.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

Order::Order(const std::string& orderId, const std::string& employeeId)
    : orderId(orderId), employeeId(employeeId), status(OrderStatus::PENDING), 
      isPaid(false), paymentMethod("") {
    createdTime = time(nullptr);
}

std::string Order::getOrderId() const { return orderId; }
std::string Order::getEmployeeId() const { return employeeId; }
time_t Order::getCreatedTime() const { return createdTime; }
OrderStatus Order::getStatus() const { return status; }
std::string Order::getPaymentMethod() const { return paymentMethod; }
bool Order::getIsPaid() const { return isPaid; }

std::string Order::getStatusString() const {
    switch(status) {
        case OrderStatus::PENDING: return "Cho xac nhan";
        case OrderStatus::CONFIRMED: return "Da xac nhan";
        case OrderStatus::PREPARING: return "Dang pha che";
        case OrderStatus::COMPLETED: return "Hoan thanh";
        case OrderStatus::CANCELLED: return "Da huy";
        default: return "Unknown";
    }
}

std::vector<std::shared_ptr<OrderItem>> Order::getItems() const {
    return items;
}

double Order::getTotalAmount() const {
    double total = 0;
    for (const auto& item : items) {
        total += item->getSubtotal();
    }
    return total;
}

void Order::addItem(std::shared_ptr<Product> product, int quantity, const std::string& note) {
    // Kiểm tra xem sản phẩm đã có trong order chưa
    for (auto& item : items) {
        if (item->getProduct()->getId() == product->getId()) {
            item->setQuantity(item->getQuantity() + quantity);
            return;
        }
    }
    
    // Nếu chưa có, thêm mới
    items.push_back(std::make_shared<OrderItem>(product, quantity, note));
}

void Order::removeItem(const std::string& productId) {
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [&productId](const std::shared_ptr<OrderItem>& item) {
                return item->getProduct()->getId() == productId;
            }),
        items.end()
    );
}

void Order::updateItemQuantity(const std::string& productId, int newQuantity) {
    for (auto& item : items) {
        if (item->getProduct()->getId() == productId) {
            if (newQuantity <= 0) {
                removeItem(productId);
            } else {
                item->setQuantity(newQuantity);
            }
            return;
        }
    }
}

void Order::confirmOrder() {
    if (status == OrderStatus::PENDING) {
        status = OrderStatus::CONFIRMED;
    }
}

void Order::startPreparing() {
    if (status == OrderStatus::CONFIRMED) {
        status = OrderStatus::PREPARING;
    }
}

void Order::completeOrder() {
    if (status == OrderStatus::PREPARING) {
        status = OrderStatus::COMPLETED;
    }
}

bool Order::cancelOrder() {
    if (status == OrderStatus::PENDING || status == OrderStatus::CONFIRMED) {
        status = OrderStatus::CANCELLED;
        return true;
    }
    return false;
}

void Order::processPayment(const std::string& paymentMethod) {
    if (status == OrderStatus::COMPLETED) {
        this->paymentMethod = paymentMethod;
        this->isPaid = true;
    }
}

void Order::displayOrder() const {
    std::cout << "\n=== THONG TIN DON HANG ===\n";
    std::cout << "Ma don: " << orderId << std::endl;
    std::cout << "Nhan vien: " << employeeId << std::endl;
    
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S %d/%m/%Y", localtime(&createdTime));
    std::cout << "Thoi gian: " << timeStr << std::endl;
    std::cout << "Trang thai: " << getStatusString() << std::endl;
    
    if (!items.empty()) {
        std::cout << "\n" << std::string(80, '-') << std::endl;
        std::cout << std::left 
                  << std::setw(8) << "Ma mon"
                  << std::setw(25) << "Ten mon"
                  << std::setw(10) << "Gia"
                  << std::setw(8) << "SL"
                  << std::setw(12) << "Thanh tien"
                  << std::setw(15) << "Ghi chu" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        
        for (const auto& item : items) {
            item->display();
        }
        
        std::cout << std::string(80, '-') << std::endl;
        std::cout << std::right << std::setw(70) << "TONG CONG: " 
                  << std::fixed << std::setprecision(0) << getTotalAmount() << " VND\n";
    } else {
        std::cout << "Don hang trong!\n";
    }
}

void Order::displayBill() const {
    if (!isPaid) {
        std::cout << "Don hang chua thanh toan!\n";
        return;
    }
    
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "              HOA DON THANH TOAN" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S %d/%m/%Y", localtime(&createdTime));
    
    std::cout << "Ma don: " << orderId << std::endl;
    std::cout << "Thoi gian: " << timeStr << std::endl;
    std::cout << "Nhan vien: " << employeeId << std::endl;
    std::cout << "Phuong thuc: " << paymentMethod << std::endl;
    
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::left 
              << std::setw(25) << "Ten mon"
              << std::setw(8) << "SL"
              << std::setw(12) << "Thanh tien" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const auto& item : items) {
        std::cout << std::left 
                  << std::setw(25) << item->getProduct()->getName()
                  << std::setw(8) << item->getQuantity()
                  << std::setw(12) << item->getSubtotal() << std::endl;
    }
    
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::right << std::setw(40) << "TONG TIEN: " 
              << std::fixed << std::setprecision(0) << getTotalAmount() << " VND\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "         CAM ON QUY KHACH!\n";
}