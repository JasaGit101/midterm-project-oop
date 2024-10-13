#include <iostream>
#include <string>
#include <iomanip>
#include <cctype> // For character checking
using namespace std;

class Item {
private:
    string id;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item(string id, string name, int quantity, double price, string category)
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    // Setters
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(double p) { price = p; }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << quantity
             << setw(10) << price
             << setw(15) << category << endl;
    }
};

class Inventory {
private:
    Item* items[100]; // Fixed size for simplicity
    int itemCount;

    bool isValidString(const string& str) {
    // Check if the string contains only alphabetic characters
    for (char c : str) {
        if (!isalpha(c)) return false; // Not a valid string
    }
    return !str.empty(); // Ensure it's not empty
}

bool isValidQuantity(const string& qtyStr) {
    // Check if the quantity is a valid non-negative integer
    for (char c : qtyStr) {
        if (!isdigit(c)) return false; // Not a valid integer
    }
    return true; // Valid non-negative integer
}

bool isValidPrice(const string& priceStr) {
    // Check if the price is a valid non-negative float/double
    bool decimalFound = false; // Track if decimal point has been found
    for (char c : priceStr) {
        if (!isdigit(c)) {
            if (c == '.' && !decimalFound) {
                decimalFound = true; // Accept one decimal point
            } else {
                return false; // Not a valid float/double
            }
        }
    }
    return !priceStr.empty() && (priceStr[0] != '.'); // Ensure it's not empty or just a decimal
}
    
    void toLowerCase(string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32; // Convert to lowercase by adjusting ASCII value
        }
    }
}

