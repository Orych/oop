#include <iostream>
#include <fstream>
#include <set>
#include <string>

int main(int argc, char* argv[]) {
    std::set<std::string> students;

    for (int i = 1; i < argc; ++i) {
        std::ifstream infile(argv[i]);
        if (!infile.is_open()) {
            std::cerr << "Could not open file: " << argv[i] << std::endl;
            continue;
        }
        std::string name;
        while (std::getline(infile, name)) {
            students.insert(name);
        }
    }

    for (const auto& student : students) {
        std::cout << student << std::endl;
    }

    return 0;
}
