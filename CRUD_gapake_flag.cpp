#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>

using namespace std;

struct Item {
    int id;
    string name;
    int quantity;
    int price;
    Item* next;
};

struct CartItem {
    int id;
    string name;
    int quantity;
    int price;
};

class Inventory {
private:
    Item* head;
    stack<CartItem> cart;
    int nextId;

public:
    Inventory() {
        head = nullptr;
        nextId = 1;
        hardcodeItems();
    }

    void hardcodeItems() {
        addItem("Laptop", 10, 1500000);
        addItem("Keyboard", 50, 200000);
        addItem("Mouse", 100, 75000);
        addItem("Monitor", 25, 250000);
        addItem("Printer", 15, 120000);
    }

    void addItem(string name, int quantity, int price) {
        Item* newItem = new Item;
        newItem->id = nextId++;
        newItem->name = name;
        newItem->quantity = quantity;
        newItem->price = price;
        newItem->next = head;
        head = newItem;
        cout << "Item added successfully." << endl;
    }

    void removeItem(int id) {
        Item* current = head;
        Item* previous = nullptr;

        while (current != nullptr && current->id != id) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Item not found." << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        cout << "Item removed successfully." << endl;
    }

    void displayInventory() const {
        Item* current = head;

        if (current == nullptr) {
            cout << "Inventory is empty." << endl;
            return;
        }

        cout << "Inventory List:" << endl;
        while (current != nullptr) {
            cout << "ID: " << current->id << ", Name: " << current->name
                 << ", Quantity: " << current->quantity << ", Price: Rp " << current->price << endl;
            current = current->next;
        }
    }

    void addItemToCart(int id, int quantity) {
        Item* current = head;

        while (current != nullptr && current->id != id) {
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Item not found." << endl;
            return;
        }
        if (current->quantity < quantity) {
            cout << "Not enough stock available." << endl;
            return;
        }

        current->quantity -= quantity;
        CartItem newCartItem;
        newCartItem.id = current->id;
        newCartItem.name = current->name;
        newCartItem.quantity = quantity;
        newCartItem.price = current->price;
        cart.push(newCartItem);
        cout << "Item added to cart successfully." << endl;
    }

    void removeItemFromCart() {
        if (cart.empty()) {
            cout << "Cart is empty." << endl;
            return;
        }

        CartItem removedItem = cart.top();
        cart.pop();
        cout << "Removed " << removedItem.name << " from the cart." << endl;

        Item* current = head;
        while (current != nullptr && current->id != removedItem.id) {
            current = current->next;
        }
        if (current != nullptr) {
            current->quantity += removedItem.quantity;
        }
    }

    void displayCart() const {
        if (cart.empty()) {
            cout << "Cart is empty." << endl;
            return;
        }

        stack<CartItem> tempCart = cart;
        int totalHarga = 0;

        cout << "Items in your cart:" << endl;
        while (!tempCart.empty()) {
            CartItem current = tempCart.top();
            tempCart.pop();
            int subtotal = current.quantity * current.price;
            totalHarga += subtotal;
            cout << "ID: " << current.id 
                 << ", Name: " << current.name
                 << ", Quantity: " << current.quantity
                 << ", Price: Rp " << current.price 
                 << ", Subtotal: Rp " << subtotal << endl;
        }
        cout << "Total Harga: Rp " << totalHarga << "\n\n";
    }

    void checkout() {
        if (cart.empty()) {
            cout << "Cart is empty. Cannot checkout." << endl;
            return;
        }

        int totalHarga = 0;
        stack<CartItem> tempCart = cart;

        while (!tempCart.empty()) {
            CartItem current = tempCart.top();
            tempCart.pop();
            totalHarga += current.quantity * current.price;
        }

        cout << "Total payment: Rp " << totalHarga << ". Checking out..." << endl;

        int paymentMethod;
        cout << "Choose a payment method:\n1. Cash\n2. Credit Card\n3. Bank Transfer\n> ";
        cin >> paymentMethod;

        switch (paymentMethod) {
            case 1:
                cout << "You have selected Cash. Please prepare the exact amount." << endl;
                break;
            case 2:
                cout << "You have selected Credit Card. Please enter your card details." << endl;
                break;
            case 3:
                cout << "You have selected Bank Transfer. Please transfer the amount to the provided bank account." << endl;
                break;
            default:
                cout << "Invalid payment method. Defaulting to Cash." << endl;
                break;
        }
        while (!cart.empty()) {
            cart.pop();
        }

        cout << "Checkout successful. Thank you for your purchase!" << endl;
    }

