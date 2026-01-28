#include "managers/MenuManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

MenuManager::MenuManager() {
    // Khởi tạo dữ liệu mẫu
    products.push_back(std::make_shared<Product>("CF001", "Ca phe den", "Ca phe", 25000, ProductStatus::AVAILABLE, 100));
    products.push_back(std::make_shared<Product>("CF002", "Ca phe sua", "Ca phe", 30000, ProductStatus::AVAILABLE, 80));
    products.push_back(std::make_shared<Product>("TS001", "Tra sua truyen thong", "Tra sua", 35000, ProductStatus::AVAILABLE, 120));
    products.push_back(std::make_shared<Product>("TS002", "Tra sua tran chau", "Tra sua", 40000, ProductStatus::OUT_OF_STOCK, 0));
    products.push_back(std::make_shared<Product>("AV001", "Banh mi", "An vat", 20000, ProductStatus::AVAILABLE, 50));
}

std::shared_ptr<Product> MenuManager::findProductById(const std::string& id) {
    for (auto& product : products) {
        if (product->getId() == id) {
            return product;
        }
    }
    return nullptr;
}

void MenuManager::displayProductHeader() {
    std::cout << "\n" << std::string(85, '=') << std::endl;
    std::cout << std::left 
              << std::setw(8) << "Ma mon" 
              << std::setw(25) << "Ten mon"
              << std::setw(15) << "Danh muc"
              << std::setw(12) << "Gia (VND)"
              << std::setw(15) << "Trang thai"
              << std::setw(10) << "Ton kho" << std::endl;
    std::cout << std::string(85, '=') << std::endl;
}

void MenuManager::addProduct() {
    std::cout << "\n=== THEM MON MOI VAO MENU ===\n";
    
    std::string id, name, category;
    double price;
    int stock;
    
    std::cout << "Nhap ma mon (VD: CF001): ";
    std::cin >> id;
    
    if (findProductById(id) != nullptr) {
        std::cout << "Loi: Ma mon da ton tai!\n";
        return;
    }
    
    std::cout << "Nhap ten mon: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::cout << "Nhap danh muc (ca phe/tra sua/an vat): ";
    std::cin >> category;
    
    std::cout << "Nhap gia: ";
    std::cin >> price;
    
    std::cout << "Nhap so luong ton kho: ";
    std::cin >> stock;
    
    ProductStatus status = (stock > 0) ? ProductStatus::AVAILABLE : ProductStatus::OUT_OF_STOCK;
    
    products.push_back(std::make_shared<Product>(id, name, category, price, status, stock));
    std::cout << "Da them mon thanh cong!\n";
}

void MenuManager::updateProduct() {
    std::cout << "\n=== CAP NHAT THONG TIN MON ===\n";
    
    std::string id;
    std::cout << "Nhap ma mon can cap nhat: ";
    std::cin >> id;
    
    auto product = findProductById(id);
    if (!product) {
        std::cout << "Khong tim thay mon voi ma: " << id << std::endl;
        return;
    }
    
    std::cout << "\nThong tin hien tai:\n";
    displayProductHeader();
    product->display();
    
    int choice;
    do {
        std::cout << "\nChon thong tin can cap nhat:\n";
        std::cout << "1. Ten mon\n";
        std::cout << "2. Danh muc\n";
        std::cout << "3. Gia\n";
        std::cout << "4. Trang thai\n";
        std::cout << "5. So luong ton kho\n";
        std::cout << "0. Quay lai\n";
        std::cout << "Lua chon: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                std::string newName;
                std::cout << "Nhap ten moi: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                product->setName(newName);
                std::cout << "Da cap nhat ten!\n";
                break;
            }
            case 2: {
                std::string newCategory;
                std::cout << "Nhap danh muc moi: ";
                std::cin >> newCategory;
                product->setCategory(newCategory);
                std::cout << "Da cap nhat danh muc!\n";
                break;
            }
            case 3: {
                double newPrice;
                std::cout << "Nhap gia moi: ";
                std::cin >> newPrice;
                product->setPrice(newPrice);
                std::cout << "Da cap nhat gia!\n";
                break;
            }
            case 4: {
                int statusChoice;
                std::cout << "Chon trang thai:\n";
                std::cout << "1. Con ban\n";
                std::cout << "2. Tam het\n";
                std::cout << "3. Ngung ban\n";
                std::cout << "Lua chon: ";
                std::cin >> statusChoice;
                
                switch(statusChoice) {
                    case 1: product->setStatus(ProductStatus::AVAILABLE); break;
                    case 2: product->setStatus(ProductStatus::OUT_OF_STOCK); break;
                    case 3: product->setStatus(ProductStatus::DISCONTINUED); break;
                    default: std::cout << "Lua chon khong hop le!\n";
                }
                std::cout << "Da cap nhat trang thai!\n";
                break;
            }
            case 5: {
                int newStock;
                std::cout << "Nhap so luong ton kho moi: ";
                std::cin >> newStock;
                product->setStock(newStock);
                
                if (newStock == 0 && product->getStatus() == ProductStatus::AVAILABLE) {
                    product->setStatus(ProductStatus::OUT_OF_STOCK);
                }
                std::cout << "Da cap nhat so luong ton kho!\n";
                break;
            }
        }
    } while (choice != 0);
}

