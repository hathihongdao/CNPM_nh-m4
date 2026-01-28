#pragma once
#include <string>
#include <unordered_map>

struct MenuItem {
    std::string id;
    std::string name;
    long long price;     // VND
    bool available;      // còn bán / hết hàng
};

struct OrderItem {
    std::string itemId;
    std::string name;
    long long unitPrice; // VND
    int quantity;

    long long lineTotal() const {
        return unitPrice * 1LL * quantity;
    }
};

enum class OrderStatus {
    OPEN,
    PAID,
    CANCELED
};

struct Order {
    std::string id;
    OrderStatus status = OrderStatus::OPEN;

    // key = itemId
    std::unordered_map<std::string, OrderItem> items;

    long long total() const {
        long long sum = 0;
        for (const auto& kv : items) sum += kv.second.lineTotal();
        return sum;
    }
};
