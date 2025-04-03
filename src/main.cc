#include <exception>
#include <fstream>
#include <iostream>
#include <CLI/CLI.hpp>

#include "parser.hxx"
#include "tree.hxx"

int main(int argc, char** argv) {
    CLI::App app{"Program that reproduces directories structure based on tree cli utility dump."};

    std::string filename = "tree.txt";
    app.add_option("-f,--file", filename, "Path to the tree output");

    std::string dir_path = "./";
    app.add_option("-d,--dest", dir_path, "Path where to reproduce the tree");

    bool preserve_files = false;
    app.add_flag("-p,--preserve-files", preserve_files, "Preserve files, make them empty");

    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose output");

    CLI11_PARSE(app, argc, argv);

    retree::tree* tree;

    try {
        std::wifstream filestream {filename};
        tree = retree::parser(filestream)
                        .produce();
    } catch(const std::exception& e) {
        std::cout << "An error occured: " << e.what() << "\n";
    }

    if (verbose)
        tree->print(0);

    try {
        tree->reproduce(dir_path, preserve_files);
    } catch(const std::exception& e) {
        std::cout << "Could not reproduce the tree: " << e.what() << "\n";
    }

    return 0;
}
