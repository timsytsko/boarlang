#include <vector>
#include <utility>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>

#include "h/lexer.hpp"

std::vector<std::string> operators = {"+", "-", "*", "/", "&&", "||", "==", "!=", ">", "<", ">=", "<=", "++", "--"};
std::vector<std::string> keywords = {"main", "var", "func", "return", "continue", "break", "if", "while"};
std::vector<std::string> types = {"int", "float", "char"};
std::vector<std::string> brackets = {"(", ")", "{", "}"};
std::vector<std::string> assignments = {"=", "+=", "-=", "*=", "/="};
std::vector<std::string> separators = {","};
std::vector<std::string> newlines = {";"};

std::vector<std::string> split_string(std::string &str) {
    std::vector<std::string> specials;
    specials.insert(specials.end(), operators.begin(), operators.end());
    specials.insert(specials.end(), brackets.begin(), brackets.end());
    specials.insert(specials.end(), assignments.begin(), assignments.end());
    specials.insert(specials.end(), separators.begin(), separators.end());
    specials.insert(specials.end(), newlines.begin(), newlines.end());
    std::sort(specials.begin(), specials.end());
    std::set<char> delimiters = {' ', '\n', 13};
    std::vector<std::string> res;
    std::string current;
    int i = 0;
    while (i < str.size()) {
        if (delimiters.count(str[i])) {
            if (current != "") {
                res.push_back(current);
                current = "";
            }
            i++;
        } else {
            bool is_special = false;
            for (int j = specials.size(); j >= 0; j--) {
                if (specials[j] == "") continue;
                if (specials[j] == str.substr(i, specials[j].size())) {
                    res.push_back(current);
                    current = "";
                    res.push_back(specials[j]);
                    i += specials[j].size();
                    is_special = true;
                    break;
                }
            }
            if (is_special) continue;
            current.push_back(str[i]);
            i++;
        }
    }
    if (current != "") res.push_back(current);
    return res;
}

bool is_number(std::string &str) {
    if (!str.size()) return false;
    int i = 0;
    if (str[0] == '-') i++;
    int dots = 0;
    for (; i < str.size(); i++) {
        if (str[i] == '.') {
            dots++;
        } else {
            if (str[i] - '0' < 0 || str[i] - '0' > 9) return false;
        }
    }
    return dots < 2;
}

bool is_valid_var(std::string &str) {
    if (48 <= str[0] && str[0] <= 57) return false;
    for (char i : str) {
        bool success = false;
        if (i == '_') success = true;
        if (48 <= i && i <= 57) success = true;
        if (97 <= i && i <= 122) success = true;
        if (!success) return false;
    }
    return true;
}

std::string recognize_tag(std::string &str) {
    if (is_number(str)) return "number";
    if (std::find(operators.begin(), operators.end(), str) != operators.end()) return "operator";
    if (std::find(keywords.begin(), keywords.end(), str) != keywords.end()) return "keyword";
    if (std::find(types.begin(), types.end(), str) != types.end()) return "type";
    if (std::find(brackets.begin(), brackets.end(), str) != brackets.end()) return "bracket";
    if (std::find(assignments.begin(), assignments.end(), str) != assignments.end()) return "assignment";
    if (std::find(separators.begin(), separators.end(), str) != separators.end()) return "separator";
    if (std::find(newlines.begin(), newlines.end(), str) != newlines.end()) return "newline";
    if (is_valid_var(str)) return "var";
    return "error";
}

std::vector<std::pair<std::string, std::string>>  lex(std::vector<std::string> &file_content) {
    std::vector<std::pair<std::string, std::string>> res;
    for (std::string line : file_content) {
        std::vector<std::string> splitted = split_string(line);
        for (std::string s : splitted) {
            if (s == " " || s == "\n" || s == "" || s[0] == 13) continue;
            std::string tag = recognize_tag(s);
            res.push_back(std::make_pair(tag, s));
        }
        res.push_back(std::make_pair("newline", ";"));
    }
    return res;
}