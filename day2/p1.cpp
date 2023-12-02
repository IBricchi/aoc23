#include <iostream>

int filter_blue = 14, filter_green = 13, filter_red = 12;

int main() {
    // while input is available
    int accumulator = 0;
    int counter = 0;
    while (true) {
        counter++;
        // read one line
        std::string line;
        std::getline(std::cin, line);
        int pos = 0;

        if (line.size() == 0) {
            break;
        }

        // read until second space
        int space_counter = 0;
        while (space_counter < 2) {
            if (line[pos] == ' ') {
                space_counter++;
            }
            pos++;
        }

        // get the data for each section
        int max_blue = 0, max_green = 0, max_red = 0;
        int value = 0;
        while (true) {
            if (pos >= line.size()) {
                break;
            }
            switch(line[pos]) {
                case 'b':
                    pos += 5;
                    max_blue = std::max(max_blue, value);
                    value = 0;
                    break;
                case 'g':
                    pos += 6;
                    max_green = std::max(max_green, value);                    
                    value = 0;
                    break;
                case 'r':
                    pos += 4;
                    max_red = std::max(max_red, value);
                    value = 0;
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    value = value * 10 + (line[pos] - '0');
                    pos++;
                    break;
                default:
                    pos++;
                    break;
            }

        }

        if (max_blue <= filter_blue && max_green <= filter_green && max_red <= filter_red) {
            accumulator += counter;
        }
    }
    std::cout << accumulator << std::endl;
}
