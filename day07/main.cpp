#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

bool is_solvable(long target, std::vector<long>& items) {
    std::cout << target << ": ";
    for(auto item = items.begin(); item != items.end(); item++) {
        std::cout << *item << ", ";
    }
    std::cout << std::endl;
    if(items.size() == 1) {
        return items[0] == target;
    }
    long cur = items[items.size() - 1];
    if(cur > target) {
        return false;
    }
    items.pop_back();
    if(target % cur == 0) {
        if(is_solvable(target / cur, items)) {
            return true;
        }
    }
    long log = std::log10(cur);
    long shift = std::pow(10, log + 1);
    if(((target - cur) % shift) == 0) {
        std::cout << "possible candidate: " << shift << ", " << cur << std::endl;
        if(is_solvable((target - cur) / shift, items)) {
            return true;
        }
    }
    if(is_solvable(target - cur, items)) {
        return true;
    }
    items.push_back(cur);
    return false;
}

int main() {
    long sum = 0;
    for(std::string line; std::getline(std::cin, line);) {
        std::istringstream line_stream(line);
        std::string s_target;
        std::getline(line_stream, s_target, ' ');
        long target = stol(s_target);
        std::vector<long> items;
        for(std::string s_item; std::getline(line_stream, s_item, ' ');) {
            items.push_back(stol(s_item));
        }
        if(is_solvable(target, items)) {
            sum += target;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}