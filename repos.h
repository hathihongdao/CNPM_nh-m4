#pragma once
#include "models.h"
#include <optional>
#include <unordered_map>

class MenuRepository {
private:
    std::unordered_map<std::string, MenuItem> data;

public:
    MenuRepository() {
        data["CF01"] = {"CF01", "Cà phê sữa", 25000, true};
        data["TS01"] = {"TS01", "Trà sữa", 32000, true};
        data["CK01"] = {"CK01", "Bánh ngọt", 18000, false}; // hết hàng
    }

    std::optional<MenuItem> findById(const std::string& id) const {
        auto it = data.find(id);
        if (it == data.end()) return std::nullopt;
        return it->second;
    }
};

class OrderRepository {
private:
    std::unordered_map<std::string, Order> data;

public:
    // tạo đơn nếu chưa có
    Order& createIfAbsent(const std::string& orderId) {
        auto it = data.find(orderId);
        if (it == data.end()) {
            data[orderId] = Order{orderId};
        }
        return data[orderId];
    }

    std::optional<std::reference_wrapper<Order>> findById(const std::string& orderId) {
        auto it = data.find(orderId);
        if (it == data.end()) return std::nullopt;
        return it->second;
    }
};
