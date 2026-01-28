#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

enum class ProductStatus {
    AVAILABLE,
    OUT_OF_STOCK,
    DISCONTINUED
};

class Product {
private:
    std::string id;
    std::string name;
    std::string category;
    double price;
    ProductStatus status;
    int stock;

public:
    Product(std::string id, std::string name, std::string category, 
            double price, ProductStatus status = ProductStatus::AVAILABLE, 
            int stock = 0);
    
    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    ProductStatus getStatus() const;
    std::string getStatusString() const;
    int getStock() const;
    bool isAvailable() const;
    
    // Setters
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setPrice(double price);
    void setStatus(ProductStatus status);
    void setStock(int stock);
    
    void display() const;
};

#endif