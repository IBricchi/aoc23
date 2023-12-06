#include <string_scanner.h>
#include <vector>
#include <deque>

int main() {
    int acc = 0;
    std::deque<int> multipliers = {1};
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) break;

        StringScanner scanner(line);
        scanner.skip_past(' ');
        scanner.skip_past(' ');

        std::vector<int> vals;
        while (scanner.peek() != '|') {
            int new_val = 0;
            while (scanner.peek() != ' ') {
                new_val = new_val * 10 + scanner.next() - '0';
            }
            vals.push_back(new_val);
            scanner.skip_past(' ');
        }
        scanner.next();
        scanner.skip_past(' ');

        int matches = 0;
        while (!scanner.eof()) {
            int new_val = 0;
            while (scanner.peek() != ' ' && !scanner.eof()) {
                new_val = new_val * 10 + scanner.next() - '0';
            }
            scanner.skip_past(' ');
            if (std::find(vals.begin(), vals.end(), new_val) != vals.end()) {
                matches++;
            }
        }
        int multiplier = multipliers.front();
        multipliers.pop_front();
        if (multipliers.empty()) {
            multipliers.push_back(1);
        }
        else {
            multipliers[0]++;
        }

        acc += multiplier;
        for(int i = 0; i < matches; i++) {
            if (multipliers.size() <= i) {
                multipliers.push_back(multiplier);
            }
            else {
                multipliers[i] += multiplier;
            }
        }
    }
    std::cout << acc << std::endl;
}