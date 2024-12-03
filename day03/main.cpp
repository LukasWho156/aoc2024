#include <regex>
#include <iostream>

using namespace std;

int main() {
    int sum = 0;
    auto pattern = regex("(mul\\(\\d{1,3},\\d{1,3}\\)|don\'t\\(\\)|do\\(\\))");
    bool enabled = true;
    for(string input; getline(cin, input);) {
        sregex_iterator it(input.begin(), input.end(), pattern), end;
        for(sregex_iterator i = it; i != end; ++i) {
            smatch match = *i;
            string expr = match.str();
            cout << expr << endl;
            // part 2 stuff
            if(expr.compare("do()") == 0) {
                enabled = true;
                continue;
            }
            if(expr.compare("don\'t()") == 0) {
                enabled = false;
                continue;
            }
            if(!enabled) {
                continue;
            }
            string n1, n2;
            bool flip = false;
            for(auto j = expr.begin() + 4; j != expr.end(); j++) {
                auto c = *j;
                if(c >= 48 && c <= 57) {
                    if(flip == true) {
                        n1 += c;
                    } else {
                        n2 += c;
                    }
                }
                if(c == ',') {
                    flip = true;
                }
            }
            int num1 = stoi(n1), num2 = stoi(n2);
            sum += num1 * num2;
        }
    }
    cout << sum << endl;
    return 0;
}