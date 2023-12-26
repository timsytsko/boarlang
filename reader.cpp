#include <string>
#include <vector>
#include <fstream>

#include "h/reader.hpp"

std::vector<std::string> read_file_content(std::string path_to_file) {
    std::fstream fd;
	fd.open(path_to_file, std::ios::in);
    std::vector<std::string> res;
    while (!fd.eof()) {
       std::string line; std::getline(fd, line, ';');
       res.push_back(line);
	}
    fd.close();
    return res;
}