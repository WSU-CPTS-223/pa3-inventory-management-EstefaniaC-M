#include <iostream>
#include <string>
#include "amazon_products.hpp"

using namespace std;

vector<Inventory> inventoryData;;


void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}
void evalCommand(string line)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
      //extract inventory id
      string id = line.substr(5);
      bool found = false;
      for (const auto& item : inventoryData) {
        if (item.uniqId == id){
            item.print();
            found = true;
            break;
        }
        }
      if (!found) {
        cout << "Inventory not found" << endl;
      }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        string category = line.substr(14);
        bool found = false;
        for (const auto& item : inventoryData) {
        for (const auto & cat : item.categories){
            if (cat == category){
                cout << "Uniq ID: " << item.uniqId
                    << " | Product Name: " << item.productName << endl;
                found = true;
                break;
            }
        }
    

    if (!found) {
        cout << "Invalid Category" << endl;
    
    }
    }
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter ':quit' to exit. or ':help' to list supported commands." << endl;
    cout << "\n> ";

    string filename = "amazon_products.csv";
    cout << "Load successful from " << filename << endl;

    inventoryData = loadInventoryFromCSV(filename);

    if (inventoryData.empty()) {
        cerr <<"Hasn't loaded successfully. Exiting." << endl;
    } else{ 
        cout << "Loaded " << inventoryData.size() << " inventory successfully." << endl;
    }
}

int main(int argc, char const *argv[])
{
    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
