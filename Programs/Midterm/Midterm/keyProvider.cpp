#include "KeyProvider.h"
#include <cassert>
#include <cctype>


std::string KeyProvider::preprocessString(const std::string& aString) noexcept {
    std::string result;
    for (char c : aString) {
        if (isalpha(c)) {
            result.push_back(toupper(c));
        }
    }
    return result;
}

KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept : fKeys(aKeyword), fIndex(0){
    fKeys = preprocessString(aKeyword);
    std::string preprocessedSource = preprocessString(aSource);

    fKeys.resize(preprocessedSource.size());

    size_t keywordIndex = 0;
    for (size_t i = 0; i < preprocessedSource.size(); i++){
        if (std::isalpha(preprocessedSource[i])) {
            fKeys[i] = std::toupper(fKeys[keywordIndex % aKeyword.size() ]);
            ++keywordIndex;
        }
    }

}

char KeyProvider::operator*() const noexcept {
    return fKeys[fIndex];
}

KeyProvider& KeyProvider::operator++() noexcept {
    ++fIndex;
    return *this;
}

KeyProvider KeyProvider::operator++(int) noexcept{
    KeyProvider temp = *this;
    ++fIndex;
    return temp;
}

bool KeyProvider::operator==(const KeyProvider& aOther) const noexcept {
    return (fKeys == aOther.fKeys) && (fIndex == aOther.fIndex);
}

bool KeyProvider::operator!=(const KeyProvider& aOther) const noexcept {
    return !(*this == aOther);
}

KeyProvider KeyProvider::begin() const noexcept {
    return KeyProvider(*this);
}

KeyProvider KeyProvider::end() const noexcept {
    KeyProvider iter = *this;
    iter.fIndex = fKeys.size();
    return iter;
}