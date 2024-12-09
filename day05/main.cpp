#include <vector>
#include <iostream>
#include <algorithm>

struct pg_order {
    int first;
    int second;
} ;

pg_order str_to_pg_order(std::string& input) {
    pg_order ord;
    std::string s1 = input.substr(0, 2);
    std::string s2 = input.substr(3, 2);
    ord.first = stoi(s1);
    ord.second = stoi(s2);
    return ord;
}

std::vector<int> str_to_pg_vec(std::string& input) {
    std::vector<int> vec;
    std::string cur = "";
    for(int i = 0; i < input.size(); i++) {
        if(input[i] == ',') {
            vec.push_back(stoi(cur));
            cur = "";
            continue;
        }
        cur += input[i];
    }
    vec.push_back(stoi(cur));
    return vec;
}

bool is_well_ordered(std::vector<int> input, std::vector<pg_order> order_list) {
    int indices[100];
    std::fill(std::begin(indices), std::end(indices), 0);
    for(int i = 0; i < input.size(); i++) {
        indices[input[i]] = i + 1;
    }
    for(int i = 0; i < order_list.size(); i++) {
        int i1 = indices[order_list[i].first], i2 = indices[order_list[i].second];
        if(i1 > 0 && i2 > 0 && i1 > i2) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<pg_order> orders;
    for(std::string line; getline(std::cin, line);) {
        if(line.empty()) {
            break;
        }
        orders.push_back(str_to_pg_order(line));
    }
    auto sort_fn = [orders](int a, int b) {
        for(int i = 0; i < orders.size(); i++) {
            if(a == orders[i].first && b == orders[i].second) {
                return true;
            }
            if(a == orders[i].second && b == orders[i].first) {
                return false;
            }
        }
        return false;
    };
    /*
    // debugging
    for(int i = 0; i < orders.size(); i++) {
        std::cout << orders[i].first << " < " << orders[i].second << std::endl;
    }
    */
    int sum = 0;
    int sum2 = 0;
    for(std::string line; getline(std::cin, line);) {
        auto input = str_to_pg_vec(line);
        if(!is_well_ordered(input, orders)) {
            std::sort(input.begin(), input.end(), sort_fn);
            sum2 += input[input.size() / 2];
            continue;
        }
        sum += input[input.size() / 2];
    }
    std::cout << sum << ", " << sum2 << std::endl;
    return 0;
}