#pragma once

#include <string>
#include <map>

class HashTable {

    std::map<int, std::string> data;

    int get_hash_index(std::string token);
    void hashconflict(int input);
};