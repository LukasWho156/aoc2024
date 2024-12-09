#include <iostream>
#include <unordered_map>
#include <vector>

#include "../shared/vec2.h"
#include "../shared/map2d.h"

/*
except for some wresting with templates in header files,
this one was very straightforward.
*/

int main() {
    std::unordered_map<char, std::vector<vec2>> positions;
    std::vector<char> chars;
    int width, height;
    int y = 0;
    for(std::string line; std::getline(std::cin, line);) {
        int x = 0;
        for(auto c_it = line.begin(); c_it != line.end(); c_it++) {
            char c = *c_it;
            if(c == '.') {
                x++;
                continue;
            }
            auto list = positions.find(c);
            if(list == positions.end()) {
                chars.push_back(c);
                std::vector<vec2> new_list;
                positions[c] = new_list;
                list = positions.find(c);
            }
            (list->second).push_back(vec2 {x, y});
            x++;
        }
        width = x;
        y++;
    }
    height = y;
    Map2D<bool> antinodes (width, height, false, false);
    for(auto c_it = chars.begin(); c_it != chars.end(); c_it++) {
        char c = *c_it;
        auto list = positions.find(c)->second;
        for(auto i = list.begin(); i != list.end(); i++) {
            for(auto j = list.begin(); j != list.end(); j++) {
                if(i == j) {
                    continue;
                }
                vec2 diff = *i - *j;
                for(vec2 target = *i; !antinodes.out_of_bounds(target); target += diff) {
                    antinodes.set(target, true);
                }   
            }
        }
    }
    std::cout << antinodes.count(true) << std::endl;
    return 0;
}