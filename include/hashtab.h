#pragma once

#include <string>
#include <shares.h>
#include <map>

class HashTable {

    std::map<int, Share> data;

    bool check_hashconflict(int &input, int step);
    void hash_step(int &input, int step);

    int get_hash_index(std::string token);

    public:
    void save_in_map(Share share);
    void delete_from_map(std::string token);
    Share* search_map(std::string token, int step = 1);

    //debug function
    void print_map();
};