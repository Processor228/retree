#pragma once

#include <iostream>
#include <istream>
#include <optional>

#include "tokens.hxx"

namespace retree {

using tok_id = int;

class tokenizer {
public:

    struct token_info {
        std::string value;
        tok_id id;
        int ident;
    };

    tokenizer(std::wistream& stream) : m_stream(stream) {

    }

    std::optional<token_info> get_next_item() {
        std::string token;
        int ident = 0;
        m_stream.imbue(std::locale("en_US.UTF-8"));
        wchar_t cur;

        // eat everything untill the name
        while (true) {
            cur = m_stream.get();
            if (cur == std::char_traits<char>::eof() || (cur == '\n' && m_met_self_dir))
                return std::nullopt;

            if (cur == '\n' && !m_met_self_dir) {
                continue;
            }

            if (cur == '#') {
                // met a comment. need to skip untill the end of the line
                while (!(cur == '\n' || cur == std::char_traits<char>::eof())) {
                    cur = m_stream.get();
                }
                ident = 0;
                continue;
            }

            if (is_valid_char_of_name(cur)) {
                break;
            }

            ++ident;
        }

        // here we parse the name
        while (true) {
             if (cur == std::char_traits<char>::eof())
                break;

            if (is_valid_char_of_name(cur)) {
                token += cur;
            } else {
                break;
            }

            cur = m_stream.get();
        }

        if (!m_met_self_dir) {
            /*
                Met the name of the dir we are recreating. Start actual parsing mode
            */
            m_met_self_dir = true;
            return token_info{token, TOKEN_THIS_DIR_ID, ident / 4};
        }

        if (ident == 0 && m_met_self_dir) {
            /*
                We are finished if threre is no identations anymore
                All whats left next is treated as comment.
            */
            return std::nullopt;
        }

        return token_info{token, TOKEN_IDENTIFIER_ID, ident / 4};
    }

    std::optional<token_info> peek_next_item() {
        std::streampos current_pos = m_stream.tellg();
        auto token = get_next_item();
        m_stream.seekg(current_pos);
        return token;
    }

private:

    bool is_valid_char_of_name(wchar_t cur) {
        return cur == '.' || std::iswalnum(cur) || cur == '-' || cur == '_' || cur == '/';
    }

    std::wistream& m_stream;
    bool m_met_self_dir = false;
};

}