    void changeItem(int id, string newName, int newQuantity, int newPrice) {
    Item* current = head;
    while (current != nullptr && current->id != id) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Item not found." << endl;
        return;
    }
    current->name = newName;
    current->quantity = newQuantity;
    current->price = newPrice;
    cout << "Item details updated successfully." << endl;
}

    void clearInventory() {
        while (head != nullptr) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
        cout << "Inventory cleared." << endl;
    }
};

void AdminMenu(Inventory& inventory) {
    int choice;
    string name;
    int quantity;
    int price;
    int id;

    while (true) {
        cout << "\nChoose an option:\n1. Add Item\n2. Remove Item\n3. Display Inventory\n4. Change Item\n5. Clear Inventory\n6. Exit\n> ";
        cin.clear();
        cin >> choice;

        if (choice == 1) {
            cout << "Enter item name: ";
            cin >> name;
            cout << "Enter item quantity: ";
            cin >> quantity;
            cout << "Enter item price: ";
            cin >> price;
            inventory.addItem(name, quantity, price);
        } else if (choice == 2) {
            cout << "Enter item ID to remove: ";
            cin >> id;
            inventory.removeItem(id);
        } else if (choice == 3) {
            inventory.displayInventory();
        } else if (choice == 4) {
            cout << "Enter item ID to change: ";
            cin >> id;
            cout << "Enter new item name: ";
            cin >> name;
            cout << "Enter new item quantity: ";
            cin >> quantity;
            cout << "Enter new item price: ";
            cin >> price;
            inventory.changeItem(id, name, quantity, price);
        } else if (choice == 5) {
            inventory.clearInventory();
        } else if (choice == 6) {
            return;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void UserMenu(Inventory& inventory) {
    int choice;
    int id;
    int quantity;

    while (true) {
        inventory.displayInventory();
        cout << "\n\nChoose an option:\n1. Add Item to Cart\n2. Remove Last Item from Cart\n3. Display Cart\n4. Checkout\n5. Exit\n> ";
        cin >> choice;

        if (choice == 1) {
            inventory.displayInventory();
            cout << "Enter the ID of the item you want to add to the cart: ";
            cin >> id;
            cout << "Enter the quantity of the item you want to buy: ";
            cin >> quantity;
            inventory.addItemToCart(id, quantity);
        } else if (choice == 2) {
            inventory.removeItemFromCart();
        } else if (choice == 3) {
            inventory.displayCart();
        } else if (choice == 4) {
            inventory.checkout();
        } else if (choice == 5) {
            cout << "Exiting Program" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    const int MAX_USERS = 100;
    string users[MAX_USERS][2] = { {"admin", "password"}, {"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"} };
    int userCount = 4; 
    string choice;
    string username, password;
    Inventory inventory;

    system("cls");
    cout << "Welcome to OL Shop!" << endl;

    while (true) {
        cout << "\nChoose an option:\n1. Signup\n2. Login\n3. Exit\n> ";
        cin.clear();
        cin >> choice;

        if (choice == "1") {
            if (userCount >= MAX_USERS) {
                cout << "User limit reached. Cannot sign up more users.\n";
                continue;
            }

            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (username == "admin") {
                cout << "You are just a buyer here.\n";
                continue;
            }

            bool userExists = false;
            for (int i = 0; i < userCount; ++i) {
                if (users[i][0] == username) {
                    userExists = true;
                    break;
                }
            }

            if (!userExists) {
                users[userCount][0] = username;
                users[userCount][1] = password;
                userCount++;
                cout << "Signup successful!\n";
            } else {
                cout << "Username already exists. Please try a different username.\n";
            }
        } else if (choice == "2") {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            bool loginSuccessful = false;
            for (int i = 0; i < userCount; ++i) {
                if (users[i][0] == username && users[i][1] == password) {
                    loginSuccessful = true;
                    break;
                }
            }

            if (loginSuccessful && username == "admin") {
                cout << "Welcome admin!\n";
                AdminMenu(inventory);
            } else if (loginSuccessful) {
                cout << "Login successful!\n";
                UserMenu(inventory);
            } else {
                cout << "Invalid username or password. Please try again.\n";
            }
        } else if (choice == "3") {
            break;
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
