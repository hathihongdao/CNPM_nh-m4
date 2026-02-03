#ifndef PAYMENT_MANAGER_H
#define PAYMENT_MANAGER_H

#include <vector>
#include <memory>
#include <map>
#include <ctime>
#include "models/Order.h"
#include "MenuManager.h"

class PaymentManager {
private:
    std::vector<std::shared_ptr<Order>> orders;
    std::map<std::string, std::shared_ptr<Order>> orderMap;
    std::shared_ptr<MenuManager> menuManager;
    int orderCounter;
    
    std::string generateOrderId();
    std::shared_ptr<Order> findOrderById(const std::string& orderId);
    
    // Phương thức thanh toán ảo
    bool simulateCashPayment(double amount);
    bool simulateBankTransfer(double amount, const std::string& bankCode);
    bool simulateQRPayment(double amount);
    
public:
    PaymentManager(std::shared_ptr<MenuManager> menuManager);
    
    // Order management
    std::shared_ptr<Order> createNewOrder(const std::string& employeeId);
    void addItemToOrder(const std::string& orderId);
    void viewCurrentOrder(const std::string& orderId);
    void confirmOrder(const std::string& orderId);
    void cancelOrderItem(const std::string& orderId);
    void cancelEntireOrder(const std::string& orderId);
    void markOrderAsPreparing(const std::string& orderId);
    void markOrderAsCompleted(const std::string& orderId);
    
    // Payment processing - Ảo
    void processVirtualPayment(const std::string& orderId);
    
    // Order viewing and statistics
    void viewAllOrders();
    void searchOrder();
    void viewOrderStatistics();
    void viewRevenueReport();
    
    // Main interface
    void runPaymentManager(const std::string& employeeId);
    
    // Getter for testing
    std::vector<std::shared_ptr<Order>> getAllOrders() const { return orders; }
};

#endif