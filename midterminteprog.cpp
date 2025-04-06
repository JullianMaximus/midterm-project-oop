#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid number.\n";
        } else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

class Item {
private:
    static int nextID;
    int productID;
    string name, category;
    int quantity;
    double price;

public:
    Item(string n, string c, int q, double p) {
        productID = nextID++;
        name = n;
        category = c;
        quantity = q;
        price = p;
    }

    int getID() const { return productID; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }

    void display() const {
        cout << left << setw(5) << productID
             << setw(15) << name
             << setw(12) << quantity
             << setw(10) << fixed << setprecision(2) << price
             << setw(15) << category << endl;
    }
};

int Item::nextID = 1;

class Inventory {
private:
    vector<Item> items;

public:
    void addItem() {
        string name, category;
        int quantity;
        double price;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Category: ";
        cin >> category;
        quantity = getIntInput("Enter Quantity: ");
        price = getDoubleInput("Enter Price: ");

        items.push_back(Item(name, category, quantity, price));
        cout << "Item added successfully!\n";
    }

    void updateItem() {
        int id = getIntInput("Enter Product ID to update: ");

        for (auto &item : items) {
            if (item.getID() == id) {
                char option;
                cout << "Update (q)uantity or (p)rice? ";
                cin >> option;
                if (option == 'q') {
                    int oldQuantity = item.getQuantity();
                    int newQuantity = getIntInput("Enter new quantity: ");
                    item.setQuantity(newQuantity);
                    cout << "Quantity of Item \"" << item.getName() << "\" updated from "
                         << oldQuantity << " to " << newQuantity << ".\n";
                } else if (option == 'p') {
                    double oldPrice = item.getPrice();
                    double newPrice = getDoubleInput("Enter new price: ");
                    item.setPrice(newPrice);
                    cout << "Price of Item \"" << item.getName() << "\" updated from "
                         << fixed << setprecision(2) << oldPrice << " to " << newPrice << ".\n";
                } else {
                    cout << "Invalid option. Use 'q' for quantity or 'p' for price.\n";
                }
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void removeItem() {
        int id = getIntInput("Enter Product ID to remove: ");

        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getID() == id) {
                cout << "Item \"" << it->getName() << "\" removed.\n";
                items.erase(it);
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void displayAll() {
        if (items.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        cout << left << setw(5) << "ID"
             << setw(15) << "Name"
             << setw(12) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;
        cout << string(55, '-') << endl;

        for (const auto &item : items) {
            item.display();
        }
    }

    void searchItem() {
        int id = getIntInput("Enter Product ID to search: ");

        for (const auto &item : items) {
            if (item.getID() == id) {
                cout << "Item found:\n";
                cout << left << setw(5) << "ID"
                     << setw(15) << "Name"
                     << setw(12) << "Quantity"
                     << setw(10) << "Price"
                     << setw(15) << "Category" << endl;
                item.display();
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void displayLowStock() {
        bool found = false;
        cout << left << setw(5) << "ID"
             << setw(15) << "Name"
             << setw(12) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;
        cout << string(55, '-') << endl;

        for (const auto &item : items) {
            if (item.getQuantity() <= 5) {
                item.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No low stock items.\n";
        }
    }

    void sortItems() {
        if (items.empty()) {
            cout << "Inventory is empty. Nothing to sort.\n";
            return;
        }

        int type = getIntInput("Sort by:\n1 - Quantity\n2 - Price\nEnter choice: ");
        int order = getIntInput("Order:\n1 - Ascending\n2 - Descending\nEnter choice: ");

        if (type == 1) {
            sort(items.begin(), items.end(), [order](const Item &a, const Item &b) {
                return order == 1 ? a.getQuantity() < b.getQuantity()
                                  : a.getQuantity() > b.getQuantity();
            });
        } else if (type == 2) {
            sort(items.begin(), items.end(), [order](const Item &a, const Item &b) {
                return order == 1 ? a.getPrice() < b.getPrice()
                                  : a.getPrice() > b.getPrice();
            });
        } else {
            cout << "Invalid sorting option.\n";
            return;
        }

        cout << "Items sorted successfully!\n";
    }
};

int main() {
    Inventory inventory;
    int choice;

    do {
        cout << "\nMenu\n";
        cout << "1 - Add Item\n";
        cout << "2 - Update Item\n";
        cout << "3 - Remove Item\n";
        cout << "4 - Display All Items\n";
        cout << "5 - Search Item\n";
        cout << "6 - Sort Items\n";
        cout << "7 - Display Low Stock Items\n";
        cout << "8 - Exit\n";

        choice = getIntInput("Enter choice: ");

        switch (choice) {
            case 1: inventory.addItem(); break;
            case 2: inventory.updateItem(); break;
            case 3: inventory.removeItem(); break;
            case 4: inventory.displayAll(); break;
            case 5: inventory.searchItem(); break;
            case 6: inventory.sortItems(); break;
            case 7: inventory.displayLowStock(); break;
            case 8: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
