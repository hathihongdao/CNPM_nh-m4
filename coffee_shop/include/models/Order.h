#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include "OrderItem.h"

// Forward declaration
class Product;

enum class OrderStatus {
    PENDING,
    CONFIRMED,
    PREPARING,
    COMPLETED,
    CANCELLED
};

class Order {
private:
    std::string orderId;
    std::string employeeId;
    time_t createdTime;
    OrderStatus status;
    std::vector<std::shared_ptr<OrderItem>> items;
    std::string paymentMethod;
    bool isPaid;
    
public:
    Order(const std::string& orderId, const std::string& employeeId);
    
    // Getters
    std::string getOrderId() const;
    std::string getEmployeeId() const;
    time_t getCreatedTime() const;
    OrderStatus getStatus() const;
    std::string getStatusString() const;
    std::vector<std::shared_ptr<OrderItem>> getItems() const;
    std::string getPaymentMethod() const;
    bool getIsPaid() const;
    double getTotalAmount() const;
    
    // Order management
    void addItem(std::shared_ptr<Product> product, int quantity, const std::string& note = "");
    void removeItem(const std::string& productId);
    void updateItemQuantity(const std::string& productId, int newQuantity);
    
    // Status management
    void confirmOrder();
    void startPreparing();
    void completeOrder();
    bool cancelOrder();
    
    // Payment
    void processPayment(const std::string& paymentMethod);
    
    void displayOrder() const;
    void displayBill() const;
};

#endif