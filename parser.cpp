#include <vector>
#include <string>

#include "h/parser.hpp"

void BinaryTree::add_element(std::pair<std::string, std::string> element) {
    this->elements.push_back(element);
    this->parents.push_back(len);
    this->children.push_back(std::make_pair(-1, -1));
    this->len++;
}

void BinaryTree::set_parent(int child, int parent) {
    this->parents[child] = parent;
}

void BinaryTree::set_child(int child, int parent) {
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

std::pair<std::string, std::string> BinaryTree::get_element_by_index(int index) {
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
        // handle btree
    }
    return res;
}