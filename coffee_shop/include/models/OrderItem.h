#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <string>
#include <memory>

// Forward declaration
class Product;

class OrderItem {
private:
    std::shared_ptr<Product> product;
    int quantity;
    std::string note;
    
public:
    OrderItem(std::shared_ptr<Product> product, int quantity, const std::string& note = "");
    
    std::shared_ptr<Product> getProduct() const;
    int getQuantity() const;
    std::string getNote() const;
    double getSubtotal() const;
    
    void setQuantity(int quantity);
    void setNote(const std::string& note);
    
    void display() const;
};

#endif