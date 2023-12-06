#include <iostream>
#include <string>
#include <string_scanner.h>

#include <vector>
#include <deque>

#include <cstdint>

int main() {
    // load the seed
    std::string line;
    std::getline(std::cin, line);
    StringScanner scanner(line);
    scanner.skip_past(' ');

    std::deque<uint64_t> vals;
    while (!scanner.eof()) {
        int new_val = 0;
        while (scanner.peek() != ' ' && !scanner.eof()) {
            new_val = new_val * 10 + scanner.next() - '0';
        }
        scanner.next();
        vals.push_back(new_val);
    }
    
    // while we have input data
    while (true) {
        // firs twe skip any empty lines
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        // we skip one line
        std::getline(std::cin, line);

        int original_vals_size = vals.size();
        std::vector<bool> found_vals(original_vals_size, false);
        while (!line.empty()) {
            StringScanner scanner(line);
            uint64_t dest_start = 0;
            while (scanner.peek() != ' ') {
                dest_start = dest_start * 10 + scanner.next() - '0';
            }
            scanner.next();
            uint64_t source_start = 0;
            while (scanner.peek() != ' ') {
                source_start = source_start * 10 + scanner.next() - '0';
            }
            scanner.next();
            uint64_t length = 0;
            while (!scanner.eof()) {
                length = length * 10 + scanner.next() - '0';
            }
            // std::cout << "Currently looking at range: " << source_start << " - " << source_start + length << " -> " << dest_start << std::endl;
            for (int i = 0; i < original_vals_size; i++) {
                if (source_start <= vals[i] && vals[i] < source_start + length) {
                    // std::cout << "Value: " << vals[i] << " was found in range: " << source_start << " - " << source_start + length << " and translated to: " << dest_start + vals[i] - source_start << std::endl;
                    vals.push_back(dest_start + vals[i] - source_start);
                    found_vals[i] = true;
                }
            }
            if (!std::getline(std::cin, line)) {
                line = "";
            }
        }

        for (int i = 0; i < original_vals_size; i++) {
            if (!found_vals[i]) {
            //     std::cout << "Value: " << vals.front() << " was not found in any range and was copied" << std::endl;
                vals.push_back(vals.front());
            }
            vals.pop_front();
        }
    }
    uint64_t min_value = vals.front();
    for (auto val : vals) {
        min_value = std::min(min_value, val);
    }
    std::cout << min_value << std::endl;
}