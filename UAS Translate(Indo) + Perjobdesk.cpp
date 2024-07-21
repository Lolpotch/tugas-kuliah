#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <random> // Untuk menghasilkan angka random

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
    //Admin Hardcode Items(A1) Azkal Salman
    void hardcodeItems() {
        addItem("Laptop", 10, 1500000);
        addItem("Keyboard", 50, 200000);
        addItem("Mouse", 100, 75000);
        addItem("Monitor", 25, 250000);
        addItem("Printer", 15, 120000);
    }

    //Admin Add Item Azkal Salman
    void addItem(string name, int quantity, int price) {
        Item* newItem = new Item;
        newItem->id = nextId++;
        newItem->name = name;
        newItem->quantity = quantity;
        newItem->price = price;
        newItem->next = head;
        head = newItem;
        cout << "Item berhasil ditambahkan" << endl;
    }
    //Admin Remove Item Azkal Salman
    void removeItem(int id) {
        Item* current = head;
        Item* previous = nullptr;

        while (current != nullptr && current->id != id) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Item tidak ditemukan" << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
        cout << "Item berhasil dihapus" << endl;
    }

    //Admin Display Inventory Azkal Salman
    void displayInventory() const {
        Item* current = head;

        if (current == nullptr) {
            cout << "Barang kosong" << endl;
            return;
        }

        cout << "Daftar Barang:" << endl;
        while (current != nullptr) {
            cout << "ID: " << current->id << ", Nama: " << current->name
                 << ", Stok tersedia: " << current->quantity << ", Harga: Rp " << current->price << endl;
            current = current->next;
        }
    }
    //Admin Change Item Azkal Salman
    void changeItem(int id, string newName, int newQuantity, int newPrice) {
        Item* current = head;

        while (current != nullptr && current->id != id) {
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Item tidak ditemukan." << endl;
            return;
        }
        current->name = newName;
        current->quantity = newQuantity;
        current->price = newPrice;
        cout << "Item sudah diperbarui." << endl;
    }
    //Admin Clear Inventory Azkal Salman
    void clearInventory() {
        while (head != nullptr) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
        cout << "Barang sudah dihapus." << endl;
    }

    //Pembeli Add Item(U1) Alif Anya
    void addItemToCart(int id, int quantity) {
        Item* current = head;

        while (current != nullptr && current->id != id) {
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Item tidak ditemukan" << endl;
            return;
        }
        if (current->quantity < quantity) {
            cout << "Stok tidak cukup" << endl;
            return;
        }

        current->quantity -= quantity;
        CartItem newCartItem;
        newCartItem.id = current->id;
        newCartItem.name = current->name;
        newCartItem.quantity = quantity;
        newCartItem.price = current->price;
        cart.push(newCartItem);
        cout << "Barang berhasil dimasukkan ke dalam keranjang.\n" << endl;
    }
    //Pembeli Remove Item Cart Alif Anya
    void removeItemFromCart() {
        if (cart.empty()) {
            cout << "Keranjang kosong" << endl;
            return;
        }

        CartItem removedItem = cart.top();
        cart.pop();
        cout << "Berhasil menghapus " << removedItem.name << " dari keranjang." << endl;

        Item* current = head;
        while (current != nullptr && current->id != removedItem.id) {
            current = current->next;
        }
        if (current != nullptr) {
            current->quantity += removedItem.quantity;
        }
    }
    //Pembeli Display Cart Alif Anya
    void displayCart() const {
        if (cart.empty()) {
            cout << "Keranjang kosong" << endl;
            return;
        }

        stack<CartItem> tempCart = cart;
        int totalHarga = 0;

        cout << "Barang dalam keranjang:" << endl;
        while (!tempCart.empty()) {
            CartItem current = tempCart.top();
            tempCart.pop();
            int subtotal = current.quantity * current.price;
            totalHarga += subtotal;
            cout << "ID: " << current.id 
                 << ", Nama: " << current.name
                 << ", Jumlah barang: " << current.quantity
                 << ", Harga: Rp " << current.price 
                 << ", Subtotal: Rp " << subtotal << endl;
        }
        cout << "\nTotal Harga: Rp " << totalHarga << endl << endl;
    }
    //Pembeli Checkout Alif Anya
    void checkout() {
        if (cart.empty()) {
            cout << "Keranjang kosong, segera isi." << endl;
            return;
        }

        int totalHarga = 0;
        stack<CartItem> tempCart = cart;

        while (!tempCart.empty()) {
            CartItem current = tempCart.top();
            tempCart.pop();
            totalHarga += current.quantity * current.price;
        }

        cout << "Total pembayaran: Rp " << totalHarga << endl;

        // Generate random payment code
        string paymentCode = generatePaymentCode();

        //Pembayaran(P1) Bang Roy
        int paymentMethod;
        cout << "Pilih Metode Pembayaran:\n1. Bank Transfer\n2. Kartu Kredit\n> ";
        cin >> paymentMethod;

        switch (paymentMethod) {
            case 1:
                cout << "Anda telah memilih Bank Transfer. Silahkan untuk segera melakukan pembayaran." << endl;
                cout << "Kode Pembayaran: " << paymentCode << endl;
                break;
            case 2:
                cout << "Anda telah memilih Kartu Kredit. Silahkan untuk segera melakukan pembayaran." << endl;
                cout << "Kode Pembayaran: " << paymentCode << endl;
                break;
            default:
                cout << "Metode pembayaran tidak valid." << endl;
                break;
        }
        while (!cart.empty()) {
            cart.pop();
        }

        cout << "Checkout telah berhasil!\n" << endl;
    }

