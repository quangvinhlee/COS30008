#include "SimpleForwardIterator.h"

SimpleForwardIterator::SimpleForwardIterator(const DataWrapper* aCollection) noexcept : fCollection(aCollection), fIndex(0) {}

const DataMap& SimpleForwardIterator::operator*() noexcept {
    return (*fCollection)[fIndex]; 
}

SimpleForwardIterator& SimpleForwardIterator::operator++() noexcept {
    ++fIndex;
    return *this;
}

SimpleForwardIterator SimpleForwardIterator::operator++(int) noexcept {
    SimpleForwardIterator temp = *this;
    ++(*this);
    return temp;
}

bool SimpleForwardIterator::operator==(const SimpleForwardIterator& aOther) const noexcept {
    return fIndex == aOther.fIndex;
}

bool SimpleForwardIterator::operator!=(const SimpleForwardIterator& aOther) const noexcept {
    return !(*this == aOther);
}

SimpleForwardIterator SimpleForwardIterator::begin() const noexcept {
    return SimpleForwardIterator(fCollection);
}

SimpleForwardIterator SimpleForwardIterator::end() const noexcept {
    return SimpleForwardIterator(fCollection);
}
