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
    
    //delete data from before the load
    hT.clearData();
    
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

bool options(char& input) {
    std::cout 
    << "0. QUIT: quit program" << std::endl
    << "1. ADD: add a share with name, wkn and token" << std::endl
    << "2. DEL: delete share" << std::endl
    << "3. IMPORT: import share history by .csv" << std::endl
    << "4. SEARCH: search for share by token" << std::endl
    << "5. PLOT: plot share history of last 30 days" << std::endl
    << "6. SAVE: save to json file" << std::endl
    << "7. LOAD: load from json file" << std::endl;

    std::cin >> input;

    if (input == '0') return false;
    return true;
}

void add(HashTable* hT) {
    Share to_add;

    std::cout << "Name: ";
    std::cin >> to_add.name;
    std::cout << "WKN: ";
    std::cin >> to_add.wkn;
    std::cout << "Token: ";
    std::cin >> to_add.token;
    std::cout << std::endl;

    hT->save_in_map(to_add);
}

void del(HashTable* hT) {

    std::string token;

    std::cout << "\nInput token to delete: ";
    std::cin >> token;
    std::cout << std::endl;

    hT->delete_from_map(token);
}

void import(HashTable* hT) {

    std::string token;
    std::string file;

    std::cout << "Input token to add history to: ";
    std::cin >> token;

    Share* to_fill = hT->get_share_from_map(token);
    
    if (to_fill == nullptr) return;

    std::cout << "File in .csv format: ";
    std::cin >> file;

    if (!to_fill->import_history(file)) return;

    std::cout << "\nImported data";
    std::cout << std::endl;
}

void search(HashTable* hT) {

    std::string token;

    std::cout << "\nSearch for share by token: ";
    std::cin >> token;
    std::cout << std::endl;

    Share* to_read = hT->get_share_from_map(token);

    if (to_read == nullptr) return;

    std::cout 
    << "Token: " << to_read->getToken() << std::endl
    << "Name: " << to_read->getName() << std::endl
    << "WKN: " << to_read->wkn << std::endl << std::endl;

    if (to_read->history.size() == 0) {
        std::cout << "NO HISTORY" << std::endl;
        return;
    };

    std::cout
    << "Date: " << to_read->history[0].date << std::endl
    << "Close: " << to_read->history[0].close << std::endl
    << "Volume: " << to_read->history[0].volume << std::endl
    << "Open: " << to_read->history[0].open << std::endl
    << "High: " << to_read->history[0].high << std::endl
    << "Low: " << to_read->history[0].low << std::endl << std::endl;
}

void plot(HashTable* hT) {
    
    std::string token;

    std::cout << "\nSearch for share by token: ";
    std::cin >> token;
    std::cout << std::endl;

    Share* to_read = hT->get_share_from_map(token);

    if (to_read == nullptr) return;

    to_read->plot_schlusskurse();

    std::cout << std::endl;
}

void save(HashTable* hT) {

    std::string file_name;

    std::cout << "\nSave Data in file: ";
    std::cin >> file_name;
    std::cout << std::endl;

    save_to_file("./hashtable_files/" + file_name, *hT);

    std::cout << "SAVED TO FILE: " << file_name << std::endl << std::endl;
}

void load(HashTable* hT) {

    std::string file_name;

    std::cout << "\nLoad Data from file: ";
    std::cin >> file_name;
    std::cout << std::endl;

    load_from_file("./hashtable_files/" + file_name, *hT);

    std::cout << "LOADED FROM FILE: " << file_name << std::endl << std::endl;
}

int main() {

    char input;

    HashTable* data = new HashTable();

    while (options(input)) {

        switch (input) {
            case '1':
                add(data);
                break;
            case '2':
                del(data);
                break;
            case '3':
                import(data);
                break;
            case '4':
                search(data);
                break;
            case '5':
                plot(data);
                break;
            case '6':
                save(data);
                break;
            case '7':
                load(data);
                break;
            default:
                std::cout << "\nINVALID INPUT\n";
        }
    }

    delete data;
 /*
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
    */
}