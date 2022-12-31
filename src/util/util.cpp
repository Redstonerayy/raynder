#include "util.hpp"
#include "headers/stl.hpp"

std::vector<std::string> SplitString(std::string stringtosplit, std::string delimiter) {
    std::vector<std::string> parts;        
    size_t pos = 0;
    while ((pos = stringtosplit.find(delimiter)) != std::string::npos) {
        parts.emplace_back(stringtosplit.substr(0, pos));
        stringtosplit.erase(0, pos + delimiter.length());
    }
    if(stringtosplit.length() > 0){
        parts.emplace_back(stringtosplit);
    }
    return parts;
}
