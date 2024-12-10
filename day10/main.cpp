#include <iostream>
#include <vector>
#include <unordered_map>

#include "../shared/vec2.h"
#include "../shared/map2d.h"

/*
I thought yesterday's part 2 was simple, but this one takes the icing on the cake.
*/

int ascend(Map2D<int>& height_map, Map2D<bool>& visited, vec2 pos, int height) {
    if(height_map.at(pos) != height) {
        return 0;
    }
    // okay, this is funny. accidentally solved part 2 before part 1 because
    // I didn't think about multiple tracks leading to the same peak being
    // counted only once.
    //if(visited.at(pos)) {
    //    return 0;
    //}
    visited.set(pos, true);
    if(height == 9) {
        return 1;
    }
    //std::cout << "Ascend to height " << height << " at ";
    //print_vec(pos);
    vec2 dir { 0, 1 };
    int sum = 0;
    for(int i = 0; i < 4; i++) {
        sum += ascend(height_map, visited, pos + dir, height + 1);
        dir = rotate90(dir);
    }
    return sum;
}

int main() {
    std::vector<std::string> input;
    for(std::string line; std::getline(std::cin, line);) {
        input.push_back(line);
    }
    std::unordered_map<char, int> heights;
    for(char c = '0'; c <= '9'; c++) {
        heights[c] = c - '0';
    }
    Map2D<int> height_map(input, heights, -1, -1);
    auto trailheads = height_map.find(0);
    int sum = 0;
    for(auto th = trailheads.begin(); th != trailheads.end(); th++) {
        Map2D<bool> visited(input[0].size(), input.size(), false, false);
        sum += ascend(height_map, visited, *th, 0);
    }
    std::cout << sum << std::endl;
}