//
// Created by c4ner on 6/4/2026.
//

#include "Tokenizer.h"
#include <cctype>

#include <cstdint>
#include <limits>
#include <stdexcept>

#include <unicode/normalizer2.h>
#include <unicode/stringpiece.h>
#include <unicode/uchar.h>
#include <unicode/unistr.h>


Tokenizer::Tokenizer() {
    stop_words.insert({"and", "a", "in", "the"});
}

Tokenizer::~Tokenizer() = default;

std::vector<std::string> Tokenizer::All_Tokenize(const std::string_view &input) const {

    if (input.empty()) {
        return {};
    }

    if (input.size() >
        static_cast<std::size_t>(
            std::numeric_limits<std::int32_t>::max())) //длинная строка. ИСУ использует инт32_т
    {
        throw std::length_error("Text is too large for ICU");
    }

    const auto text = icu::UnicodeString::fromUTF8( icu::StringPiece(input.data(),static_cast<std::int32_t>(input.size())));

    UErrorCode status = U_ZERO_ERROR; //нормализация ок для неучей пишу

    const auto* normalizer = icu::Normalizer2::getNFKCCasefoldInstance(status);
    if (U_FAILURE(status)) {
        throw std::runtime_error(u_errorName(status));
    }

    icu::UnicodeString normalized;
    normalizer->normalize(text, normalized, status);

    if (U_FAILURE(status)) {
        throw std::runtime_error(u_errorName(status));
    }



    //------
    //все чо я могу +- вкурить в коде ниже:
    std::vector<std::string> result;
    icu::UnicodeString current_word; //символы одного слова

    auto finish_word = [&]() {
        if (current_word.isEmpty()) {
            return;
        }

        std::string word;
        current_word.toUTF8String(word);

        if (!stop_words.contains(word)) {
            result.push_back(word);
        }
        current_word.remove();
    };

    for (std::int32_t i = 0; i < normalized.length();) {
       const UChar32 c = normalized.char32At(i);
        i = normalized.moveIndex32(i,1);

        const auto cs = u_charType(c);
        const bool is_mark = cs == U_NON_SPACING_MARK || cs == U_COMBINING_SPACING_MARK || cs == U_ENCLOSING_MARK;

        if (u_isalnum(c) || (is_mark && !current_word.isEmpty())) { //ислам - я буква? я цифра?
            current_word.append(c); //аппанд - тип копирует пушбэк
        }
        else {
            finish_word();
        }
    }
        finish_word();
        return result;

    }