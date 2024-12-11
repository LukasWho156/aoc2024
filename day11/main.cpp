#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

/*
looks like something that scales exponentially with no of steps,
but let's still try an naive approach first.

yup, part 2 definitely doesn't work with a naive approach. Let's
think about this.

maybe it's enough to calculate duplicates at the same time? Let's
try.

yup! Took ~ half a second. very nice!
*/

void increment(std::unordered_map<long, long>& input, long no, long amount = 1) {
    if(input.find(no) != NULL) {
        input[no] += amount;
    } else {
        input[no] = amount;
    }
}

int main() {
    //std::vector<long> input;
    std::unordered_map<long, long> input;
    for(std::string no_s; std::getline(std::cin, no_s, ' '); ) {
        long no = std::stol(no_s);
        increment(input, no);
    }
    // at least for part one it doesn't matter if stones shift,
    // so let's just append them to the end of the array and
    // hope there are no surprises in part 2
    for(int i = 0; i < 75; i++) {
        std::unordered_map<long, long> buffer;
        for(auto pair = input.begin(); pair != input.end(); pair++) {
            auto no = pair->first;
            auto amount = pair->second;
            if(amount == 0) {
                continue;
            }
            if(no == 0) {
                increment(buffer, 1, amount);
                continue;
            }
            long lg = std::log10(no);
            if((lg % 2) == 0) {
                increment(buffer, no * 2024, amount);
                continue;
            }
            long split = std::pow(10, (lg + 1) / 2);
            increment(buffer, no / split, amount);
            increment(buffer, no % split, amount);
        }
        input = buffer;
    }
    long sum = 0;
    for(auto pair = input.begin(); pair != input.end(); pair++) {
        sum += pair->second;
    }
    std::cout << sum << std::endl;
    return 0;
}