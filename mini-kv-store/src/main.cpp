#include "kv_store.h"
#include <iostream>
#include <sstream> 
#include <thread>// NEW: for parsing input line

int main() {
    KVStore kv;
    kv.loadFromFile("store.txt");
    std::string line, command, key, value;

    std::cout << "Mini Key-Value Store. Commands: PUT, GET, DEL, LIST, EXIT\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line); // Read whole line instead of one word

        std::istringstream iss(line); // Create string stream from line
        iss >> command;

        if (command == "PUT") {
            iss >> key;
            std::getline(iss, value); // Read the rest as value (with spaces)
            if (!value.empty() && value[0] == ' ')
                value.erase(0, 1); // Remove leading space
            kv.put(key, value);
            std::cout << "Stored [" << key << " => " << value << "]\n";
        } 
        else if (command == "GET") {
            iss >> key;
            std::cout << kv.get(key) << "\n";
        } 
        else if (command == "DEL") {
            iss >> key;
            kv.del(key);
            std::cout << "Deleted key [" << key << "]\n";
        } 
        else if (command == "LIST") {
            kv.list();
        } 
        else if (command == "EXIT") {
            kv.saveToFile("store.txt");
            std::cout << "Data saved successfully.\n";
            break;
        } 
        else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}
