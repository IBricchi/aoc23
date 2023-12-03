#include <iostream>

int main() {
    int accumulator = 0;
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        if (line.size() == 0) {
            break;
        }

        int pos = 0;
        int first_digit = 0;
        while (true) {
            if (line[pos] >= '0' && line[pos] <= '9') {
                first_digit = line[pos] - '0';
                break;
            }
            pos++;
        }

        int last_digit = first_digit;
        while (pos < line.size()) {
            if (line[pos] >= '0' && line[pos] <= '9') {
                last_digit = line[pos] - '0';
            }
            pos++;
        }

        accumulator += first_digit * 10 + last_digit;
    }
    std::cout << accumulator << std::endl;
}