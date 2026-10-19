//
// Created by c4ner on 6/4/2026.
//

#ifndef BM25_C___INVERTEDINDEX_H
#define BM25_C___INVERTEDINDEX_H
#include <span>
#include <string>
#include <unordered_map>
#include <vector>
#include "Types.h"

class InvertedIndex {
    public:
    InvertedIndex();
    ~InvertedIndex();

    std::span<const Position> GetPosting(const std::string &word) const;//список документов и позиций
    size_t GetTotalDocCounts() const;
    double GetAverageDocumentLength() const;
    size_t GetDocumentsLength(size_t doc_id) const;
    size_t GetDocumentFrequency(const std::string& word) const;
    void AddDocument(size_t ID, const std::vector<std::string>& vector_token);

    private:
    std::unordered_map<size_t, size_t> doc_lengths; //Айди - колво слов в нем
    std::unordered_map<std::string, std::vector<Position>> inverted_index; //индекс, самл слово, f(q,D)
    //слово -> список карточек документов
};


#endif //BM25_C___INVERTEDINDEX_H
