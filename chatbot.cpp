#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Structure for Transaction (Linked List)
struct Transaction {
    string type;
    double amount;
    string date;
    Transaction* next;
};

// Structure for Account (Linked List)
struct Account {
    int accNo;
    string name;
    double balance;
    Transaction* history;
    Account* next;
};

class ChatBot {
private:
    Account* head;

    // Find account by account number
    Account* findAccount(int accNo) {
        Account* temp = head;
        while (temp != NULL) {
            if (temp->accNo == accNo)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    // Record transaction (add node at beginning)
    void recordTransaction(Account* acc, string type, double amount, string date) {
        Transaction* t = new Transaction;
        t->type = type;
        t->amount = amount;
        t->date = date;
        t->next = acc->history;
        acc->history = t;
    }

public:
    ChatBot() { head = NULL; }

    // Create demo accounts (for testing)
    void createDemoAccounts() {
        Account* a1 = new Account{1001, "Ashhul", 10000, NULL, NULL};
        Account* a2 = new Account{1002, "Lucky", 12450, NULL, NULL};
        a2->next = a1;
        head = a2;
    }

    void startChat() {
        cout << "Bot: Hello! Welcome to SmartBank. What's your name?\n";
        cout << "User: ";
        string userName;
        getline(cin, userName);

        cout << "Bot: Nice to meet you, " << userName << "! Do you have an account with us?\n";
        cout << "User: ";
        string hasAccount;
        getline(cin, hasAccount);

        if (hasAccount == "no" || hasAccount == "No") {
            cout << "Bot: Oh! Please visit our nearest branch to create an account, " << userName << ".\n";
            return;
        }

        cout << "Bot: Great! Please enter your account number.\n";
        cout << "User: ";
        int accNo;
        cin >> accNo;

        Account* userAcc = findAccount(accNo);
        if (!userAcc) {
            cout << "Bot: Sorry, account not found. Please check your account number.\n";
            return;
        }

        cout << "Bot: What would you like to do today?\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. View Transaction History\n";
        cout << "5. Transfer Funds\n";

        cout << "User: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Bot: Your current balance is ?" << fixed << setprecision(2)
                     << userAcc->balance << ".\n";
                break;

            case 2: {
                double amt;
                cout << "Bot: Enter the amount to deposit:\n";
                cout << "User: ";
                cin >> amt;
                userAcc->balance += amt;
                recordTransaction(userAcc, "Deposit", amt, "27-Oct-2025");
                cout << "Bot: ?" << amt << " has been successfully deposited.\n";
                cout << "Bot: Your new balance is ?" << userAcc->balance << ".\n";
                break;
            }

            case 3: {
                double amt;
                cout << "Bot: Enter the amount to withdraw:\n";
                cout << "User: ";
                cin >> amt;
                if (amt > userAcc->balance) {
                    cout << "Bot: Insufficient balance!\n";
                } else {
                    userAcc->balance -= amt;
                    recordTransaction(userAcc, "Withdraw", amt, "27-Oct-2025");
                    cout << "Bot: ?" << amt << " withdrawn successfully.\n";
                    cout << "Bot: Remaining balance ?" << userAcc->balance << ".\n";
                }
                break;
            }

            case 4: {
                cout << "Bot: Here’s your recent transaction history:\n";
                Transaction* t = userAcc->history;
                if (!t) cout << "No transactions yet.\n";
                else {
                    while (t != NULL) {
                        cout << "- " << t->type << " ?" << t->amount
                             << " on " << t->date << "\n";
                        t = t->next;
                    }
                }
                break;
            }

            case 5: {
                int targetAcc;
                double amt;
                cout << "Bot: Enter receiver’s account number:\n";
                cout << "User: ";
                cin >> targetAcc;
                Account* receiver = findAccount(targetAcc);
                if (!receiver) {
                    cout << "Bot: Receiver account not found.\n";
                    break;
                }
                cout << "Bot: Enter amount to transfer:\n";
                cout << "User: ";
                cin >> amt;
                if (amt > userAcc->balance) {
                    cout << "Bot: Not enough balance for this transfer.\n";
                    break;
                }
                userAcc->balance -= amt;
                receiver->balance += amt;
                recordTransaction(userAcc, "Transfer (to " + receiver->name + ")", amt, "27-Oct-2025");
                recordTransaction(receiver, "Received (from " + userAcc->name + ")", amt, "27-Oct-2025");
                cout << "Bot: ?" << amt << " has been transferred to " << receiver->name << ".\n";
                cout << "Bot: Your remaining balance is ?" << userAcc->balance << ".\n";
                break;
            }

            default:
                cout << "Bot: Sorry, I didn’t understand that option.\n";
        }

        cout << "User: Thank you!\n";
        cout << "Bot: You’re welcome, " << userName << "! ??\n";
    }
};

int main() {
    ChatBot bot;
    bot.createDemoAccounts(); // Pre-loads sample accounts
    bot.startChat();
    return 0;
}