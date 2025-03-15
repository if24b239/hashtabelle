#include <hashtab.h>
#include <iostream>
#include <shares.h>
#include <to_json.h>
#include <ostream>
#include <fstream>
/*STUPID IDE COMMENT
#include "hashtab.cpp"
#include "shares.cpp"*/

void save_to_file(std::string filename, const HashTable& hT) {
    json j = json(hT);

    std::ofstream file(filename);

    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        return;
    }
    std::cout << "\nCOuLdN't OpEN FilE\n";
}

void load_from_file(std::string filename, HashTable& hT) {
    json j;

    std::ifstream file(filename);

    if (file.is_open()) {
        file >> j;
        j.get_to(hT);
        file.close();
        return;
    }
    std::cout << "\nCOuLdN't OpEN FilE\n";
}

int main() {
    // Create a hash table
    HashTable* data = new HashTable();

    // Create some sample shares
    Share apple("Apple Inc.", "AAPL", "865985");
    Share tesla("Tesla Inc.", "TSLA", "A1CX3T");
    Share amazon("Amazon.com", "AMZN", "906866");

    // Add shares to hash table
    data->save_in_map(apple);
    data->save_in_map(tesla);
    data->save_in_map(amazon);

    // Print the hash table contents
    std::cout << "Hash table contents:" << std::endl;
    data->print_map();

    // save info to a file
    save_to_file("./hashtable_files/first.json", *data);

    HashTable* data2 = new HashTable();

    load_from_file("./hashtable_files/first.json", *data2);
    data2->print_map();

    // Example: Find a share by token
    std::string search_token = "AAPL";
    Share* found_share = data2->get_share_from_map(search_token);

    if (found_share != nullptr) {
        std::cout << "\nFound share: " << found_share->getName() << std::endl;

        // Import history from CSV file
        found_share->import_history("HistoricalData_1741869447634.csv");

        // Print share data including sample of history
        found_share->print_share_data();

        found_share->plot_schlusskurse();  // Standard: 30 Tage

    } else {
        std::cout << "\nShare with token " << search_token << " not found" << std::endl;
    }  

    // Clean up
    delete data;
    delete data2;
    return 0;
}