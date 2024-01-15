#include<vector>
#include<string>
#include<iostream>

#include "h/parser.hpp"

Node::Node(std::string _tag, std::string _value) {
    this->tag = _tag;
    this->value = _value;
}

int AbstractTree::get_last() {
    return this->len - 1;
}
void AbstractTree::add(Node el) {
    this->elements.push_back(el);
    this->parents.push_back(this->len);
    this->children.push_back(this->len);
    len++;
}
void AbstractTree::unparent(int child, int parent);
void AbstractTree::parent(int child, int parent) {
    this->unparent(child, this->parents[child]);
    this->parents[child] = parent;
    if (find(this->children[parent].begin(), this->children[parent].end(), child) == this->children[parent].end()) {
        this->children[parent].push_back(child);
    }
}
Node AbstractTree::get_element(int index) {
    return this->elements[index];
}

std::vector<std::vector<std::pair<std::string, std::string>>> split_by_newline(std::vector<std::pair<std::string, std::string>> &lexed) {
    std::vector<std::vector<std::pair<std::string, std::string>>> res;
    std::vector<std::pair<std::string, std::string>> current;
    for (std::pair<std::string, std::string> i : lexed) {
        if (i.first == "newline") {
            if (current) res.push_back(current);
            current = {};
        } else {
            current.push_back(i);
        }
    }
    if (current) res.push_back(current);
    return res;
}

AbstractTree parse(std::vector<std::pair<std::string, std::string>> &lexed) {
    AbstractTree tree;
    tree.add(Node("start", "start"));
    for (std::vector<std::pair<std::string, std::string>> line : split_by_newline(lexed)) {
        //
    }
    return tree;
}