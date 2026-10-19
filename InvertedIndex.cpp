//
// Created by c4ner on 6/4/2026.
//

#include "InvertedIndex.h"

#include <stdexcept> // Здесь объявлен std::invalid_argument.
#include <span>


InvertedIndex::InvertedIndex() = default;

InvertedIndex::~InvertedIndex() = default;


std::span<const Position> InvertedIndex::GetPosting(const std::string &word) const {
    const auto it = inverted_index.find(word);
    if (it == inverted_index.end()) {
        return {};
    }
    return it->second; //к значению через итератор
}

size_t InvertedIndex::GetTotalDocCounts() const { //N - колво доков в базе
    return doc_lengths.size();
}

double InvertedIndex::GetAverageDocumentLength() const {
    if (doc_lengths.empty()) { //если доков еще нет, считаем 0 ок.
        return 0.0;
    }
    double total_length = 0.0; //chtobi bilo drobnoe

    for (const auto& entry : doc_lengths) {
        // entry.first — ID документа.
        // entry.second — его длина в токенах.

        total_length += static_cast<double>(entry.second);
    }
    // size() — число документов.
    return total_length / static_cast<double>(doc_lengths.size());
}

size_t InvertedIndex::GetDocumentsLength(size_t doc_id) const {
    const auto it = doc_lengths.find(doc_id);

    if (it == doc_lengths.end()) {
        return 0;
    }

    return it->second;
}


size_t InvertedIndex::GetDocumentFrequency(const std::string &word) const { //doc.frequency(df) - в скольких уникальных доках встр. слово
    const auto it = inverted_index.find(word);

    if (it == inverted_index.end()) {
        return 0;
    }
   return it->second.size();
}


void InvertedIndex::AddDocument(size_t ID, const std::vector<std::string> &vector_token) {

    if (doc_lengths.contains(ID)) { //док_ленз хранит айди уже добавленных доков, контаинс(ИД) возвращает тру если такой ключ уже есть
        throw std::invalid_argument("Document ID " + std::to_string(ID) + " already exists"); //передаем привет коду: передан уже занятый айди.
        //сроу прекратит выполнение этой функции.
    }

    auto temp_size = vector_token.size();
    doc_lengths.insert({ID, temp_size});
    for (size_t i = 0; i < vector_token.size(); ++i) {
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

