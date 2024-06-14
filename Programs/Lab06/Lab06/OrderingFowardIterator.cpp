#include "OrderingForwardIterator.h"

OrderingForwardIterator::OrderingForwardIterator(const DataWrapper* aCollection) noexcept
    : fCollection(aCollection), fIndex(0), fMapPosition(0) {
    setMapPosition(); // Initialize fMapPosition in constructor
}

const DataMap& OrderingForwardIterator::operator*() noexcept {
    return (*fCollection)[fMapPosition]; // Accessing data from DataWrapper using fMapPosition
}

OrderingForwardIterator& OrderingForwardIterator::operator++() noexcept {
    ++fIndex;
    setMapPosition(); // Update fMapPosition after incrementing fIndex
    return *this;
}

OrderingForwardIterator OrderingForwardIterator::operator++(int) noexcept {
    OrderingForwardIterator temp = *this;
    ++(*this);
    return temp;
}

bool OrderingForwardIterator::operator==(const OrderingForwardIterator& aOther) const noexcept {
    return fIndex == aOther.fIndex;
}

bool OrderingForwardIterator::operator!=(const OrderingForwardIterator& aOther) const noexcept {
    return !(*this == aOther);
}

OrderingForwardIterator OrderingForwardIterator::begin() const noexcept {
    return OrderingForwardIterator(fCollection);
}

OrderingForwardIterator OrderingForwardIterator::end() const noexcept {
    OrderingForwardIterator endIterator = *this;
    endIterator.fIndex = fCollection->size(); // Set fIndex to the size of the collection
    endIterator.fMapPosition = fCollection->size(); // Set fMapPosition to the size of the collection
    return endIterator;
}

void OrderingForwardIterator::setMapPosition() {
    // Implement your logic to set fMapPosition based on ordering here
    // This function should map the current iterator index to the correct ordered position in the collection
    // It needs to be called in the constructor, in the prefix increment operator, and in begin()
}
