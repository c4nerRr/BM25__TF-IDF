//
// Created by c4ner on 6/4/2026.
//

#include "InvertedIndex.h"


InvertedIndex::InvertedIndex() = default;

InvertedIndex::~InvertedIndex() = default;


std::vector<InvertedIndex::Position> InvertedIndex::GetPosting(const std::string &word) const { //TF - для скора
    if (!(inverted_index.contains(word))) {
        return {};
    }
    return inverted_index.at(word);
}

size_t InvertedIndex::GetTotalDocCounts() const { //N - колво доков в базе
    return doc_lengths.size();
}

size_t InvertedIndex::GetDocumentsLength(const size_t doc_id) const { // |D| - длинна конкретного дока, чтоб штрафовать длинные тексты
    if (!doc_lengths.contains(doc_id)) {
        return 0;
    }
    return doc_lengths.at(doc_id);
}

size_t InvertedIndex::GetDocumentFrequency(const std::string &word) const { //doc.frequency(df) - в скольких уникальных доках встр. слово
    if (!inverted_index.contains(word)) {
        return 0;
    }
    const auto f =  inverted_index.at(word);
    return f.size();
}


void InvertedIndex::AddDocument(size_t ID, const std::vector<std::string> &vector_token) {
    auto temp_size = vector_token.size();
    doc_lengths.insert({ID, temp_size});
    for (int i = 0; i < vector_token.size(); ++i) {
        auto& posting_list = inverted_index[vector_token[i]]; //список взят по ссылке.
        if (!posting_list.empty() && posting_list.back().doc_ID == ID) {
            posting_list.back().positions.push_back(i);
        }
        else {
            Position temp_position;
            temp_position.doc_ID = ID;
            temp_position.positions.push_back(i);
            posting_list.push_back(temp_position);
        }
    }
}

