#include <hashtab.h>

int HashTable::get_hash_index(std::string token) {
    unsigned long hash = 0;
    for (char c : token) {
        hash = hash * 31 + c;  // Multiply by prime number and add ASCII value
    }

    // Since you're using std::map, you might not need a modulo operation
    // as the map will handle the storage. But including it for a smaller range.
    return hash % 1000;  // Limiting to a range of 0-999
}