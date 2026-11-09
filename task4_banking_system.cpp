#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Transaction {
private:
    std::string type;
    double amount;
    double postBalance;

public:
    Transaction(std::string t, double amt, double bal)
        : type(t), amount(amt), postBalance(bal) {}

    void display() const {
        std::cout << std::left << std::setw(15) << type
                  << std::setw(12) << amount
                  << std::setw(12) << postBalance << "\n";
    }
};

class Customer {
private:
    std::string customerId;
    std::string name;

public:
    Customer() = default;
    Customer(std::string id, std::string n) : customerId(id), name(n) {}

    std::string getId() const { return customerId; }
    std::string getName() const { return name; }
};

class Account {
private:
    int accountNumber;
    Customer customer;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account(int accNum, Customer cust, double initialBalance)
        : accountNumber(accNum), customer(cust), balance(initialBalance) {
        transactions.emplace_back("Initial", initialBalance, balance);
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        transactions.emplace_back("Deposit", amount, balance);
        std::cout << "Successfully deposited $" << amount << ". New balance: $" << balance << "\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Invalid withdrawal amount.\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount, balance);
        std::cout << "Successfully withdrew $" << amount << ". New balance: $" << balance << "\n";
        return true;
    }

    void addTransferRecord(const std::string& type, double amount) {
        transactions.emplace_back(type, amount, balance);
    }

    void displayDetails() const {
        std::cout << "\n--- Account Information ---\n";
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "Customer ID:    " << customer.getId() << "\n";
        std::cout << "Customer Name:  " << customer.getName() << "\n";
        std::cout << "Current Balance: $" << balance << "\n";
    }

    void displayHistory() const {
        std::cout << "\n--- Transaction History for Account " << accountNumber << " ---\n";
        std::cout << std::left << std::setw(15) << "Type" << std::setw(12) << "Amount" << std::setw(12) << "Balance" << "\n";
        for (const auto& t : transactions) {
            t.display();
        }
    }
};

Account* findAccount(std::vector<Account>& accounts, int accNum) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return &acc;
        }
    }
    return nullptr;
}

int main() {
    std::vector<Account> accounts;
    int nextAccNum = 1001;
    int choice;

    while (true) {
        std::cout << "\n=== Banking System ===\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Fund Transfer\n";
        std::cout << "5. Account Info & Balance\n";
        std::cout << "6. Transaction History\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter choice: ";
        if (!(std::cin >> choice)) break;

        if (choice == 1) {
            std::string id, name;
            double initialDeposit;
            std::cout << "Enter Customer ID: ";
            std::cin >> id;
            std::cout << "Enter Customer Name: ";
            std::cin >> name;
            std::cout << "Enter Initial Deposit: ";
            std::cin >> initialDeposit;

            Customer c(id, name);
            accounts.emplace_back(nextAccNum, c, initialDeposit);
            std::cout << "Account created successfully. Your Account Number is: " << nextAccNum << "\n";
            nextAccNum++;
        } else if (choice == 2) {
            int accNum;
            double amt;
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc) {
                std::cout << "Enter Deposit Amount: ";
                std::cin >> amt;
                acc->deposit(amt);
            } else {
                std::cout << "Account not found.\n";
            }
        } else if (choice == 3) {
            int accNum;
            double amt;
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc) {
                std::cout << "Enter Withdrawal Amount: ";
                std::cin >> amt;
                acc->withdraw(amt);
            } else {
                std::cout << "Account not found.\n";
            }
        } else if (choice == 4) {
            int fromAccNum, toAccNum;
            double amt;
            std::cout << "Enter Source Account Number: ";
            std::cin >> fromAccNum;
            std::cout << "Enter Destination Account Number: ";
            std::cin >> toAccNum;

            Account* fromAcc = findAccount(accounts, fromAccNum);
            Account* toAcc = findAccount(accounts, toAccNum);

            if (!fromAcc || !toAcc) {
                std::cout << "One or both account numbers are invalid.\n";
                continue;
            }
            if (fromAccNum == toAccNum) {
                std::cout << "Cannot transfer to the same account.\n";
                continue;
            }

            std::cout << "Enter Transfer Amount: ";
            std::cin >> amt;

            if (fromAcc->withdraw(amt)) {
                toAcc->deposit(amt);
                fromAcc->addTransferRecord("Transfer Sent", amt);
                toAcc->addTransferRecord("Transfer Recv", amt);
                std::cout << "Transfer completed successfully.\n";
            }
        } else if (choice == 5) {
            int accNum;
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc) {
                acc->displayDetails();
            } else {
                std::cout << "Account not found.\n";
            }
        } else if (choice == 6) {
            int accNum;
            std::cout << "Enter Account Number: ";
            std::cin >> accNum;
            Account* acc = findAccount(accounts, accNum);
            if (acc) {
                acc->displayHistory();
            } else {
                std::cout << "Account not found.\n";
            }
        } else if (choice == 7) {
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
