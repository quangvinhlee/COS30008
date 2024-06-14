#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

template<typename T>
class List
{
private:
    using Node = typename DoublyLinkedList<T>::Node;

    Node fHead;
    Node fTail;
    size_t fSize;

public:

    using Iterator = DoublyLinkedListIterator<T>;

    List() noexcept : fHead(nullptr), fTail(nullptr), fSize(0) {}

    List(const List& aOther) : fSize(aOther.fSize) {
        if (aOther.fHead) {
            fHead = DoublyLinkedList<T>::makeNode(aOther.fHead->fData);
            fHead->fPrevious.reset();
            Node current = fHead;
            Node otherCurrent = aOther.fHead->fNext;

            while (otherCurrent) {
                current->fNext = DoublyLinkedList<T>::makeNode(otherCurrent->fData);
                current->fNext->fPrevious = current;
                current = current->fNext;
                otherCurrent = otherCurrent->fNext;
            }

            fTail = current;
        }
        else {
            fHead = fTail = nullptr;
        }
    }

    List& operator=(const List& aOther) {
        if (this != &aOther) {
            List temp(aOther);
            swap(temp);
        }
        return *this;
    }

    List(List&& aOther) noexcept :
        fHead(std::move(aOther.fHead)),
        fTail(std::move(aOther.fTail)),
        fSize(aOther.fSize)
    {
        aOther.fHead = nullptr;
        aOther.fTail = nullptr;
        aOther.fSize = 0;
    }

    List& operator=(List&& aOther) noexcept {
        if (this != &aOther) {
            if (fHead) {
                this->~List();
            }
            fHead = std::move(aOther.fHead);
            fTail = std::move(aOther.fTail);
            fSize = aOther.fSize;
            aOther.fHead = nullptr;
            aOther.fTail = nullptr;
            aOther.fSize = 0;
        }
        return *this;
    }

    void swap(List& aOther) noexcept {
        using std::swap;
        swap(fHead, aOther.fHead);
        swap(fTail, aOther.fTail);
        swap(fSize, aOther.fSize);
    }

    size_t size() const noexcept {
        return fSize;
    }

    template <typename U>
    void push_front(U&& aData) {
        Node newNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

        if (fHead) {
            newNode->fNext = fHead;
            fHead->fPrevious = newNode;
        }
        else {
            fTail = newNode;
        }

        fHead = newNode;
        ++fSize;
    }

    template <typename U>
    void push_back(U&& aData) {
        Node newNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

        if (fTail) {
            newNode->fPrevious = fTail;
            fTail->fNext = newNode;
        }
        else {
            fHead = newNode;
        }

        fTail = newNode;
        ++fSize;
    }

    void remove(const T& aElement) noexcept {
        for (Node current = fHead; current; current = current->fNext) {
            if (current->fData == aElement) {
                if (current == fHead) {
                    fHead = current->fNext;
                }
                if (current == fTail) {
                    fTail = current->fPrevious.lock();
                }
                current->isolate();
                --fSize;
                break;
            }
        }
    }

    const T& operator[](size_t aIndex) const {
        if (aIndex >= fSize) {
            throw std::out_of_range("List index out of bounds");
        }

        Node current = fHead;
        for (size_t i = 0; i < aIndex; ++i) {
            current = current->fNext;
        }
        return current->fData;
    }

    Iterator begin() const noexcept {
        return Iterator(fHead, fTail);
    }

    Iterator end() const noexcept {
        return Iterator(fHead, fTail).end();
    }

    Iterator rbegin() const noexcept {
        return Iterator(fHead, fTail).rbegin();
    }

    Iterator rend() const noexcept {
        return Iterator(fHead, fTail).rend();
    }
};
