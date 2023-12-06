#include <string_scanner.h>
#include <vector>

int main() {
    int acc = 0;
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

        int points = 0;
        int next_points = 1;
        while (!scanner.eof()) {
            int new_val = 0;
            while (scanner.peek() != ' ' && !scanner.eof()) {
                new_val = new_val * 10 + scanner.next() - '0';
            }
            scanner.skip_past(' ');
            if (std::find(vals.begin(), vals.end(), new_val) != vals.end()) {
                points = (points == 0) ? 1 : points * 2;
            }
        }
        acc += points;
    }
    std::cout << acc << std::endl;
}