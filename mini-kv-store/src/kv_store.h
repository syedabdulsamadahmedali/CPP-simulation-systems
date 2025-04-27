#pragma once

#include <unordered_map>
#include <string>
#include <mutex>

class KVStore {
public:
    // Insert or update a key-value pair
    void put(const std::string& key, const std::string& value);

    // Retrieve a value by key
    std::string get(const std::string& key) const;

    // Delete a key-value pair
    void del(const std::string& key);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;


    // List all keys
    void list() const;

private:
    std::unordered_map<std::string, std::string> store_;
    mutable std::mutex mtx_;
};
