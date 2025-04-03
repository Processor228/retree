#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace retree {

namespace fs = std::filesystem;

class tree {
public:

    virtual void reproduce(const std::string& where, bool with_files) {
        fs::path target_path = fs::path(where) / m_name;

        // if there is no kids this is not considered a directory
        if (!sub_items.empty() && !fs::exists(target_path)) {
            fs::create_directory(target_path);
        }

        /*
            if there is no kids and its not a symlink then it is a file
            and we reproduce those in case -p flag is provided.
        */
        if (with_files && sub_items.empty()) {
            std::ofstream file(target_path);
        }

        for (auto val : sub_items) {
            val->reproduce(target_path.string(), with_files);
        }
    }

    virtual void print(int layer) {
        std::cout << std::string(layer, ' ') << m_name << '\n';
        for (auto val : sub_items) {
            val->print(layer + 4);
        }
    }

    void add_sub_item(tree* node) {
        sub_items.push_back(node);
    }

    std::string get_name() { return m_name; }

    tree(std::string name) : m_name(std::move(name)) {}

private:
    std::string m_name;
    std::vector<tree*> sub_items;
};

}
