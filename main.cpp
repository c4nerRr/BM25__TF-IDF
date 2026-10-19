#include <iostream>
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>

#include "Tokenizer.h"
#include "InvertedIndex.h"
#include "Scorer.h"

int main() {
    try {
        const std::filesystem::path folder = "documents";
        if (!std::filesystem::is_directory(folder)) {
            throw std::runtime_error("Not a directory");
        }

        std::vector<std::filesystem::path> files;
        for (const auto& entry : std::filesystem::directory_iterator(folder)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                files.push_back(entry.path());
            }
        }

        std::ranges::sort(files);

        Tokenizer tokenizer{};
        InvertedIndex inverted_index{};

        std::vector<std::filesystem::path> docs{};
        for (const auto& path : files) {
            std::ifstream input(path, std::ios::binary); //binary сейвит исходные байты ЮТФ-8
            if (!input) {
                throw std::runtime_error("Could not open file");
            }

            const std::string text { std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };
            if (input.bad()) {
                throw std::runtime_error("Could not read file");
            }
            const auto tokens = tokenizer.All_Tokenize(text);
            const std::size_t doc_count = docs.size();

            inverted_index.AddDocument(doc_count, tokens);
            docs.push_back(path);
        }
        if (docs.empty()) {
            throw std::runtime_error("No documents found");
        }
        std::cout << "Indexed doc: " << inverted_index.GetTotalDocCounts() << '\n';

        Scorer scorer(inverted_index);
        std::cout<< std::fixed << std::setprecision(6);

        std::string query{};

        while (std::cout<<"\nQuery (empty = exit): ", std::getline(std::cin, query)) {
            if (query.empty()) {
                break;
            }

            const auto query_tokens = tokenizer.All_Tokenize(query);
            const auto results = scorer.Query(query_tokens, 10);

            if (results.empty()) {
                std::cout<<"No results found\n";
                continue;
            }

            for (const auto&[docID, score] : results) {
                const auto& path = docs.at(docID); //получили путь по айди

                const auto utf8_path = path.u8string();
                const std::string display_path(utf8_path.begin(), utf8_path.end());

                std::cout << score << " | " << display_path << '\n';
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
