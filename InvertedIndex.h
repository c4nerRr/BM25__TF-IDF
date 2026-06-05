//
// Created by c4ner on 6/4/2026.
//

#ifndef BM25_C___INVERTEDINDEX_H
#define BM25_C___INVERTEDINDEX_H
#include <string>
#include <unordered_map>
#include <vector>

class InvertedIndex {
    public:
    InvertedIndex();
    ~InvertedIndex();


    struct Position {
        size_t doc_ID{}; //поле для айди
        std::vector<std::size_t> positions; //TF - частота слова
    };
    std::vector<Position> GetPosting(const std::string &word) const;//список документов и позиций
    size_t GetTotalDocCounts() const;
    size_t GetDocumentsLength(size_t doc_id) const;
    size_t GetDocumentFrequency(const std::string& word) const;

    void AddDocument_public(size_t ID, const std::vector<std::string>& vector_token);


    private:
    std::unordered_map<size_t, size_t> doc_lengths; //Айди - колво слов в нем
    std::unordered_map<std::string, std::vector<Position>> inverted_index; //индекс, самл слово, f(q,D)
    //слово -> список карточек документов
    void AddDocument(size_t ID, const std::vector<std::string>& vector_token);
};


#endif //BM25_C___INVERTEDINDEX_H
