#include <iostream>
#include <string>

using namespace std;

int main() {
    const int MAX_USERS = 100;
    string users[MAX_USERS][2] = { {"admin", "password"}, {"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"} };
    int userCount = 4; // to keep track of the number of users
    string choice;
    string username, password;

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
                // INFO: DISINI MASUK LOGIN SEBAGAI ADMIN
            }
            else if (loginSuccessful) {
                cout << "Login successful!\n";
                // INFO: DISINI MASUK LOGIN SEBAGAI PEMBELI
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
