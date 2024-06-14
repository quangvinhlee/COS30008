#include "VigenereForwardIterator.h"
#include <iostream>
#include <string>

void VigenereForwardIterator::initializeTable()
{
    for (char row = 0; row < CHARACTERS; row++)
    {
        char lChar = 'B' + row;
        for (char column = 0; column < CHARACTERS; column++)
        {
            if (lChar > 'Z')
                lChar = 'A';
            fMappingTable[row][column] = lChar++;
        }
    }
}

VigenereForwardIterator::VigenereForwardIterator(
    const std::string& aKeyword,
    const std::string& aSource,
    EVigenereMode aMode 
) noexcept :
    fMode(aMode),
    fKeys(aKeyword, aSource),
    fSource(aSource),
    fIndex(0)
{
    initializeTable();  
    if (fKeys != fKeys.end()) {  
        if (aMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        }
        else {
            decodeCurrentChar();
        }
    }
}


void VigenereForwardIterator::encodeCurrentChar() noexcept {
    char currentChar = fSource[fIndex];
    if (isalpha(currentChar)) {
        bool isUpperCase = isupper(currentChar);
        char keywordChar = *fKeys;
        //std::cout << keywordChar << std::endl;

        char encodedChar;

        currentChar = toupper(currentChar);
        encodedChar = fMappingTable[keywordChar - 'A'][currentChar - 'A'];
        //std::cout << encodedChar << std::endl;

        fCurrentChar = isUpperCase ? encodedChar : tolower(encodedChar);
        //std::cout << fCurrentChar << std::endl;
        ++fKeys;
    }
    else {
        fCurrentChar = currentChar;
    }
}

void VigenereForwardIterator::decodeCurrentChar() noexcept {
    char currentChar = fSource[fIndex];

    if (isalpha(currentChar)) {
        bool isUpperCase = isupper(currentChar);
        char keywordChar = *fKeys;
        char decodedChar;

        currentChar = toupper(currentChar);

        char* column = std::find(fMappingTable[keywordChar - 'A'], fMappingTable[keywordChar - 'A'] + CHARACTERS, currentChar);
        if (column != fMappingTable[keywordChar - 'A'] + CHARACTERS) {
            decodedChar = 'A' + (column - fMappingTable[keywordChar - 'A']);
        }
        else {
            decodedChar = currentChar;
        }

        fCurrentChar = isUpperCase ? decodedChar : tolower(decodedChar);

        ++fKeys;
    }
    else {
        fCurrentChar = currentChar;
    }
}

char VigenereForwardIterator::operator*() const noexcept { 
        return fCurrentChar;  
}

VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept {

    ++fIndex;
    if (fIndex < fSource.size()) {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        }
        else {
            decodeCurrentChar();
        }
    }

    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept {
    VigenereForwardIterator temp = *this;
    operator++();
    return temp;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept {
    return fSource == aOther.fSource && fIndex == aOther.fIndex;
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept {
    return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const noexcept
{
    VigenereForwardIterator temp(*this);
    temp.fIndex = 0;
    return temp;
}

VigenereForwardIterator VigenereForwardIterator::end() const noexcept
{
    VigenereForwardIterator temp(*this);
    temp.fIndex = fSource.size();
    return temp;
}