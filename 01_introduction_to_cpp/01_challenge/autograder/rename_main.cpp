#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

void rename_main_function(const std::string& input_filepath, const std::string& output_filepath, bool empty = false) {
    std::ifstream input_file(input_filepath);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return;
    }

    std::string content;
    std::string line;
    while (std::getline(input_file, line)) {
        content += line + '\n';
    }
    input_file.close();

    size_t pos = content.find("int main(");
    if (pos != std::string::npos) {
        content.replace(pos, 9, "int dummy_main(");
    } else {
        std::cerr << "main function not found." << std::endl;
        return;
    }

    std::ofstream output_file(output_filepath);
    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    if (empty) {
        output_file << "int dummy_main() { return 1; }";
    } else {
        output_file << content;
    }
    output_file.close();
}

int main(int argc, char** argv) {
    bool empty = argc > 3;
    rename_main_function(argv[1], argv[2], empty);
}