#pragma once

#include <string>
#include <shares.h>
#include <unordered_map>

class HashTable {

    std::unordered_map<int, Share> data;

    bool check_hashconflict(int &input, int step);
    bool check_is_right_location(int &index, int step, std::string token);
    void hash_step(int &input, int step);

    int get_hash_index(std::string token);

    std::pair<int, Share*> search_map(std::string token);

    public:
    void save_in_map(Share share);
    void delete_from_map(std::string token);
    Share* get_share_from_map(std::string token);

    //debug function
    void print_map();
};