void MenuManager::deleteProduct() {
    std::cout << "\n=== XOA MON KHOI MENU ===\n";
    
    std::string id;
    std::cout << "Nhap ma mon can xoa: ";
    std::cin >> id;
    
    auto product = findProductById(id);
    if (product) {
        product->setStatus(ProductStatus::DISCONTINUED);
        std::cout << "Da danh dau mon '" << product->getName() << "' la NGUNG BAN.\n";
    } else {
        std::cout << "Khong tim thay mon voi ma: " << id << std::endl;
    }
}

void MenuManager::viewProductsByCategory(const std::string& category) {
    std::cout << "\n=== DANH SACH MON ===\n";
    
    if (category.empty()) {
        std::cout << "Tat ca cac danh muc:\n";
    } else {
        std::cout << "Danh muc: " << category << std::endl;
    }
    
    displayProductHeader();
    
    int count = 0;
    for (const auto& product : products) {
        if (category.empty() || product->getCategory() == category) {
            product->display();
            count++;
        }
    }
    
    if (count == 0) {
        std::cout << "Khong co mon nao trong danh muc nay.\n";
    } else {
        std::cout << "Tong so: " << count << " mon\n";
    }
}

void MenuManager::searchProduct() {
    std::cout << "\n=== TIM KIEM MON ===\n";
    
    int searchType;
    std::cout << "Tim kiem theo:\n";
    std::cout << "1. Ma mon\n";
    std::cout << "2. Ten mon\n";
    std::cout << "Lua chon: ";
    std::cin >> searchType;
    
    std::string keyword;
    std::cout << "Nhap tu khoa: ";
    std::cin.ignore();
    std::getline(std::cin, keyword);
    
    displayProductHeader();
    
    int count = 0;
    for (const auto& product : products) {
        bool match = false;
        
        if (searchType == 1 && product->getId().find(keyword) != std::string::npos) {
            match = true;
        } else if (searchType == 2 && product->getName().find(keyword) != std::string::npos) {
            match = true;
        }
        
        if (match) {
            product->display();
            count++;
        }
    }
    
    if (count == 0) {
        std::cout << "Khong tim thay mon phu hop.\n";
    }
}

std::shared_ptr<Product> MenuManager::getProductById(const std::string& id) {
    return findProductById(id);
}

std::vector<std::shared_ptr<Product>> MenuManager::getAvailableProducts() {
    std::vector<std::shared_ptr<Product>> availableProducts;
    for (const auto& product : products) {
        if (product->isAvailable()) {
            availableProducts.push_back(product);
        }
    }
    return availableProducts;
}

void MenuManager::updateProductStock(const std::string& productId, int quantity) {
    auto product = findProductById(productId);
    if (product) {
        int newStock = product->getStock() - quantity;
        if (newStock < 0) newStock = 0;
        
        product->setStock(newStock);
        
        if (newStock == 0) {
            product->setStatus(ProductStatus::OUT_OF_STOCK);
        }
    }
}

void MenuManager::runMenuManager() {
    int choice;
    do {
        std::cout << "\n=== QUAN LY MENU ===\n";
        std::cout << "1. Xem toan bo menu\n";
        std::cout << "2. Xem theo danh muc\n";
        std::cout << "3. Tim kiem mon\n";
        std::cout << "4. Them mon moi\n";
        std::cout << "5. Cap nhat mon\n";
        std::cout << "6. Xoa mon\n";
        std::cout << "0. Quay lai menu chinh\n";
        std::cout << "Lua chon: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1: viewProductsByCategory(); break;
            case 2: {
                std::string category;
                std::cout << "Nhap danh muc (ca phe/tra sua/an vat): ";
                std::cin >> category;
                viewProductsByCategory(category);
                break;
            }
            case 3: searchProduct(); break;
            case 4: addProduct(); break;
            case 5: updateProduct(); break;
            case 6: deleteProduct(); break;
        }
    } while (choice != 0);
}