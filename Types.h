//
// Created by c4ner on 6/4/2026.
//

#ifndef BM25_C___TYPES_H
#define BM25_C___TYPES_H


#include <string>
#include <vector>
#include <cstddef>


//тут будут общие структуры данных, напр ПозитионРостинг, чтоб разные модули могли работать с этим без циклические зависимостей

struct Position {
    size_t doc_ID{}; //поле для айди
    std::vector<std::size_t> positions; //TF - частота слова
};

struct SearchResult {
    std::size_t docID{}; //айди найденного дока, началка - 0
    double score{};
};

#endif //BM25_C___TYPES_H