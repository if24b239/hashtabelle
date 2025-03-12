#include <hashtab.h>
#include <iostream>

#define HASH_SIZE 4

int HashTable::get_hash_index(std::string token) {
    unsigned long hash = 0;
    for (char c : token) {
        hash = hash * 31 + c;
    }

    return hash % HASH_SIZE;  
}

void HashTable::delete_from_map(std::string token) {

    
}

Share* HashTable::search_map(std::string token, int step) {

    /*auto index = get_hash_index(token);

    if (data.find(index) == data.end()) {
        std::cout << "\nShare not found\n";
        return nullptr;
    }

    if (data.at(index).getToken() != token) {
        hash_step(index, step);
        search_map(token, step++);
    }

    return &data.at(index);*/

    int index = get_hash_index(token);

    if () {
        
    }
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
    if (step == HASH_SIZE) return false;

    hash_step(index, step);

    check_hashconflict(index, step++);
    return true;
}

void HashTable::hash_step(int& index, int step) {
    index += 11 * step;
    index += 7 * step * step;
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