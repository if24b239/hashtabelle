#pragma once

#include <string>
#include <ctime>

/*class Day {
    std::string date;
    double close;
    int volume;
    double open;
    double high;
    double low;

    public:
    Day(std::string value);
};*/

class Share {

    std::string name;
    std::string token;
    std::string wkn;
    //History* history;

    public:
    /// @brief 
    /// @param name 
    /// @param token 
    /// @param wkn 
    Share(std::string name, std::string token, std::string wkn) : name(name), token(token), wkn(wkn) {};

    std::string getToken() { return token; }

    void import_history();
};

/*class History {

    Day history[30];

    public:
    History(Share share);
};*/