#include <iostream>
#include <string>
#include <unordered_map>

class Product {
public:
    Product() : name(""), quantity(0) {}
    Product(const std::string& name, int quantity) : name(name), quantity(quantity) {}

    void decreaseQuantity(int amount) {
        quantity -= amount;
        if (quantity <= 0) {
            quantity = 0;
        }
    }

    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }

private:
    std::string name;
    int quantity;
};

class Storage {
public:
    void addProduct(const Product& product) {
        products[product.getName()] = product;
    }

    void removeProductIfEmpty() {
        for (auto it = products.begin(); it != products.end();) {
            if (it->second.getQuantity() == 0) {
                it = products.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    const std::unordered_map<std::string, Product>& getAllProducts() const {
        return products;
    }

    void decreaseQuantity(std::string& productToBuy, int quantityToBuy) {
        products.at(productToBuy).decreaseQuantity(quantityToBuy);
    }

private:
    std::unordered_map<std::string, Product> products;
};

class Store : public Storage {};

int main() {
    Storage storage;
    Store store;

    while (true) {
        std::cout << "Choose your role: (1) Warehouse Customer, (2) Store Customer, (3) Supplier, (4) Exit: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) { // Warehouse Customer
            std::cout << "Available products in the warehouse:" << std::endl;
            for (const auto& pair : storage.getAllProducts()) {
                std::cout << pair.first << " - " << pair.second.getQuantity() << " available" << std::endl;
            }

            std::string productToBuy;
            int quantityToBuy;
            std::cout << "Enter the product you want to buy from the warehouse: ";
            std::cin >> productToBuy;
            std::cout << "Enter the quantity you want to buy: ";
            std::cin >> quantityToBuy;

            if (storage.getAllProducts().count(productToBuy) == 0) {
                std::cout << "Product not available in the warehouse." << std::endl;
            }
            else if (quantityToBuy > storage.getAllProducts().at(productToBuy).getQuantity()) {
                std::cout << "Not enough quantity available in the warehouse." << std::endl;
            }
            else {
                storage.decreaseQuantity(productToBuy, quantityToBuy);
                std::cout << "Purchase successful!" << std::endl;
            }
        }
        if (choice == 2) { // Store Customer
            std::cout << "Available products in the store:" << std::endl;
            for (const auto& pair : store.getAllProducts()) {
                std::cout << pair.first << " - " << pair.second.getQuantity() << " available" << std::endl;
            }

            std::string productToBuy;
            int quantityToBuy;
            std::cout << "Enter the product you want to buy from the store: ";
            std::cin >> productToBuy;
            std::cout << "Enter the quantity you want to buy: ";
            std::cin >> quantityToBuy;

            if (store.getAllProducts().count(productToBuy) == 0) {
                std::cout << "Product not available in the store." << std::endl;
            }
            else if (quantityToBuy > store.getAllProducts().at(productToBuy).getQuantity()) {
                std::cout << "Not enough quantity available in the store." << std::endl;
            }
            else {
                store.decreaseQuantity(productToBuy, quantityToBuy);
                std::cout << "Purchase successful!" << std::endl;
            }
        }
        else if (choice == 3) {
            std::string productName;
            int quantity;

            std::cout << "Enter the product name you want to supply: ";
            std::cin >> productName;

            std::cout << "Enter the quantity you want to supply: ";
            std::cin >> quantity;

            Product newProduct(productName, quantity);

            if (storage.getAllProducts().size() + store.getAllProducts().size() + 1 > 10) {
                std::cout << "Storage is full, cannot add more products!" << std::endl;
            }
            else {
                int supplyChoice;
                std::cout << "Where do you want to supply the product? (1) Warehouse, (2) Store: ";
                std::cin >> supplyChoice;

                if (supplyChoice == 1) {
                    storage.addProduct(newProduct);
                }
                else if (supplyChoice == 2) {
                    store.addProduct(newProduct);
                }
                else {
                    std::cout << "Invalid choice!" << std::endl;
                }
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }

    return 0;
}
