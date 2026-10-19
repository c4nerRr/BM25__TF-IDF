//
// Created by c4ner on 6/4/2026.
//

#ifndef BM25_C___TOKENIZER_H
#define BM25_C___TOKENIZER_H
#include <string>
#include <unordered_set>
#include <vector>
#include <string_view>


class Tokenizer {
    public:
    Tokenizer();
    ~Tokenizer();
    std::vector<std::string> All_Tokenize(const std::string_view &input) const;

    private:
    std::unordered_set<std::string> stop_words;
};


#endif //BM25_C___TOKENIZER_H