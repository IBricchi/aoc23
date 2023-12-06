#include <iostream>
#include <string>
#include <string_scanner.h>

#include <vector>
#include <deque>

#include <cstdint>

struct Range {
    uint64_t start;
    uint64_t end;

    // overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const Range& range) {
        os << "{" << range.start << " - " << range.end << "}";
        return os;
    }

    // overload the | operator
    friend Range operator|(const Range& range, const Range& other) {
        uint64_t start = std::min(range.start, other.start);
        uint64_t end = std::max(
            range.end == static_cast<uint64_t>(-1) ? 0 : range.end,
            other.end == static_cast<uint64_t>(-1) ? 0 : other.end
        );
        return {start, end};
    }
};

int main() {
    // load the seed
    std::string line;
    std::getline(std::cin, line);
    StringScanner scanner(line);
    scanner.skip_past(' ');

    std::deque<Range> vals;
    while (!scanner.eof()) {
        uint64_t start_range = 0;
        while (scanner.peek() != ' ' && !scanner.eof()) {
            start_range = start_range * 10 + scanner.next() - '0';
        }
        scanner.next();
        uint64_t length = 0;
        while (scanner.peek() != ' ' && !scanner.eof()) {
            length = length * 10 + scanner.next() - '0';
        }
        scanner.next();
        vals.push_back({start_range, start_range + length});
    }

    // std::cout << "Initial ranges: ";
    // for (auto val : vals) {
    //     std::cout << val << " ";
    // }
    // std::cout << std::endl;
    
    // while we have input data
    while (true) {
        // firs twe skip any empty lines
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        // std::cout << "----------------------\n";

        // we skip one line
        std::getline(std::cin, line);

        int original_vals_size = vals.size();
        std::vector<Range> found_vals(original_vals_size, {static_cast<uint64_t>(-1), static_cast<uint64_t>(-1)});
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
            // std::cout << "Currently looking at r/ange: " << source_start << " - " << source_start + length << " -> " << dest_start << std::endl;
            for (int i = 0; i < original_vals_size; i++) {
                Range range = vals[i];
                // std::cout << "Range: " << range << std::endl;
                // if fully contained
                if (source_start <= range.start && range.end < source_start + length) {
                    vals.push_back({dest_start + range.start - source_start, dest_start + range.end - source_start});
                    // std::cout << "FULL: Value: " << range << " was found in range: " << source_start << " - " << source_start + length << " and translated to: " << vals.back() << std::endl;
                    found_vals[i] = found_vals[i] | range;
                }
                // if left side is contained
                else if (source_start < range.end && range.end < source_start + length) {
                    vals.push_back({dest_start, dest_start + range.end - source_start});
                    // std::cout << "LEFT: Value: " << range << " was found in range: " << source_start << " - " << source_start + length << " and translated to: " << vals.back() << std::endl;
                    found_vals[i] = found_vals[i] | Range{source_start, range.end};
                }
                // if right side is contained
                else if (source_start <= range.start && range.start < source_start + length) {
                    vals.push_back({dest_start + range.start - source_start, dest_start + length});
                    // std::cout << "RIGTH: Value: " << range << " was found in range: " << source_start << " - " << source_start + length << " and translated to: " << vals.back() << std::endl;
                    found_vals[i] = found_vals[i] | Range{range.start, source_start + length};
                }
            }
            if (!std::getline(std::cin, line)) {
                line = "";
            }
        }

        for (int i = 0; i < original_vals_size; i++) {
            if (found_vals[i].start == static_cast<uint64_t>(-1)) {
                // std::cout << "Value: " << vals.front() << " was not found in any range and was copied" << std::endl;
                vals.push_back(vals.front());
            }
            else {
                // check if the range is to the left
                if (found_vals[i].start > vals.front().start) {
                    // std::cout << "Value: " << vals.front() << " was not found in any range and was copied" << std::endl;
                    vals.push_back({vals.front().start, found_vals[i].start});
                }
                else if (vals.front().end > found_vals[i].end) {
                    // std::cout << "Value: " << vals.front() << " was not found in any range and was copied" << std::endl;
                    vals.push_back({found_vals[i].end, vals.front().end});
                }
                else {
                    // std::cout << "Value: " << vals.front() << " was found in range: " << found_vals[i] << std::endl;
                }
            }
            vals.pop_front();
        }

        // std::cout << "Ranges after iteration: ";
        // for (auto val : vals) {
            // std::cout << val << " ";
        // }
        // std::cout << std::endl;
    }
    uint64_t min_value = vals.front().start;
    for (auto val : vals) {
        min_value = std::min(min_value, val.start);
    }
    std::cout << min_value << std::endl;
}