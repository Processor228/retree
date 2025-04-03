#include <exception>
#include <fstream>
#include <iostream>
#include <CLI/CLI.hpp>

#include "parser.hxx"
#include "tree.hxx"

int main(int argc, char** argv) {
    CLI::App app{"Program that reproduces directories structure based on tree cli utility dump."};

    std::string filename = "tree.txt";
    auto file_opt = app.add_option("-f,--file", filename, "Path to the tree output");

    bool flag_from_stdin = false;
    auto from_stdin_opt = app.add_flag("-i,--from-stdin", flag_from_stdin, "Use stdin to pass tree");

    std::string dir_path = "./";
    app.add_option("-d,--dest", dir_path, "Path where to reproduce the tree");

    bool preserve_files = false;
    app.add_flag("-p,--preserve-files", preserve_files, "Preserve files, make them empty");

    file_opt->excludes(from_stdin_opt);
    from_stdin_opt->excludes(file_opt);

    CLI11_PARSE(app, argc, argv);

    retree::tree* tree;

    try {
        if (flag_from_stdin) {
            tree = retree::parser(std::wcin)
                          .produce();
        } else {
            std::wifstream filestream {filename};
            tree = retree::parser(filestream)
                          .produce();
        }
    } catch(const std::exception& e) {
        std::cout << "An error occured: " << e.what() << "\n";
    }

    tree->print(0);

    try {
        tree->reproduce(dir_path, preserve_files);
    } catch(const std::exception& e) {
        std::cout << "Could not reproduce the tree: " << e.what() << "\n";
    }

    return 0;
}
