#include <iostream>
#include <vector>

struct NumberEntry {
    int value;
    int x1, x2;
    int y;

    NumberEntry(int value, int x1, int x2, int y) : value(value), x1(x1), x2(x2), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const NumberEntry& entry) {
        os << "NumberEntry(" << entry.value << ", " << entry.x1 << ", " << entry.x2 << ", " << entry.y << ")";
        return os;
    }
};

struct Symbol {
    char symbol;
    int x, y;
    Symbol(char symbol, int x, int y) : symbol(symbol), x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& os, const Symbol& coord) {
        os << "Coordinate(" << coord.x << ", " << coord.y << ")";
        return os;
    }
};

int main() {
    std::vector<NumberEntry> entries;
    std::vector<Symbol> symbols;

    int y = 0;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        if (line.size() == 0) {
            break;
        }

        int value_start = 0;
        int value = -1;
        for(int i = 0; i < line.size(); i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                if (value == -1) {
                    value = 0;
                    value_start = i;
                }
                value = value * 10 + (line[i] - '0');
            }
            else if (value != -1) {
                entries.push_back(NumberEntry(value, value_start, i-1, y));
                value = -1;
            }

            if ((line[i] < '0' || line[i] > '9') && line[i] != '.') {
                symbols.push_back(Symbol(line[i], i, y));
            }
        }
        if (value != -1) {
            entries.push_back(NumberEntry(value, value_start, line.size() - 1, y));
        }
        
        y++;
    }

    int accumulator = 0;
    for (Symbol &symbol : symbols) {
        if (symbol.symbol != '*') {
            continue;
        }

        int neighbour_count = 0;
        int neighbour_ratio = 1;
        for (NumberEntry &entry : entries) {
            if (symbol.x < entry.x1 - 1 || symbol.x > entry.x2 + 1) {
                continue;
            }
            if (symbol.y < entry.y - 1 || symbol.y > entry.y + 1) {
                continue;
            }
            neighbour_count++;
            if (neighbour_count > 2) {
                break;
            }
            neighbour_ratio *= entry.value;
        }
        if (neighbour_count == 2) {
            accumulator += neighbour_ratio;
        }
    }

    std::cout << accumulator << std::endl;
}
