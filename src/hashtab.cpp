#include <hashtab.h>
#include <iostream>
#include <functional>

#define HASH_SIZE 240

// helper functions

int HashTable::get_hash_index(std::string token) {
    unsigned long hash = 0;
    for (char c : token) {
        hash = hash * 31 + c;
    }

    return hash % HASH_SIZE;  
}

void HashTable::delete_from_map(std::string token) {
    
    
}

Share* HashTable::search_map(std::string token) {

    int index = get_hash_index(token);

    if (!check_is_right_location(index, 1, token)) {
        std::cout << "\nERROR: Share not found\n";
        return nullptr;
    }
    
    return &data.at(index);
}

bool HashTable::check_is_right_location(int &index, int step, std::string token) {

    if (data.find(index) != data.end() && data.at(index).getToken() == token) return true;
    if (step == 10) return false;

    hash_step(index, step);

    return check_is_right_location(index, ++step, token);
    
}


void HashTable::save_in_map(Share share) {

    int index = get_hash_index(share.getToken());

    if (!check_hashconflict(index, 1)) {
        std::cout << "\n ERROR: STORAGE FULL\n";
        return;
    };

    data.insert({index, share});
}

bool HashTable::check_hashconflict(int& index, int step) {

    if (data.find(index) == data.end()) return true;
    if (step == 200) return false;

    hash_step(index, step);

    check_hashconflict(index, ++step);
    return true;
}

void HashTable::hash_step(int& index, int step) {
    /*index += 2 * step;
    index += step * step;
    */
    index += 1;
    index %= HASH_SIZE;
}

/*
DEBUG FUNCTION
*/
void HashTable::print_map() {
    for (auto e : data) {
        std::cout << e.first << ": " << e.second.getToken() << std::endl;
    }
}