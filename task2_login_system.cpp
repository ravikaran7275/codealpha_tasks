#include <iostream>
#include <fstream>
#include <string>

bool isUsernameTaken(const std::string& username) {
    std::ifstream file("users.txt");
    if (!file.is_open()) return false;

    std::string u, p;
    while (file >> u >> p) {
        if (u == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void registerUser() {
    std::string username, password;
    std::cout << "\nEnter username: ";
    std::cin >> username;

    if (isUsernameTaken(username)) {
        std::cout << "Error: Username already exists. Please choose a different one.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        file << username << " " << password << "\n";
        file.close();
        std::cout << "Success: User registered successfully.\n";
    } else {
        std::cout << "Error: Could not open file for writing.\n";
    }
}

void loginUser() {
    std::string username, password;
    std::cout << "\nEnter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::ifstream file("users.txt");
    if (!file.is_open()) {
        std::cout << "Error: No user database found. Please register first.\n";
        return;
    }

    std::string u, p;
    bool authenticated = false;
    while (file >> u >> p) {
        if (u == username && p == password) {
            authenticated = true;
            break;
        }
    }
    file.close();

    if (authenticated) {
        std::cout << "Success: Login successful. Welcome, " << username << "!\n";
    } else {
        std::cout << "Error: Invalid username or password.\n";
    }
}

int main() {
    int choice;
    while (true) {
        std::cout << "\n1. Register\n2. Login\n3. Exit\nEnter choice: ";
        if (!(std::cin >> choice)) break;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loginUser();
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
