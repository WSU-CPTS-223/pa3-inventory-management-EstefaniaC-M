#ifndef AMAZON_PRODUCTS_HPP
#define AMAZON_PRODUCTS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Inventory {
    string uniqId;
    string productName;
    string brandName;
    vector<string> categories; 
    double listPrice;
    double sellingPrice;
    int quantity;

    void print() const {
        cout << "Uniq ID: " << uniqId << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Brand Name: " << brandName << endl;
        cout << "Categories: ";

        for ( size_t i=0; i < categories.size(); i++ ){
            cout << categories[i];
            if (i != categories.size() - 1) {
                cout << " | ";
            }
            
        }
        cout << endl;
        cout << "List Price: $" << listPrice << endl;
        cout << "Selling Price: $" << sellingPrice << endl;
        cout << "Quantity: " << quantity << endl;
    }
};

vector<string> splitCategories(const string& singleString) {
    vector<string> categories;
    stringstream ss(singleString);
    string category;

    // Split by '|'
    while (getline(ss, category, '|')) {
        // If the category is empty, push back "NA"
        if (category.empty())
            categories.push_back("NA");
        else
            categories.push_back(category);
    }

    // If there was no category info at all, mark as "NA"
    if (categories.empty())
        categories.push_back("NA");

    return categories;
}

vector<Inventory> loadInventoryFromCSV(const string& filename) {
    vector<Inventory> inventory;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Trouble opening file: " << filename << endl;
        return inventory;
    }

    // Skip header line
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        Inventory invenItem;
      
        getline(ss, invenItem.uniqId, ',');          // Uniq Id
        getline(ss, invenItem.productName, ',');     // Product Name
        getline(ss, invenItem.brandName, ',');       // Brand Name
        getline(ss, item, ',');                // Asin (skip)
        getline(ss, item, ',');                // Category
        //splitting categories
        invenItem.categories = splitCategories(item);
        getline(ss, item, ',');                // Upc Ean Code (skip)
        getline(ss, item, ',');                // List Price

         if (!item.empty()) {
            invenItem.listPrice = stod(item);  // convert string to double
        } else {
            invenItem.listPrice = 0.0;
        }

        // --- Selling Price ---
        getline(ss, item, ',');
        if (!item.empty()) {
            invenItem.sellingPrice = stod(item);
        } else {
            invenItem.sellingPrice = 0.0;
        }

        // --- Quantity ---
        getline(ss, item, ',');
        if (!item.empty()) {
            invenItem.quantity = stoi(item);  // convert string to int
        } else {
            invenItem.quantity = 0;
        }
        inventory.push_back(invenItem);
    }

    file.close();
    return inventory;
}







#endif