//
// Created by c4ner on 6/4/2026.
//

#ifndef BM25_C___TOKENIZER_H
#define BM25_C___TOKENIZER_H
#include <string>
#include <unordered_set>
#include <vector>


class Tokenizer {
    public:
    Tokenizer();
    ~Tokenizer();
    std::vector<std::string> Tokenize(const std::string& input);

    private:
    std::string Punctuations_Removal(const std::string& input); //убрать точки, запятые и тд
    std::vector<std::string> Splitting(const std::string& input); //порезать текст на куски
    std::vector<std::string> Stop_Words_Removal(const std::vector<std::string>& input); //выкидка предлогов и союзов ("и", "в", "а", "на" и тд)
    std::string Lowercasing(const std::string &input); // привести все к нижнему регистру (ЯБЛОКО/Яблоко -> яблоко)
    std::unordered_set<std::string> stop_words;
};


#endif //BM25_C___TOKENIZER_H