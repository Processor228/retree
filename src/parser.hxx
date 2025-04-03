#pragma once

#include <iostream>

#include "tokens.hxx"
#include "tree.hxx"
#include "tokenizer.hxx"

namespace retree {

class parser {
public:

    tree* produce() {
        tree* root = new tree("./");
        return parse_directory(root, 1);
    }

    parser(std::wistream& stream) : m_tokenizer(stream) {}

private:
    tree* parse_directory(tree* parent, int layer_level) {
        std::string token;
        while (true) {
            auto current_item = m_tokenizer.get_next_item();

            if (!current_item)
                break;

            if (current_item->id == TOKEN_IGNORE_ID || current_item->id == TOKEN_THIS_DIR_ID)
                continue;

            auto current_node = new tree(current_item->value);
            parent->add_sub_item(current_node);

            auto next_item = m_tokenizer.peek_next_item();
            if (layer_level < next_item->ident) {
                parse_directory(current_node, layer_level + 1);
            }
            if (next_item->ident < layer_level) {
                break;
            }
        }

        return parent;
    }

    tokenizer m_tokenizer;  // whats being parsed
};

}