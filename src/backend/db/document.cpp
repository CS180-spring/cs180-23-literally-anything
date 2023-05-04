#include "document.h"

#include <iostream>

Document::Document() {
    this->id = 9999;
}
Document::Document(int id) {
    this->id = id;
}

int Document::get_id() {
    return id;
}

std::string Document::get_content() {
    return content_str;
}
json Document::get_content_json() {
    return content;
}

bool Document::update_content(std::string new_content) {
    json j = json::parse(new_content, nullptr, false);

    // Not valid json
    if (j.is_discarded()) {
        return false;
    }
    content_str = new_content;
    content = j;
    return true;
}