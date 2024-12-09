#include <vector>
#include <iostream>

char get_char_at(std::vector<std::string>& input, int x, int y) {
    if(x < 0 || y < 0 || x >= input[0].size() || y >= input.size()) {
        return '?';
    }
    return input[y][x];
}

bool directed_word_serach(std::vector<std::string>& input, std::string& searchstr, int x, int y, int dx, int dy) {
    for(int i = 0; i < searchstr.size(); i++) {
        if(get_char_at(input, x + i * dx, y + i * dy) != searchstr[i]) {
            return false;
        }
    }
    return true;
}

int word_search(std::vector<std::string>& input, std::string& searchstr, int x, int y) {
    int matches = 0;
    for(int dy = -1; dy <= 1; dy++) {
        for(int dx = -1; dx <= 1; dx++) {
            if(directed_word_serach(input, searchstr, x, y, dx, dy)) {
                matches++;
            }
        }
    }
    return matches;
}

int x_word_search(std::vector<std::string>& input, std::string& searchstr, int x, int y) {
    int matches = 0;
    for(int dy = -1; dy <= 1; dy += 2) {
        for(int dx = -1; dx <= 1; dx += 2) {
            if(!directed_word_serach(input, searchstr, x, y, dx, dy)) {
                continue;
            }
            if(directed_word_serach(input, searchstr, x + 2 * dx, y, -dx, dy)) {
                matches++;
            }
            if(directed_word_serach(input, searchstr, x, y + 2 * dy, dx, -dy)) {
                matches++;
            }
        }
    }
    return matches;
}

int main() {
    std::vector<std::string> input;
    std::string pattern("MAS"); // part1: "XMAS"
    for(std::string line; getline(std::cin, line);) {
        input.push_back(line);
    }
    int total = 0;
    for(int y = 0; y < input.size(); y++) {
        for(int x = 0; x < input[0].size(); x++) {
            total += x_word_search(input, pattern, x, y); // part1: word_search
        }
    }
    std::cout << (total / 2) << std::endl;
}