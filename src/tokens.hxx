#pragma once

#include <string>
#include <unordered_map>


#define TOKEN(name, id) \
    constexpr const char* TOKEN_##name = id; \
    constexpr int TOKEN_##name##_ID = __COUNTER__;


TOKEN(THIS_DIR, "./")
TOKEN(DIR_ITEM, "├──")
TOKEN(DIR_FINAL_ITEM, "└──")
TOKEN(PARENT_DIR_SHADOW, "│")
TOKEN(IDENTIFIER, "..")  // impossible name
TOKEN(IGNORE, "///")


const std::unordered_map<std::string, int> token_to_id = {
    {TOKEN_THIS_DIR, TOKEN_THIS_DIR_ID},
    {TOKEN_DIR_ITEM, TOKEN_DIR_ITEM_ID},
    {TOKEN_DIR_FINAL_ITEM, TOKEN_DIR_FINAL_ITEM_ID},
    {TOKEN_PARENT_DIR_SHADOW, TOKEN_PARENT_DIR_SHADOW_ID},
    {TOKEN_IDENTIFIER, TOKEN_IDENTIFIER_ID},
    {TOKEN_IGNORE, TOKEN_IGNORE_ID}
};
