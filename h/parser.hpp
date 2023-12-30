#include <vector>
#include <string>

class BinaryTree {
    private:
        std::vector<std::pair<std::string, std::string>> elements;
        std::vector<int> parents;
        std::vector<std::pair<int, int>> children;
        int len = 0;
    public:
        int get_len();
        int get_last_index();
        void add_element(std::pair<std::string, std::string> element);
        void set_relative(int child, int parent);
        int get_parent(int child);
        std::pair<int, int> get_children(int parent);
        std::pair<std::string, std::string> get_element(int index);
        int find_root();
};

std::vector<BinaryTree> parse(std::vector<std::pair<std::string, std::string>> &lexed);