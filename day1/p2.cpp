#include <iostream>

#include <string_scanner.h>

static const char* string_digits[] = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int main() {
    int accumulator = 0;
   
    while(true) {
        std::string line;
        std::getline(std::cin, line);

        if (line.size() == 0) {
            break;
        }

        StringScanner scanner(line);

        int first_digit = 0;
        int reps = 0;
        while (true) {
            if (scanner.eof()) { exit(1); }
            bool found = false;
            for (int i = 0; i < 10; i++) {
                if (scanner.match(string_digits[i])) {
                    first_digit = i;
                    found = true;
                    break;
                }
                if (scanner.match(string_digits[i+10])) {
                    first_digit = i;
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
            scanner.next();
        }

        int last_digit = first_digit;
        while (!scanner.eof()) {
            bool found = false;
            for (int i = 0; i < 10; i++) {
                if (scanner.match(string_digits[i])) {
                    last_digit = i;
                    found = true;
                    break;
                }
                if (scanner.match(string_digits[i+10])) {
                    last_digit = i;
                    found = true;
                    break;
                }
            }
            scanner.next();
        }

        accumulator += first_digit * 10 + last_digit;
    }

    std::cout << accumulator << std::endl;
}