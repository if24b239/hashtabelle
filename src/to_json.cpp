#include <to_json.h>

/**
 * 
 * DAY JSON CONVERSION
 * 
 */
void to_json(json& j, const Day& day) {
    j = json{
        {"date", day.date},
        {"close", day.close},
        {"volume", day.volume},
        {"open", day.open},
        {"high", day.high},
        {"low", day.low}
    };
}

void from_json(const json& j, Day& day) {
    j.at("date").get_to(day.date);
    j.at("close").get_to(day.close);
    j.at("volume").get_to(day.volume);
    j.at("open").get_to(day.open);
    j.at("high").get_to(day.high);
    j.at("low").get_to(day.low);
}

/**
*
* SHARE JSON CONVERSION
*
*/
void to_json(json& j, const Share& share) {
    j = json{
        {"name", share.name},
        {"wkn", share.wkn},
        {"token", share.token},
        {"history", share.history}
    };
}

void from_json(const json& j, Share& share) {
    j.at("name").get_to(share.name);
    j.at("wkn").get_to(share.wkn);
    j.at("token").get_to(share.token);
    j.at("history").get_to(share.history);
}

/**
 * 
 * HASHTABLE JSON CONVERSION
 * 
 */
void to_json(json& j, const HashTable& hT) {
    j = json::array();
    for (const auto& s : hT.getData()) {
        j.push_back(s.second);
    }
};

void from_json(const json& j, HashTable& hT) {
    for (const auto& item : j) {
        Share share = item.get<Share>();
        hT.save_in_map(share);
    }
}