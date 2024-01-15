#include <vector>
#include <string>

class Node {
    public:
        std::string tag;
        std::string value;
        Node(std::string _tag, std::string _value);
};

class AbstractTree {
    private:
        std::vector<int> parents;
        std::vector<vector<int>> children;
        std::vector<Node> elements;
        int len = 0;
    public:
        int get_last();
        void add(Node el);
        void unparent(int child, int parent);
        void parent(int child, int parent);
        Node get_element(int index);
};