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
            if (m_stream.eof() || (cur == '\n' && m_met_self_dir))
                return std::nullopt;

            if (cur == '.' || std::iswalnum(cur)) {
                break;
            }

            ++ident;
        }

        while (true) {
             if (m_stream.eof())
                break;

            if (cur == '.' || std::iswalnum(cur) || cur == '-' || cur == '_' || cur == '/') {
                token += cur;
            } else {
                break;
            }

            cur = m_stream.get();
        }

        if (token.starts_with("./")) {
            m_met_self_dir = true;
            return token_info{token, TOKEN_THIS_DIR_ID, ident / 4};
        }

        if (!m_met_self_dir)
            return token_info{"#", TOKEN_IGNORE_ID, ident / 4};

        if (ident == 0 && !token.starts_with("./")) {
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
    std::wistream& m_stream;
    bool m_met_self_dir = false;
};

}
