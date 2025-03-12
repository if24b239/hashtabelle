#include <hashtab.h>

int HashTable::get_hash_index(std::string token) {
    unsigned long hash = 0;
    for (char c : token) {
        hash = hash * 31 + c;
    }

    return hash % 100;  
}