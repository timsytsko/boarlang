#include <iostream>
#include <string>
#include <vector>

#include "h/reader.hpp"
#include "h/lexer.hpp"
#include "h/parser.hpp"

int main() {
    std::vector<std::string> file_content = read_file_content("code/main.brl");
    std::vector<std::pair<std::string, std::string>> lexed = lex(file_content);
    // std::vector<std::vector<std::pair<int, int>>> parsed = parse(lexed);
    for (auto s : lexed)  {
        std::cout << s.first << ' ' << s.second << std::endl;
    }
    std::cout << '\n';
}