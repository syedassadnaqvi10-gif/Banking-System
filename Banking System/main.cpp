#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Customer Class
class Customer {
private:
    int customerID;
    string name;
    string email;
    string phone;

public:
    Customer(int id, string n, string e, string p) {
        customerID = id;
        name = n;
        email = e;
        phone = p;
    }

    int getID() {
        return customerID;
    }

    string getName() {
        return name;
    }

    void displayCustomer() {
        cout << "\nCustomer ID: " << customerID;
        cout << "\nName: " << name;
        cout << "\nEmail: " << email;
        cout << "\nPhone: " << phone << endl;
    }
};

// Transaction Class
class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }

    void display() {
        cout << type << " : Rs. "
             << fixed << setprecision(2) << amount << endl;
    }
};

// Account Class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int number, double initialBalance = 0) {
        accountNumber = number;
        balance = initialBalance;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return;
        }

        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));

        cout << "Deposit successful!\n";
    }

    void withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Insufficient balance or invalid amount!\n";
            return;
        }

        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));

        cout << "Withdrawal successful!\n";
    }

    void transfer(Account &receiver, double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Transfer failed!\n";
            return;
        }

        balance -= amount;
        receiver.balance += amount;

        transactions.push_back(Transaction("Transfer Sent", amount));
        receiver.transactions.push_back(Transaction("Transfer Received", amount));

        cout << "Transfer successful!\n";
    }

    void displayAccount() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nBalance: Rs. "
             << fixed << setprecision(2) << balance << endl;
    }

    void showTransactions() {
        cout << "\n--- Transaction History ---\n";

        if (transactions.empty()) {
            cout << "No transactions found.\n";
            return;
        }

        for (auto &t : transactions) {
            t.display();
        }
    }
};

// Banking System Class
class BankingSystem {
private:
    vector<Customer> customers;
    vector<Account> accounts;

public:
    void createCustomer() {
        int id;
        string name, email, phone;

        cout << "Enter Customer ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Email: ";
        getline(cin, email);

        cout << "Enter Phone: ";
        getline(cin, phone);

        customers.push_back(Customer(id, name, email, phone));

        cout << "Customer created successfully!\n";
    }

    void createAccount() {
        int number;
        double balance = 0;

        cout << "Enter Account Number: ";
        cin >> number;

        cout << "Enter Initial Deposit: ";
        cin >> balance;

        if (balance < 0) {
            cout << "Invalid initial deposit!\n";
            return;
        }

        accounts.push_back(Account(number, balance));

        cout << "Account created successfully!\n";
    }

    Account* findAccount(int number) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == number) {
                return &account;
            }
        }
        return nullptr;
    }

    void depositMoney() {
        int number;
        double amount;

        cout << "Enter Account Number: ";
        cin >> number;

        Account* account = findAccount(number);

        if (account == nullptr) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        account->deposit(amount);
    }

    void withdrawMoney() {
        int number;
        double amount;

        cout << "Enter Account Number: ";
        cin >> number;

        Account* account = findAccount(number);

        if (account == nullptr) {
            cout << "Account not found!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        account->withdraw(amount);
    }

    void transferMoney() {
        int sender, receiver;
        double amount;

        cout << "Enter Sender Account: ";
        cin >> sender;

        cout << "Enter Receiver Account: ";
        cin >> receiver;

        Account* senderAccount = findAccount(sender);
        Account* receiverAccount = findAccount(receiver);

        if (senderAccount == nullptr || receiverAccount == nullptr ||
            senderAccount == receiverAccount) {
            cout << "Invalid accounts!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        senderAccount->transfer(*receiverAccount, amount);
    }

    void checkBalance() {
        int number;

        cout << "Enter Account Number: ";
        cin >> number;

        Account* account = findAccount(number);

        if (account != nullptr) {
            account->displayAccount();
        } else {
            cout << "Account not found!\n";
        }
    }

    void transactionHistory() {
        int number;

        cout << "Enter Account Number: ";
        cin >> number;

        Account* account = findAccount(number);

        if (account != nullptr) {
            account->showTransactions();
        } else {
            cout << "Account not found!\n";
        }
    }

    void displayCustomers() {
        for (auto &customer : customers) {
            customer.displayCustomer();
        }

        if (customers.empty()) {
            cout << "No customers found.\n";
        }
    }

    void menu() {
        int choice;

        do {
            cout << "\n========== BANKING MANAGEMENT SYSTEM ==========\n";
            cout << "1. Create Customer\n";
            cout << "2. Create Account\n";
            cout << "3. Deposit Money\n";
            cout << "4. Withdraw Money\n";
            cout << "5. Transfer Money\n";
            cout << "6. Check Balance\n";
            cout << "7. Transaction History\n";
            cout << "8. Display Customers\n";
            cout << "0. Exit\n";

            cout << "\nEnter Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createCustomer();
                    break;

                case 2:
                    createAccount();
                    break;

                case 3:
                    depositMoney();
                    break;

                case 4:
                    withdrawMoney();
                    break;

                case 5:
                    transferMoney();
                    break;

                case 6:
                    checkBalance();
                    break;

                case 7:
                    transactionHistory();
                    break;

                case 8:
                    displayCustomers();
                    break;

                case 0:
                    cout << "Thank you for using our banking system!\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }

        } while (choice != 0);
    }
};

// Main Function
int main() {
    BankingSystem bank;
    bank.menu();

    return 0;
}