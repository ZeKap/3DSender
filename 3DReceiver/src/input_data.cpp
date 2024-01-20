#include "input_data.hpp"

std::vector<std::string> getKeys(std::uint32_t buttons) {
    std::vector<std::string> keys;
    for(auto i = s_keys.begin(); i != s_keys.end(); i++) {
        if(i->second & buttons) {
            keys.push_back(i->first);
        }
    }
    return keys;
}
