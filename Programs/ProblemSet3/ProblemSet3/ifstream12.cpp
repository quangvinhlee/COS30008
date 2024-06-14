#include "ifstream12.h"
#include <iostream>
ifstream12::ifstream12(const char* aFileName, size_t aBufferSize) : fIStream(), fBuffer(nullptr), fBufferSize(aBufferSize), fByteCount(0), fByteIndex(0), fBitIndex(0) {
    if (aFileName != nullptr) {
        open(aFileName);

    }
}

ifstream12::~ifstream12() {
    close();
}

void ifstream12::open(const char* aFileName) {
    close();
    fIStream.open(aFileName, std::ios::binary);
    if (fIStream.is_open()) {

        fIStream.seekg(0, std::ios::end);
        fBufferSize = fIStream.tellg();
        fIStream.seekg(0, std::ios::beg);


        fBuffer = new std::byte[fBufferSize];
        reset();
    }
}

void ifstream12::close() {
    if (fIStream.is_open()) {
        fIStream.close();
    }
    delete[] fBuffer;
    fBuffer = nullptr;
}

bool ifstream12::isOpen() const {
    return fIStream.is_open();
}

bool ifstream12::good() const {
    return fIStream.good();
}

bool ifstream12::eof() const {

    return fByteIndex >= fBufferSize || fIStream.eof();
}

void ifstream12::reset() {
    fByteCount = 0;
    fByteIndex = 0;
    fBitIndex = 7;
}

void ifstream12::fetch_data() {
    fIStream.read(reinterpret_cast<char*>(fBuffer), fBufferSize);
    fByteCount = fIStream.gcount();
}

std::optional<size_t> ifstream12::readBit() {
    if (fByteCount == 0) {
        fetch_data();
    }    

    if (eof()) {
        return std::nullopt; // Reached EOF
    }

    std::byte lByte = fBuffer[fByteIndex] & (std::byte{ 1 } << fBitIndex);
    size_t bitValue = std::to_integer<size_t>(lByte);

    if (bitValue > 1) {
        bitValue = 1;
    }

    //size_t bitValue = (std::to_integer<size_t>(fBuffer[fByteIndex]) >> fBitIndex) & 0x01;
    
    fBitIndex--;
    if (fBitIndex < 0) {
        fByteIndex++;
        fByteCount--; 
        fBitIndex = 7; 
    }

    return bitValue;
}


ifstream12& ifstream12::operator>>(size_t& aValue) {


    aValue = 0;
    for (int i = 1; i <= 12; i++) {
        std::optional<size_t> bit = readBit();
        if (bit == std::nullopt) {
            break;
        }

        if (bit == 1) {
            aValue = aValue + (*bit << (i - 1));
        }
    }
    return *this;
}