#include <iostream>
#include <string>

using namespace std;

struct Node {
    string username;
    string hashedPassword;
    Node* next;
    Node* prev;
};

class UsersLinkedList {
private:
    Node* head;
    Node* tail;

    string hashPassword(const string& password) {
        // Simple hash function for demonstration (e.g., sum of ASCII values)
        unsigned long hash = 0;
        for (char ch : password) {
            hash = hash * 31 + ch; // 31 is a small prime number commonly used in hash functions
        }
        return to_string(hash);
    }

public:
    UsersLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void addNode(const string& username, const string& password) {
        string hashedPassword = hashPassword(password);

        Node* newNode = new Node();
        newNode->username = username;
        newNode->hashedPassword = hashedPassword;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }

    bool validateLogin(const string& username, const string& password) {
        string hashedPassword = hashPassword(password);

        Node* current = head;
        while (current) {
            if (current->username == username && current->hashedPassword == hashedPassword) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

int main() {
    UsersLinkedList userList;
    userList.addNode("user123", "pass123");
    userList.addNode("user456", "pass456");
    userList.addNode("admin", "admin123"); 

    string inputUsername, inputPassword;

    cout << "Enter username: ";
    cin >> inputUsername;

    cout << "Enter password: ";
    cin >> inputPassword;

    if (userList.validateLogin(inputUsername, inputPassword)) {
        cout << "Login successful!" << endl;
        if (inputUsername == "admin") {
            cout << "Welcome, Admin!" << endl;
        }
    } else {
        cout << "Invalid username or password!" << endl;
    }

    return 0;
}
