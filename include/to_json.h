#pragma once

#include <hashtab.h>
#include <shares.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void from_json(const json& j, Day& day);
void to_json(json& j, const Day& day);
void to_json(json& j, const Share& share);
void from_json(const json& j, Share& share);
void to_json(json& j, const HashTable& hT);
void from_json(const json& j, HashTable& hT);