#include "PalindromeStringIterator.h"
#include <iostream>
#include <cctype>

void PalindromeStringIterator::moveToNextIndex() {
    while (++fIndex < static_cast<int>(fString.length())) {
        if (std::isalpha(fString[fIndex])) {
            break;
        }
    }
}

void PalindromeStringIterator::moveToPreviousIndex() {
    while (--fIndex >= 0) {
        if (std::isalpha(fString[fIndex])) {
            break;
        }
    }
}

PalindromeStringIterator::PalindromeStringIterator(const std::string& aString)
    : fString(aString), fIndex(-1) {
    moveToNextIndex();
}

char PalindromeStringIterator::operator*() const noexcept {
    return std::toupper(fString[fIndex]);
}

PalindromeStringIterator& PalindromeStringIterator::operator++() noexcept {
    moveToNextIndex();
    return *this;
}

PalindromeStringIterator PalindromeStringIterator::operator++(int) noexcept {
    PalindromeStringIterator old = *this;
    ++(*this);
    return old;
}

PalindromeStringIterator& PalindromeStringIterator::operator--() noexcept {
    moveToPreviousIndex();
    return *this;
}

PalindromeStringIterator PalindromeStringIterator::operator--(int) noexcept {
    PalindromeStringIterator old = *this;
    --(*this);
    return old;
}

bool PalindromeStringIterator::operator==(const PalindromeStringIterator& aOther) const noexcept {
    return fIndex == aOther.fIndex;
}

bool PalindromeStringIterator::operator!=(const PalindromeStringIterator& aOther) const noexcept {
    return !(*this == aOther);
}

PalindromeStringIterator PalindromeStringIterator::begin() const noexcept {
    PalindromeStringIterator temp = *this;
    temp.fIndex = -1;
    temp.moveToNextIndex();
    return temp;
}

PalindromeStringIterator PalindromeStringIterator::end() const noexcept {
    PalindromeStringIterator temp = *this;
    temp.fIndex = static_cast<int>(fString.length());
    return temp;
}

PalindromeStringIterator PalindromeStringIterator::rbegin() const noexcept {
    PalindromeStringIterator temp = *this;
    temp.fIndex = static_cast<int>(fString.length());
    temp.moveToPreviousIndex();
    return temp;
}

PalindromeStringIterator PalindromeStringIterator::rend() const noexcept {
    PalindromeStringIterator temp = *this;
    temp.fIndex = -1;
    return temp;
}

