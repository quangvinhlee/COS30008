#pragma once
#include <optional>
#include <cassert>
#include <iostream>

template<typename T>
class DynamicQueue {
private:
    T* fElements;
    size_t fFirstIndex;
    size_t fLastIndex;
    size_t fCurrentSize;
    size_t fCapacity; 

    
    void resize(size_t aNewSize) {
        if (aNewSize == 0) {
            throw std::runtime_error("New size cannot be 0.");
        }
        T* newElements = new T[aNewSize];
        for (size_t i = 0; i < fCurrentSize; ++i) {
            newElements[i] = fElements[(fFirstIndex + i) % fCapacity];
        }
        delete[] fElements;
        fElements = newElements;
        fFirstIndex = 0;
        fLastIndex = fCurrentSize;
        fCapacity = aNewSize;
    }

    void ensure_capacity() {
        if (fCurrentSize == fCapacity) {
            resize(fCapacity * 2); 
        }
    }

    void adjust_capacity() {
        if (fCurrentSize <= fCapacity / 4 && fCapacity > 1) {
            resize(fCapacity / 2);
        }
    }

public:
    DynamicQueue() : fElements(new T[1]), fFirstIndex(0), fLastIndex(0), fCurrentSize(0), fCapacity(1) {}

    ~DynamicQueue() { delete[] fElements; }

    DynamicQueue(const DynamicQueue&) = delete;
    DynamicQueue& operator=(const DynamicQueue&) = delete;

    std::optional<T> top() const noexcept {
        if (fCurrentSize == 0) {
            return std::nullopt;
        }
        else {
            return fElements[fFirstIndex];
        }
    }

    void enqueue(const T& aValue) {
        ensure_capacity();
        fElements[fLastIndex] = aValue;
        fLastIndex = (fLastIndex + 1) % fCapacity;
        ++fCurrentSize;
    }

    void dequeue() {
        assert(fCurrentSize > 0);
        fFirstIndex = (fFirstIndex + 1) % fCapacity;
        --fCurrentSize;
        adjust_capacity();
    }
};
