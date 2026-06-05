//
// Created by c4ner on 6/4/2026.
//

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
    stop_words.insert({"and", "a", "in", "the"});
}

Tokenizer::~Tokenizer() = default;

std::vector<std::string> Tokenizer::Tokenize(const std::string &input) {
    const std::string temp1 = Lowercasing(input);
    const std::string temp2 = Punctuations_Removal(temp1);
    std::vector<std::string> temp = Splitting(temp2);
    std::vector<std::string> result = Stop_Words_Removal(temp);
    return result;
}

std::string Tokenizer::Punctuations_Removal(const std::string &input) { //NOLINT
    std::string result;
    //auto result = " ";
    for (const char & i : input) {
        if (i == ',' || i == '!' || i == '?' || i == '.' || i == '/' || i == '(' || i == ')' || i == '[' || i == ']' || i == '{' || i == '}') {
            continue;
        }
        result += i;
    }
    return result;
}

std::vector<std::string> Tokenizer::Splitting(const std::string &input) { //NOLINT
    std::vector<std::string> result;
    std::string temp;
    for (const char & i : input) {
        if (!(i == ' ' || i == '\n' || i == '\t')) {
            temp += i;
        }
        else {
            if (!(temp.empty())) {
                result.push_back(temp);
                temp.clear();
            }
        }
    }
    if (!temp.empty()) {
        result.push_back(temp);
        temp.clear();
    }
    return result;
}

std::vector<std::string> Tokenizer::Stop_Words_Removal(const std::vector<std::string> &input) { //NOLINT
    std::vector<std::string> result;
    for (auto & i : input) {
        if (stop_words.contains(i)) {
            continue;
        }
        result.push_back(i);
    }
    return result;
}


std::string Tokenizer::Lowercasing(const std::string &input) { //NOLINT
    std::string result;
    for (const char & i : input) {
        if (i >= 'A' && i <= 'Z') {
            result.push_back(tolower(i)); //NOLUNT
        }
        else {
            result.push_back(i);
        }
    }
    return result;
}

