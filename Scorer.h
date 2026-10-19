//
// Created by c4ner on 6/4/2026.
//

#ifndef BM25_C___SCORER_H
#define BM25_C___SCORER_H
#include <string>
#include <vector>
#include <cstddef>

#include "InvertedIndex.h"
#include "Types.h"


class Scorer {
    public:
    explicit Scorer(const InvertedIndex& invertedIndex);
    ~Scorer();

    [[nodiscard]]std::vector<SearchResult> Query(const std::vector<std::string> &query_tokens, std::size_t top_k = 10) const;

    private:
    const InvertedIndex& _index{};
    double _k1 = 1.2;
    double _b = 0.75;

    [[nodiscard]]double CalculateIDF(const std::string& term) const; //насколько слово помогает отличить доки
    [[nodiscard]] double ScoreTerm(std::size_t term_frequency, std::size_t doc_length, double averange_length, double idf) const;

};


#endif //BM25_C___SCORER_H