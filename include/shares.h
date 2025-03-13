#pragma once

#include <string>
#include <vector>

// A simple struct to store daily stock data
struct Day {
    std::string date;
    double close;
    int volume;
    double open;
    double high;
    double low;

    // Simple constructor
    Day() {};
    Day(std::string d, double c, int v, double o, double h, double l) :
        date(d), close(c), volume(v), open(o), high(h), low(l) {}
};

class Share {
public:  
    std::string name;
    std::string token;
    std::string wkn;

    // Vector to store the history of days
    std::vector<Day> history;
    Share() {};
    /// @brief Constructor for a Share
    /// @param name 
    /// @param token 
    /// @param wkn 
    Share(std::string name, std::string token, std::string wkn) :
        name(name), token(token), wkn(wkn) {};

    // Get the token (ticker symbol)
    std::string getToken() { return token; }

    // Get the name
    std::string getName() { return name; }

    // Get the history
    std::vector<Day>& getHistory() { return history; }

    // Import history from a CSV file
    bool import_history(const std::string& filename);

    // Print the share data (for debugging)
    void print_share_data();
};