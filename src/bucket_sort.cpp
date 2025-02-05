#include "bucket_sort.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <forward_list>
#include <functional>
#include <iostream>
#include <vector>

namespace {
    auto createLinearMapping(double inputMin, double inputMax, int outputSize) {
        const double linearMappingSlope = (outputSize) / (inputMax - inputMin);
        const double linearMappingOffset = -inputMin * linearMappingSlope;
        return [linearMappingSlope, linearMappingOffset, outputSize](double value) {
            int index = int(linearMappingSlope * value + linearMappingOffset);
            if (index < 0) index = 0;
            if (index >= outputSize) index = outputSize - 1;
            return index;
        };
    }

    std::pair<double, double> minMax(const std::vector<double>& data) {
        double min = data.at(0);
        double max = data.at(0);
        for (double item : data) {
            if (item < min) min = item;
            if (item > max) max = item;
        }
        return std::pair<double, double> {min, max};
    }

    void insertionSort(std::vector<double>& data) {
        double temp;
        int j;
        for (unsigned int i = 1; i < data.size(); i++) {

            temp = data.at(i);
            j = i - 1;
            while (j >= 0 && temp < data.at(j)) {
                data.at(j + 1) = data.at(j);
                j--;
            }
            data.at(j + 1) = temp;
        }
    }

    class Bucket {

      public:
        Bucket(const int startingSize) :
            size(startingSize), numItems(0), items(new double[startingSize]) { }

        Bucket(const Bucket& other) : size(other.size), numItems(0), items(new double[other.size]) { }

        ~Bucket() { delete[] items; }

        void add(double item) {
            if (numItems == size) resize();
            items[numItems++] = item;
        }

        double* begin() { return items; }

        double* end() { return items + numItems; }

        const double* begin() const { return items; }

        const double* end() const { return items + numItems; }

      private:
        int size;
        int numItems;
        double* items;

        void resize() {
            int newSize = size * 2;
            double* newItems {new double[newSize]};
            std::memcpy(newItems, items, numItems * sizeof(double));
            delete[] items;
            items = newItems;
            size = newSize;
        }
    };

    Bucket* getBuckets(int numBuckets, int bucketSize) {
        Bucket* buckets = static_cast<Bucket*>(operator new[](numBuckets * sizeof(Bucket)));

        for (int i = 0; i < numBuckets; ++i) {
            new (&buckets[i]) Bucket(bucketSize);
        }
        return buckets;
    }
}

/**
 * @brief Sort a vector of numeric data using a bucket sort algorithm.
 *
 *
 * @param data A reference to a vector of unsorted numeric data
 * @param bucketsPerItem The number of buckets to use per item
 */
void bucketSort(std::vector<double>& data, double bucketsPerItem = 1) {
    if (data.size() == 0) return;

    if (bucketsPerItem <= 0) throw std::invalid_argument("bucketsPerItem must be greater than 0");

    int numBuckets = static_cast<int>(data.size() * bucketsPerItem);
    if (numBuckets < 1) numBuckets = 1;

    int bucketSize = std::ceil(1.5 / bucketsPerItem);
    if (bucketSize < 1) bucketSize = 1;

    Bucket* buckets = getBuckets(numBuckets, bucketSize);

    // Create a mapping of values to bucket indices
    const auto [min, max] = minMax(data);
    if (min == max) return;

    const std::function<int(double)> linearMapping = createLinearMapping(min, max, numBuckets);

    // Map the data to buckets
    for (double value : data) {
        buckets[linearMapping(value)].add(value);
    }

    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (double value : buckets[i]) {
            data.at(index++) = value;
        }
        buckets[i].~Bucket();
    }
    operator delete[](buckets);

    insertionSort(data);
    return;
}
