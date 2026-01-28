#include "models/Product.h"
#include <iostream>
#include <iomanip>

Product::Product(std::string id, std::string name, std::string category, 
                 double price, ProductStatus status, int stock)
    : id(id), name(name), category(category), price(price), 
      status(status), stock(stock) {}

std::string Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
ProductStatus Product::getStatus() const { return status; }
int Product::getStock() const { return stock; }

std::string Product::getStatusString() const {
    switch(status) {
        case ProductStatus::AVAILABLE: return "Con ban";
        case ProductStatus::OUT_OF_STOCK: return "Tam het";
        case ProductStatus::DISCONTINUED: return "Ngung ban";
        default: return "Unknown";
    }
}

bool Product::isAvailable() const {
    return status == ProductStatus::AVAILABLE && stock > 0;
}

void Product::setName(const std::string& name) { this->name = name; }
void Product::setCategory(const std::string& category) { this->category = category; }
void Product::setPrice(double price) { this->price = price; }
void Product::setStatus(ProductStatus status) { this->status = status; }
void Product::setStock(int stock) { this->stock = stock; }

void Product::display() const {
    std::cout << std::left 
              << std::setw(8) << id 
              << std::setw(25) << name
              << std::setw(15) << category
              << std::setw(12) << price
              << std::setw(15) << getStatusString()
              << std::setw(10) << stock << std::endl;
}