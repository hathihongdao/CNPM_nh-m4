#include <iostream>
#include <iomanip>
#include "order_service.h"

static void printOrder(const Order& o) {
    std::cout << "\n=== ORDER: " << o.id << " ===\n";
    if (o.items.empty()) {
        std::cout << "(Đơn trống)\n";
        return;
    }

    std::cout << std::left
              << std::setw(8)  << "ID"
              << std::setw(18) << "Tên"
              << std::setw(8)  << "SL"
              << std::setw(12) << "Đơn giá"
              << std::setw(12) << "Thành tiền"
              << "\n";

    for (const auto& kv : o.items) {
        const auto& it = kv.second;
        std::cout << std::left
                  << std::setw(8)  << it.itemId
                  << std::setw(18) << it.name
                  << std::setw(8)  << it.quantity
                  << std::setw(12) << it.unitPrice
                  << std::setw(12) << it.lineTotal()
                  << "\n";
    }
    std::cout << "TOTAL: " << o.total() << " VND\n";
}

int main() {
    MenuRepository menuRepo;
    OrderRepository orderRepo;
    OrderService service(menuRepo, orderRepo);

    std::string orderId = "ORD001";

    try {
        // Đặt món
        service.addItem(orderId, "CF01", 2);
        service.addItem(orderId, "TS01", 1);
        printOrder(orderRepo.findById(orderId)->get());

        // Huỷ món
        service.removeItem(orderId, "TS01");
        printOrder(orderRepo.findById(orderId)->get());

        // Test lỗi: món hết hàng
        service.addItem(orderId, "CK01", 1);
    }
    catch (const AppError& e) {
        std::cout << "\n[LỖI] " << e.what() << "\n";
    }
}
