#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Structure to store expense details
struct Expense {
    string category;
    string description;
    double amount;
};

// Function to add a new expense
void addExpense(vector<Expense>& expenses) {
    Expense exp;
    cout << "Enter category (e.g., Food, Travel): ";
    cin >> exp.category;
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, exp.description);
    cout << "Enter amount: ";
    cin >> exp.amount;
    expenses.push_back(exp);
    cout << "Expense added successfully.\n";
}

// Function to display all expenses
void viewExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }
    cout << setw(10) << "Category" << setw(20) << "Description" << setw(10) << "Amount\n";
    cout << string(40, '-') << '\n';
    for (const auto& exp : expenses) {
        cout << setw(10) << exp.category
             << setw(20) << exp.description
             << setw(10) << exp.amount << '\n';
    }
}

// Function to calculate total expenses by category
void calculateCategoryTotal(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses to calculate.\n";
        return;
    }
    cout << "Enter the category to calculate total for: ";
    string category;
    cin >> category;
    double total = 0.0;
    for (const auto& exp : expenses) {
        if (exp.category == category) {
            total += exp.amount;
        }
    }
    cout << "Total expenses for " << category << ": " << total << '\n';
}

// Function to save expenses to a file
void saveExpenses(const vector<Expense>& expenses) {
    ofstream outFile("expenses.txt");
    for (const auto& exp : expenses) {
        outFile << exp.category << '|' << exp.description << '|' << exp.amount << '\n';
    }
    cout << "Expenses saved to file successfully.\n";
}

// Function to load expenses from a file
void loadExpenses(vector<Expense>& expenses) {
    ifstream inFile("expenses.txt");
    if (!inFile) {
        cout << "No saved expenses found.\n";
        return;
    }
    expenses.clear();
    Expense exp;
    string line;
    while (getline(inFile, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        exp.category = line.substr(0, pos1);
        exp.description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        exp.amount = stod(line.substr(pos2 + 1));
        expenses.push_back(exp);
    }
    cout << "Expenses loaded successfully.\n";
}

// Main menu
void showMenu() {
    cout << "\nExpense Tracker Menu:\n";
    cout << "1. Add Expense\n";
    cout << "2. View Expenses\n";
    cout << "3. Calculate Total by Category\n";
    cout << "4. Save Expenses to File\n";
    cout << "5. Load Expenses from File\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Expense> expenses;
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                calculateCategoryTotal(expenses);
                break;
            case 4:
                saveExpenses(expenses);
                break;
            case 5:
                loadExpenses(expenses);
                break;
            case 6:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
