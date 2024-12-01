#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void bubble_sort(vector<int>& list) {
    for(int i = 0; i < list.size(); i++) {
        for(int j = i + 1; j < list.size(); j++) {
            if(list[i] > list[j]) {
                swap(list[i], list[j]);
            }
        }
    }
}

int main() {
    vector<int> list1;
    vector<int> list2;
    for(std::string line; std::getline(std::cin, line);) {
        istringstream input;
        input.str(line);
        string p1, p2;
        getline(input, p1, ' ');
        while(getline(input, p2, ' ')) {
            // noop
        }
        list1.push_back(stoi(p1));
        list2.push_back(stoi(p2));
    }
    bubble_sort(list1);
    bubble_sort(list2);
    /*
    // part 1
    int diff = 0;
    for(int i = 0; i < list1.size(); i++) {
        diff += abs(list2[i] - list1[i]);
    }
    cout << diff << endl;
     */
    // part 2
    // there might be some smarter data structure for this, but meh.
    int j = 0;
    int score = 0;
    int prev_val = 0;
    int prev_score = 0;
    for(int i = 0; i < list1.size(); i++) {
        if(list1[i] == prev_val) {
            score += prev_score;
        } else {
            prev_val = list1[i];
            prev_score = 0;
            while(list1[i] >= list2[j]) {
                if(list1[i] == list2[j]) {
                    prev_score += list1[i];
                }
                j += 1;
                if(j >= list2.size()) {
                    j -= 1;
                    break;
                }
            }
            score += prev_score;
        }
    }
    cout << score << endl;
    return 0;
} 