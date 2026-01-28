#pragma once
#include "repos.h"
#include "errors.h"

class OrderService {
private:
    MenuRepository& menuRepo;
    OrderRepository& orderRepo;

    static void ensureOrderOpen(const Order& order) {
        if (order.status != OrderStatus::OPEN) {
            throw AppError("Đơn không ở trạng thái OPEN nên không thể chỉnh sửa.");
        }
    }

public:
    OrderService(MenuRepository& m, OrderRepository& o) : menuRepo(m), orderRepo(o) {}

    // ===== ĐẶT MÓN =====
    // - kiểm tra số lượng
    // - kiểm tra món tồn tại + còn bán
    // - thêm vào đơn (nếu đã có thì cộng dồn quantity)
    Order& addItem(const std::string& orderId, const std::string& itemId, int quantity) {
        if (quantity <= 0) throw AppError("Số lượng phải > 0.");

        Order& order = orderRepo.createIfAbsent(orderId);
        ensureOrderOpen(order);

        auto optItem = menuRepo.findById(itemId);
        if (!optItem) throw AppError("Không tìm thấy món: " + itemId);

        MenuItem item = *optItem;
        if (!item.available) throw AppError("Món đang hết hàng / ngừng bán: " + itemId);

        auto it = order.items.find(itemId);
        if (it == order.items.end()) {
            order.items[itemId] = OrderItem{item.id, item.name, item.price, quantity};
        } else {
            it->second.quantity += quantity;
        }

        return order;
    }

    // ===== HUỶ MÓN =====
    // - kiểm tra đơn tồn tại
    // - kiểm tra món có trong đơn
    // - xóa món khỏi đơn
    Order& removeItem(const std::string& orderId, const std::string& itemId) {
        auto optOrder = orderRepo.findById(orderId);
        if (!optOrder) throw AppError("Không tìm thấy đơn: " + orderId);

        Order& order = optOrder->get();
        ensureOrderOpen(order);

        auto it = order.items.find(itemId);
        if (it == order.items.end()) {
            throw AppError("Món không có trong đơn nên không thể huỷ: " + itemId);
        }

        order.items.erase(it);
        return order;
    }
};
