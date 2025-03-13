#include <hashtab.h>
#include <iostream>
#include <shares.h>
#include "hashtab.cpp"
#include "shares.cpp"

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

    // Example: Find a share by token
    std::string search_token = "AAPL";
    Share* found_share = data->get_share_from_map(search_token);

    if (found_share != nullptr) {
        std::cout << "\nFound share: " << found_share->getName() << std::endl;

        // Import history from CSV file
        found_share->import_history("HistoricalData_1741869447634.csv");

        // Print share data including sample of history
        found_share->print_share_data();

        found_share->plot_schlusskurse();  // Standard: 30 Tage
        // ODER
    } else {
        std::cout << "\nShare with token " << search_token << " not found" << std::endl;
    }
    Share* found_share2 = data->get_share_from_map(search_token);
    found_share2->print_share_data();


    // Clean up
    delete data;
    return 0;
}