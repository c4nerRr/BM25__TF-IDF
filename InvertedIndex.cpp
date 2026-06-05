//
// Created by c4ner on 6/4/2026.
//

#include "InvertedIndex.h"


InvertedIndex::InvertedIndex() {
}

InvertedIndex::~InvertedIndex() {
}


size_t InvertedIndex::GetTotalDocCounts() const {
}

size_t InvertedIndex::GetDocumentsLength(size_t doc_id) const {
}

size_t InvertedIndex::GetDocumentFrequency(const std::string &word) const {
}

void InvertedIndex::AddDocument_public(const size_t ID, const std::vector<std::string> &vector_token) {
    AddDocument(ID, vector_token);
}

void InvertedIndex::AddDocument(size_t ID, const std::vector<std::string> &vector_token) {
    auto temp_size = vector_token.size();
    doc_lengths.insert({ID, temp_size});
    for (int i = 0; i < vector_token.size(); ++i) {

    }
}

