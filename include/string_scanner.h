#pragma once

#include <iostream>
#include <string>
#include <cstring>

class StringScanner {
public:
    StringScanner(const char* str, size_t str_len) : str(str), str_len(str_len), pos(0) {}
    StringScanner(const char* str) : StringScanner(str, strlen(str)) {}
    StringScanner(const std::string& str) : StringScanner(str.c_str(), str.size()) {}

    bool eof() const {return str[pos] == '\0';}
    char next() {return str[pos++];}
    char peek() const {return str[pos];}
    char skip(size_t n) {pos += n; return str[pos - 1];}
    char skip_past(char c) {
        while (str[pos] != c && str[pos] != '\0') {
            pos++;
        }
        if (str[pos] != '\0') {
            pos++;
        }
        return str[pos];
    }

    bool match(const char* s, size_t len) {
        if (pos + len > str_len) {
            return false;
        }
        for (size_t i = 0; i < len; i++) {
            if (str[pos + i] != s[i]) {
                return false;
            }
        }
        return true;
    }
    bool match(const char* s) {return match(s, strlen(s));}
    bool match(const std::string& s) {return match(s.c_str(), s.size());}

    const char* remaining() const {
        return str + pos;
    }

private:
    const char* str;
    const size_t str_len;
    size_t pos;
};
