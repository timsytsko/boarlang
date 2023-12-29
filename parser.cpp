#include <vector>
#include <string>

#include "h/parser.hpp"
#include <iostream>

int BinaryTree::get_len() {
    return this->len;
}

void BinaryTree::add_element(std::pair<std::string, std::string> element) {
    this->elements.push_back(element);
    this->parents.push_back(len);
    this->children.push_back(std::make_pair(-1, -1));
    this->len++;
}

void BinaryTree::set_relative(int child, int parent) {
    this->parents[child] = parent;
    if (this->children[parent].first != -1) {
        this->children[parent].first = child;
    } else {
        this->children[parent].second = child;
    }
}

int BinaryTree::get_parent(int child) {
    return this->parents[child];
}

std::pair<int, int> BinaryTree::get_children(int parent) {
    return this->children[parent];
}

std::pair<std::string, std::string> BinaryTree::get_element(int index) {
    return this->elements[index];
}

int BinaryTree::find_root() {
    for (int i = 0; i < this->len; i++) {
        if (parents[i] == i) return i;
    }
    return -1;
}

std::vector<std::vector<std::pair<std::string, std::string>>> split_vector_by_nl(std::vector<std::pair<std::string, std::string>> &lexed) {
    std::vector<std::vector<std::pair<std::string, std::string>>> res;
    std::vector<std::pair<std::string, std::string>> current;
    for (std::pair<std::string, std::string> element : lexed) {
        if (element.first == "nl") {
            if (current.size() > 0) {
                res.push_back(current); current = {};
            }
        } else {
            current.push_back(element);
        }
    }
    return res;
}

std::vector<BinaryTree> parse(std::vector<std::pair<std::string, std::string>> &lexed) {
    std::vector<BinaryTree> res;
    for (std::vector<std::pair<std::string, std::string>> line : split_vector_by_nl(lexed)) {
        BinaryTree btree;
        int last_handled = 0;
        btree.add_element(line[0]);
        for (int i = 1; i < line.size(); i++) {
            if (line[i].first == "int") {
                // int
                btree.add_element(line[i]);
                btree.set_relative(i, last_handled); last_handled = i;
            } else if (line[i].first == "br") {
                // br
                if (line[i].second == "(") {
                    btree.add_element(std::make_pair("br", "()"));
                    btree.set_relative(i, last_handled); last_handled = i;
                } else if (line[i].second == ")") {
                    while (btree.get_element(last_handled).first != "br") {
                        last_handled = btree.get_parent(last_handled);
                    }
                    last_handled = btree.get_parent(last_handled);
                }
            } else if (line[i].first == "op") {
                // op
                if (line[i].second == "+" || line[i].second == "-") {
                    if (btree.get_element(last_handled).first == "int") {
                        if (btree.get_element(btree.get_parent(last_handled)).first == "op") {
                            if (btree.get_element(btree.get_parent(last_handled)).second == "+" || btree.get_element(btree.get_parent(last_handled)).second == "-") {
                                btree.add_element(line[i]);
                                btree.set_relative(i, btree.get_parent(last_handled));
                                btree.set_relative(last_handled, i); last_handled = i;
                            } else if (btree.get_element(btree.get_parent(last_handled)).second == "*" || btree.get_element(btree.get_parent(last_handled)).second == "/") {
                                
                            }
                        } else if (btree.get_element(btree.get_parent(last_handled)).first == "br") {
                            btree.add_element(line[i]);
                            btree.set_relative(i, btree.get_parent(last_handled));
                            btree.set_relative(last_handled, i); last_handled = i;
                        } else if (last_handled == btree.get_parent(last_handled)) {
                            btree.add_element(line[i]);
                            btree.set_relative(last_handled, i); last_handled = i;
                        }
                    }
                } else if (line[i].second == "*" || line[i].second == "/") {
                    
                }
            }
            std::cout << "iteration " << i << " passed :)\n";
            for (int i = 0 ; i < btree.get_len(); i++) {
                std::pair<std::string, std::string> child = btree.get_element(i);
                std::pair<std::string, std::string> parent = btree.get_element(btree.get_parent(i));
                std::cout << "child: " << child.second << ", parent: " << parent.second << "\n";
            }
        }
        res.push_back(btree);
    }
    return res;
}