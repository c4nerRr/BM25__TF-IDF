cmake_minimum_required(VERSION 4.0)
project(BM25_C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(BM25_C__ main.cpp
        Tokenizer.cpp
        Tokenizer.h
        InvertedIndex.cpp
        InvertedIndex.h
        Compressor.cpp
        Compressor.h
        Scorer.cpp
        Scorer.h
        Types.h)

find_package(ICU REQUIRED COMPONENTS uc)
target_link_libraries(BM25_C__ PRIVATE ICU::uc)
