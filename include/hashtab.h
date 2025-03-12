#pragma once

#include <string>
#include <map>

class HashTable {

    std::map<int, std::string> data;

    void resolve_hashconflict(int input);

    public:
    int get_hash_index(std::string token);
};