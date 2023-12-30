#include <iostream>
#include <string>
#include <vector>

#include "h/reader.hpp"
#include "h/lexer.hpp"
#include "h/parser.hpp"

int main() {
    std::string path_to_file = "code/main.brl";
    std::vector<std::string> file_content = read_file_content(path_to_file);
    std::vector<std::pair<std::string, std::string>> lexed = lex(file_content);
    std::vector<BinaryTree> parsed = parse(lexed);
    // for (int i = 0 ; i < parsed[0].get_len(); i++) {
    //     std::pair<std::string, std::string> child = parsed[0].get_element(i);
    //     std::pair<std::string, std::string> parent = parsed[0].get_element(parsed[0].get_parent(i));
    //     std::cout << "child: " << child.second << ", parent: " << parent.second << "\n";
    // }
    std::cout << '\n';
}