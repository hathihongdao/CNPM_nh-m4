#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <vector>
#include <memory>
#include "models/Product.h"

class MenuManager {
private:
    std::vector<std::shared_ptr<Product>> products;
    
    std::shared_ptr<Product> findProductById(const std::string& id);
    void displayProductHeader();
    
public:
    MenuManager();
    
    // Quản lý menu
    void addProduct();
    void updateProduct();
    void deleteProduct();
    void viewProductsByCategory(const std::string& category = "");
    void searchProduct();
    
    // Hỗ trợ cho các module khác
    std::shared_ptr<Product> getProductById(const std::string& id);
    std::vector<std::shared_ptr<Product>> getAvailableProducts();
    void updateProductStock(const std::string& productId, int quantity);
    
    void runMenuManager();
};

#endif