private:
    string generatePaymentCode() {
        // Initialize random number generator
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(10000000, 99999999); // Generate 6-digit number

        int randomCode = dis(gen);
        return to_string(randomCode);
    }
};
//Admin Menu(A2) Azkal Salman
void AdminMenu(Inventory& inventory) {
    int choice;
    string name;
    int quantity;
    int price;
    int id;

    while (true) {
        cout << "\nPilih:\n1. Tambahkan Barang\n2. Hapus Barang\n3. Tampilkan Barang\n4. Ganti Barang\n5. Bersihkan Barang\n6. Keluar\n> ";
        cin.clear();
        cin >> choice;

        if (choice == 1) {
            cout << "Masukkan Nama Barang: ";
            cin >> name;
            cout << "Masukkan Jumlah Barang: ";
            cin >> quantity;
            cout << "Masukkan Harga Barang: ";
            cin >> price;
            inventory.addItem(name, quantity, price);
        } else if (choice == 2) {
            cout << "Masukkan ID untuk menghapus: ";
            cin >> id;
            inventory.removeItem(id);
        } else if (choice == 3) {
            inventory.displayInventory();
        } else if (choice == 4) {
            cout << "Masukkan ID barang yang ingin diubah: ";
            cin >> id;
            cout << "Masukkan Nama Barang Baru: ";
            cin >> name;
            cout << "Masukkan Jumlah Barang: ";
            cin >> quantity;
            cout << "Masukkan Harga Barang: ";
            cin >> price;
            inventory.changeItem(id, name, quantity, price);
        } else if (choice == 5) {
            inventory.clearInventory();
        } else if (choice == 6) {
            return;
        } else {
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    }
}
//User Menu(U2) Alif Anya Bang Roy
void UserMenu(Inventory& inventory) {
    int choice;
    int id;
    int quantity;

    while (true) {
        inventory.displayInventory();
        cout << "\n\nPilih:\n1. Tambahkan Barang ke Keranjang\n2. Hapus barang terakhir dari keranjang\n3. Tampilkan keranjang\n4. Checkout\n5. Keluar\n> ";
        cin >> choice;

        if (choice == 1) {
            // inventory.displayInventory();
            cout << "Masukkan ID barang untuk masuk ke dalam keranjang : ";
            cin >> id;
            cout << "Masukkan jumlah barang yang ingin dibeli: ";
            cin >> quantity;
            inventory.addItemToCart(id, quantity);
        } else if (choice == 2) {
            inventory.removeItemFromCart();
        } else if (choice == 3) {
            inventory.displayCart();
        } else if (choice == 4) {
            inventory.checkout();
        } else if (choice == 5) {
            cout << "Anda telah keluar" << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    }
}
//Bagian LogIn (L1) Iqbal Chandra
int main() {
    const int MAX_USERS = 100;
    string users[MAX_USERS][2] = { {"admin", "password"}, {"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"} };
    int userCount = 4; 
    string choice;
    string username, password;
    Inventory inventory;
    system("cls");
    cout << "Selamat Datang di OL Shop!" << endl;

    while (true) {
        cout << "\nPilih:\n1. Sign Up\n2. Login\n3. Keluar\n> ";
        cin.clear();
        cin >> choice;

        if (choice == "1") {
            if (userCount >= MAX_USERS) {
                cout << "User telah mencapai batas. Tidak bisa menambah lagi\n";
                continue;
            }

            cout << "Masukkan username: ";
            cin >> username;
            cout << "Masukkan password: ";
            cin >> password;

            if (username == "admin") {
                cout << "Anda hanya pembeli.\n";
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
                cout << "Signup berhasil!\n";
            } else {
                cout << "Username sudah tersedia. Coba gunakan yang lain.\n";
            }
        } else if (choice == "2") {
            cout << "Masukkan username: ";
            cin >> username;
            cout << "Masukkan password: ";
            cin >> password;

            bool loginSuccessful = false;
            for (int i = 0; i < userCount; ++i) {
                if (users[i][0] == username && users[i][1] == password) {
                    loginSuccessful = true;
                    break;
                }
            }

            if (loginSuccessful && username == "admin") {
                cout << "Selamat Datang Admin!\n";
                AdminMenu(inventory);
            } else if (loginSuccessful) {
                cout << "Login Berhasil!\n\n";
                UserMenu(inventory);
            } else {
                cout << "Username dan Password tidak valid. Coba lagi\n";
            }
        } else if (choice == "3") {
            break;
        } else {
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    }

    return 0;
}
