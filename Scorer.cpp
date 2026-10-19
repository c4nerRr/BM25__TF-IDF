//
// Created by c4ner on 6/4/2026.
//

#include "Scorer.h"
#include <cmath>         // std::log1p.
#include <algorithm>     // std::sort.
#include <unordered_map>
#include <unordered_set> //уже учтунные слова запроса.

Scorer::Scorer(const InvertedIndex &invertedIndex) : _index(invertedIndex) {
}

Scorer::~Scorer() = default;

std::vector<SearchResult> Scorer::Query(const std::vector<std::string> &query_tokens, std::size_t top_k) const {
    if (query_tokens.empty() || top_k == 0 ||
        _index.GetTotalDocCounts() == 0)
    {
        return {};
    }
    const double average_length = _index.GetAverageDocumentLength(); //один раз для всего запроса

    if (average_length <= 0.0) { //кейс с пустыми доками
        return {};
    }

    std::unordered_map<std::size_t, double> scores;
    std::unordered_set<std::string> processed_terms;

    for (const auto& term : query_tokens) {
        if (!processed_terms.insert(term).second) { //повтор слова не увеличит вес
            continue;
        }

        const auto postings = _index.GetPosting(term);

        if (postings.empty()) {
            continue;
        }

        const double idf = CalculateIDF(term);

        for (const auto& posting : postings) {
            const std::size_t tf = posting.positions.size();
            const std::size_t dl =
                _index.GetDocumentsLength(posting.doc_ID);

            scores[posting.doc_ID] +=
                ScoreTerm(tf, dl, average_length, idf);
        }
    }

    std::vector<SearchResult> results;
    results.reserve(scores.size());

    for (const auto& [doc_id, score] : scores) {
        results.push_back(SearchResult{doc_id, score});
    }

    std::ranges::sort(results, [](const SearchResult& left, const SearchResult& right)
                        {
                          if (left.score == right.score) {
                              return left.docID < right.docID;
                          }

                          return left.score > right.score;
                        }
    );

    if (results.size() > top_k) {
        results.resize(top_k);
    }

    return results;

}

double Scorer::CalculateIDF(const std::string &term) const {
    const auto n = static_cast<double>(_index.GetTotalDocCounts());
    const auto df = static_cast<double>(_index.GetDocumentFrequency(term));

    if (n== 0.0 || df == 0.0) { //для отсутств слова
        return 0.0;
    }

    return std::log1p((n-df + 0.5) / (df + 0.5));
}

double Scorer::ScoreTerm(std::size_t term_frequency, std::size_t doc_length, double averange_length, double idf) const {
    if (term_frequency == 0 || averange_length <= 0) {
        return 0.0;
    }
    const auto tf = static_cast<double>(term_frequency);
    const auto dl = static_cast<double>(doc_length);

    const auto lenght_norm = 1.0 - _b + _b * (dl/averange_length);
    const auto tf_weight = (tf*(_k1 + 1.0) / (tf + _k1 * lenght_norm));

    return tf_weight * idf;
}
