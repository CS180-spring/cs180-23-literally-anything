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
    std::cout << "get_content: " << body << std::endl;
    return body;
}

bool Document::update_content(std::string content) {
    body = content;
    std::cout << "update: " << body << std::endl;
    // will return false in the future if the given content is not valid json
    return true;
}
