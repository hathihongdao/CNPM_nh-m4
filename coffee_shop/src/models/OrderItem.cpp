#include "models/OrderItem.h"
#include "models/Product.h"
#include <iostream>
#include <iomanip>

OrderItem::OrderItem(std::shared_ptr<Product> product, int quantity, const std::string& note)
    : product(product), quantity(quantity), note(note) {}

std::shared_ptr<Product> OrderItem::getProduct() const { return product; }
int OrderItem::getQuantity() const { return quantity; }
std::string OrderItem::getNote() const { return note; }
double OrderItem::getSubtotal() const { return product->getPrice() * quantity; }

void OrderItem::setQuantity(int quantity) { this->quantity = quantity; }
void OrderItem::setNote(const std::string& note) { this->note = note; }

void OrderItem::display() const {
    std::cout << std::left 
              << std::setw(8) << product->getId()
              << std::setw(25) << product->getName()
              << std::setw(10) << product->getPrice()
              << std::setw(8) << quantity
              << std::setw(12) << getSubtotal()
              << std::setw(15) << note << std::endl;
}