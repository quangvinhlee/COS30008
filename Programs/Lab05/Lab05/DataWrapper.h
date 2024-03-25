#pragma once

#include "Map.h"
#include <string>
#include <fstream> // For file operations

using DataMap = Map<size_t, size_t>;

class DataWrapper {
private:
    size_t fSize;
    DataMap* fData;

public:
    // Constructor (initialize fSize and fData to 0 and nullptr)
    DataWrapper() : fSize(0), fData(nullptr) {}

    // Destructor (free memory allocated for fData using delete[])
    ~DataWrapper() {
        delete[] fData;
    }

    // Disallow copying (deleted copy constructor and assignment operator)
    DataWrapper(const DataWrapper&) = delete;
    DataWrapper& operator=(const DataWrapper&) = delete;

    // load() function (takes file name, returns true on success)
    bool load(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            return false; // Error: could not open file
        }

        // Read the size of the data
        size_t dataSize;
        file >> dataSize;

        // Allocate memory for fData based on dataSize
        fData = new DataMap[dataSize];

        // Read key-value pairs and populate fData
        for (size_t i = 0; i < dataSize; ++i) {
            size_t key, value;
            file >> key >> value;
            fData[i] = DataMap(key, value);
        }

        fSize = dataSize; // Update fSize after successful loading

        return true;
    }

    // size() function (returns the size of the data array)
    size_t size() const noexcept {
        return fSize;
    }

    // Indexer operator[] (returns a constant reference to the Map object at index)
    const DataMap& operator[](size_t index) const {
        if (index >= fSize) {
            // Handle potential out-of-bounds access (throw exception or return default value)
            throw std::out_of_range("Index out of bounds");
        }
        return fData[index];
    }
};
