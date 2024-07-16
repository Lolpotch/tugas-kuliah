#include <iostream>
#include <string>
using namespace std;

struct Item {
    int id;
    string name;
    int quantity;
    int price;
    Item* next;
};

class Inventory {
private:
    Item* head;
    int nextId;

public:
    Inventory() {
        head = nullptr;
        nextId = 1;
        hardcodeItems();
    }

    ~Inventory() {
        while (head != nullptr) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
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
};

void AdminMenu(Inventory& inventory) {
    int choice;
    string name;
    int quantity;
    int price;
    int id;

    while (true) {
        cout << "\nChoose an option:\n1. Add Item\n2. Remove Item\n3. Display Inventory\n4. Exit\n> ";
        cin.clear();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item quantity: ";
                cin >> quantity;
                cout << "Enter item price: ";
                cin >> price;
                inventory.addItem(name, quantity, price);
                break;
            case 2:
                cout << "Enter item ID to remove: ";
                cin >> id;
                inventory.removeItem(id);
                break;
            case 3:
                inventory.displayInventory();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}


int main() {
    const int MAX_USERS = 100;
    string users[MAX_USERS][2] = { {"admin", "password"}, {"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"} };
    int userCount = 4; // to keep track of the number of users
    string choice;
    string username, password;
    Inventory inventory;

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

            // Check if username already exists
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

            // Check the username and password in the array
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