public:
    Inventory() : itemCount(0) {}

    void AddItem() {
    string category;
    cout << "Enter Category (Clothing, Electronics, Entertainment): ";
    cin >> category;

    // Convert category to lowercase
    toLowerCase(category);
    
    if (category != "clothing" && category != "electronics" && category != "entertainment") {
        cout << "Category " << category << " does not exist!" << endl;
        return;
    }

    string id, name, qtyStr, priceStr;

    // Input ID
    cout << "Enter ID (string): ";
    cin >> id;
    while (!isValidString(id)) {
        cout << "Invalid ID! Please enter a valid string (only alphabetic characters): ";
        cin >> id;
    }

    // Input Name
    cout << "Enter Name (string): ";
    cin >> name;
    while (!isValidString(name)) {
        cout << "Invalid Name! Please enter a valid string (only alphabetic characters): ";
        cin >> name;
    }

    // Input Quantity
    cout << "Enter Quantity (integer): ";
    cin >> qtyStr;
    while (!isValidQuantity(qtyStr)) {
        cout << "Invalid Quantity! Please enter a valid non-negative integer: ";
        cin >> qtyStr;
    }
    int quantity = stoi(qtyStr); // Convert string to int

    // Input Price
    cout << "Enter Price (float/double): ";
    cin >> priceStr;
    while (!isValidPrice(priceStr)) {
        cout << "Invalid Price! Please enter a valid non-negative float/double: ";
        cin >> priceStr;
    }
    double price = stod(priceStr); // Convert string to double

    // Add item to the inventory
    items[itemCount] = new Item(id, name, quantity, price, category);
    itemCount++;
    cout << "Item added successfully!" << endl;
}

    void UpdateItem() {
    if (itemCount == 0) {
        cout << "There are no items in the inventory to be updated." << endl;
        return;
    }

    string id;
    cout << "Input ID: ";
    cin >> id;

    for (int i = 0; i < itemCount; i++) {
        if (items[i]->getId() == id) {
            string option;
            cout << "Update Quantity or Price? (Enter 'quantity' or 'price', or 'cancel' to cancel): ";
            cin >> option;

            // Convert option to lowercase for case insensitive comparison
            for (char &c : option) {
                c = tolower(c);
            }

            if (option == "quantity") {
                int newQuantity;
                cout << "Input new quantity: ";
                cin >> newQuantity;
                
                // Validate new quantity
                while (newQuantity < 0) { // Ensure it's non-negative
                    cout << "Invalid quantity! Please enter a non-negative quantity: ";
                    cin >> newQuantity;
                }
                
                int oldQuantity = items[i]->getQuantity();
                
                if (newQuantity != oldQuantity) { // Check if the new quantity is different
                    items[i]->setQuantity(newQuantity);
                    cout << "Quantity of Item " << items[i]->getName() 
                         << " is updated from " << oldQuantity << " to " << newQuantity << endl;
                } else {
                    cout << "No change in quantity. Current quantity is still " << oldQuantity << "." << endl;
                }

            } else if (option == "price") {
                double newPrice;
                cout << "Input new price: ";
                cin >> newPrice;

                // Validate new price
                while (newPrice < 0) { // Ensure it's non-negative
                    cout << "Invalid price! Please enter a non-negative price: ";
                    cin >> newPrice;
                }
                
                double oldPrice = items[i]->getPrice();
                
                if (newPrice != oldPrice) { // Check if the new price is different
                    items[i]->setPrice(newPrice);
                    cout << "Price of Item " << items[i]->getName() 
                         << " is updated from " << oldPrice << " to " << newPrice << endl;
                } else {
                    cout << "No change in price. Current price is still " << oldPrice << "." << endl;
                }

            } else if (option == "cancel") {
                cout << "Update cancelled." << endl;
                return;
            } else {
                cout << "Invalid option! Please enter 'quantity' or 'price'." << endl;
            }
            return;
        }
    }
    cout << "Item not found!" << endl;
}

    void RemoveItem() {
        if (itemCount == 0) {
            cout << "There is no item in the inventory to be removed." << endl;
            return;
        }

        string id;
        cout << "Input ID: ";
        cin >> id;

        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getId() == id) {
                cout << "Item " << items[i]->getName() << " has been removed from the inventory." << endl;
                delete items[i]; // Free memory
                items[i] = items[itemCount - 1]; // Move last item to this position
                itemCount--;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void DisplayItemsByCategory() {
        if (itemCount == 0) {
            cout << "There are no items in the inventory to display." << endl;
            return;
        }

        string category;
        cout << "Input Category (Clothing, Electronics, Entertainment): ";
        cin >> category;

        // Convert category to lowercase for case insensitive comparison
        for (char &c : category) {
            c = tolower(c);
        }

        if (category != "clothing" && category != "electronics" && category != "entertainment") {
            cout << "Category " << category << " does not exist!" << endl;
            return;
        }

        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;

        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getCategory() == category) {
                items[i]->display();
                found = true;
            }
        }

        if (!found) {
            cout << "No items found in category " << category << "." << endl;
        }
    }

    void DisplayAllItems() {
        if (itemCount == 0) {
            cout << "There are no items in the inventory to display." << endl;
            return;
        }

        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;

        for (int i = 0; i < itemCount; i++) {
            items[i]->display();
        }
    }

    void SearchItem() {
        if (itemCount == 0) {
            cout << "There is no item in the inventory to search." << endl;
            return;
        }

        string id;
        cout << "Input ID: ";
        cin >> id;

        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getId() == id) {
                items[i]->display();
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void SortItems() {
        if (itemCount == 0) {
            cout << "There are no items in the inventory to sort." << endl;
            return;
        }

        int sortOption;
        cout << "Sort by: 1. Quantity 2. Price (Enter 1 or 2): ";
        cin >> sortOption;

        bool ascending;
        cout << "Ascending or Descending? (Enter 1 for Ascending, 0 for Descending): ";
        cin >> ascending;

        for (int i = 0; i < itemCount - 1; i++) {
            for (int j = i + 1; j < itemCount; j++) {
                bool condition = (sortOption == 1) ? 
                    (ascending ? items[i]->getQuantity() > items[j]->getQuantity() 
                               : items[i]->getQuantity() < items[j]->getQuantity()) : 
                    (ascending ? items[i]->getPrice() > items[j]->getPrice() 
                               : items[i]->getPrice() < items[j]->getPrice());
                
                if (condition) {
                    Item* temp = items[i];
                    items[i] = items[j];
                    items[j] = temp;
                }
            }
        }

        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;

        for (int i = 0; i < itemCount; i++) {
            items[i]->display();
        }
    }

    void DisplayLowStockItems() {
        if (itemCount == 0) {
            cout << "There are no items in the inventory to display low stock items." << endl;
            return;
        }

        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;

        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getQuantity() <= 5) { // Assuming low stock threshold is 5
                items[i]->display();
                found = true;
            }
        }

        if (!found) {
            cout << "No low stock items found." << endl;
        }
    }
};

bool isValidMenuChoice(const string& choice) {
    // Check if choice is a number between 1 and 9
    if (choice.length() != 1 || !isdigit(choice[0])) {
        return false;
    }
    
    int numChoice = choice[0] - '0'; // Convert char to int
    return (numChoice >= 1 && numChoice <= 9);
}

int main() {
    Inventory inventory;
    string choice;

    do {
        cout << "\nMenu:\n"
             << "1 - Add Item\n"
             << "2 - Update Item\n"
             << "3 - Remove Item\n"
             << "4 - Display Items by Category\n"
             << "5 - Display All Items\n"
             << "6 - Search Item\n"
             << "7 - Sort Items\n"
             << "8 - Display Low Stock Items\n"
             << "9 - Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        // Validate the menu choice
        while (!isValidMenuChoice(choice)) {
            cout << "Invalid input! Please enter a number between 1 and 9: ";
            cin >> choice;
        }

        int numChoice = choice[0] - '0'; // Convert char to int
        switch (numChoice) {
            case 1: inventory.AddItem(); break;
            case 2: inventory.UpdateItem(); break;
            case 3: inventory.RemoveItem(); break;
            case 4: inventory.DisplayItemsByCategory(); break;
            case 5: inventory.DisplayAllItems(); break;
            case 6: inventory.SearchItem(); break;
            case 7: inventory.SortItems(); break;
            case 8: inventory.DisplayLowStockItems(); break;
            case 9: cout << "Exiting the program." << endl; break;
        }
    } while (choice[0] != '9');

    return 0;
}
