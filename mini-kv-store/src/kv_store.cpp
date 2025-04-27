#include "kv_store.h"
#include <iostream>
#include <fstream>
#include <mutex> 

void KVStore::put(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mtx_);
    store_[key] = value;
}


std::string KVStore::get(const std::string& key) const {
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = store_.find(key);
    if (it != store_.end()) {
        return it->second;
    } else {
        return "Key not found.";
    }
}


void KVStore::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(mtx_);
    store_.erase(key);
}


void KVStore::list() const {
    std::lock_guard<std::mutex> lock(mtx_);
    for (const auto& pair : store_) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }
}


void KVStore::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "No existing store file. Starting fresh.\n";
        return;
    }

    std::string key, value;
    while (std::getline(infile, key) && std::getline(infile, value)) {
        store_[key] = value;
    }
}

void KVStore::saveToFile(const std::string& filename) const {
    std::ofstream outfile(filename);
    for (const auto& pair : store_) {
        outfile << pair.first << "\n" << pair.second << "\n";
    }
}
