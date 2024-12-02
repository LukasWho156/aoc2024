#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool is_safe(vector<int>& input, int depth = 0) {
    int prev = input[0];
    int dir = 0;
    for(int i = 1; i < input.size(); i++) {
        int cur = input[i];
        int diff = cur - prev;
        if(abs(diff) > 3 || diff == 0) {
            if(depth == 0) {
                return false;
            }
            // part 2 stuff
            for(int j = 0; j < input.size(); j++) {
                vector<int> copy(input);
                copy.erase(copy.begin() + j);
                if(is_safe(copy, depth - 1)) {
                    return true;
                }
            }
            return false;
        }
        if(dir != 0) {
            if(dir * diff <= 0) {
                if(depth == 0) {
                    return false;
                }
                // part 2 stuff
                for(int j = 0; j < input.size(); j++) {
                    vector<int> copy(input);
                    copy.erase(copy.begin() + j);
                    if(is_safe(copy, depth - 1)) {
                        return true;
                    }
                }
                return false;
            }
        }
        dir = diff;
        prev = cur;
    }
    return true;
}

int main() {
    int count = 0;
    for(string line; getline(cin, line); ) {
        istringstream input(line);
        vector<int> vec;
        for(string no; getline(input, no, ' '); ) {
            vec.push_back(stoi(no));
        }
        if(is_safe(vec, 1)) {
            count += 1;
        }
    }
    cout << count << endl;
}