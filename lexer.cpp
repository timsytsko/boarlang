#include <vector>
#include <utility>
#include <string>
#include <set>

#include "h/lexer.hpp"

std::vector<std::string> split_string(std::string &str) {
    std::set<char> delimiters = {' ', '\n'};
    std::set<char> key_chars = {'+', '-', '*', '/', '(', ')'};
    std::vector<std::string> res;
    std::string current;
    for (char c : str) {
        if (delimiters.count(c)) {
            if (current != "") {
                res.push_back(current);
                current = "" ;
            }
        } else if (key_chars.count(c)) {
            if (current != "") {
                res.push_back(current);
                current = "";
            }
            current.push_back(c);
            res.push_back(current);
            current = "";
        } else {
            current.push_back(c);
        }
    }
    if (current != "") res.push_back(current);
    return res;
}

std::string recognize_tag(std::string &str) {
    // operator
    if (str == "+" || str == "-" || str == "*" || str == "/") {
        return "op";
    }
    // integer
    bool all_are_digits = true;
    for (char c : str) {
        if (c < 48 || c > 57) {
            all_are_digits = false; break;
        }
    }
    if (all_are_digits) {
        return "int";
    }
    // brackets
    if (str == "(" || str == ")") {
        return "br";
    }
    // unknown
    return "unknown";
}

std::vector<std::pair<std::string, std::string>>  lex(std::vector<std::string> &file_content) {
    std::vector<std::pair<std::string, std::string>> res;
    for (std::string line : file_content) {
        std::vector<std::string> splitted = split_string(line);
        for (std::string s : splitted) {
            res.push_back(std::make_pair(recognize_tag(s), s));
        }
        res.push_back(std::make_pair("nl", ";"));
    }
    return res;
}