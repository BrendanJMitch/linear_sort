#include "bucket_sort.hpp"

#include <algorithm>
#include <forward_list>
#include <functional>
#include <iostream>
#include <vector>

namespace {
    std::function<int(double)> createLinearMapping(double inputMin, double inputMax, int outputSize) {
        const double linear_mapping_slope = (outputSize) / (inputMax - inputMin);
        const double linear_mapping_offset = -inputMin * linear_mapping_slope;
        return [linear_mapping_slope, linear_mapping_offset, outputSize](double value) {
            int index = int(linear_mapping_slope * value + linear_mapping_offset);
            if (index < 0) index = 0;
            if (index >= outputSize) index = outputSize - 1;
            return index;
        };
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
}

/**
 * @brief Sort a vector of numeric data in O(n) time .
 *
 *
 * @param data A reference to a vector of unsorted numeric data
 * @param bucketsPerItem The number of buckets to use per item
 */
void bucketSort(std::vector<double>& data, double bucketsPerItem = 1) {
    if (data.size() == 0) {
        return;
    }
    if (bucketsPerItem <= 0) {
        throw std::invalid_argument("bucketsPerItem must be greater than 0");
    }
    int numBuckets = static_cast<int>(data.size() * bucketsPerItem);
    if (numBuckets < 1) {
        numBuckets = 1;
    }
    std::vector<std::forward_list<double>> buckets(numBuckets);

    // Create a mapping of values to bucket indices
    const auto [min, max] = std::ranges::minmax_element(data);
    if (*min == *max) {
        return;
    }
    const std::function<int(double)> linearMapping = createLinearMapping(*min, *max, numBuckets);

    // Map the data to buckets
    for (double value : data) {
        unsigned int index = linearMapping(value);
        if (index > buckets.size()) {
            std::cout << linearMapping(0) << " " << linearMapping(10) << std::endl;
        }
        buckets.at(index).push_front(value);
    }

    int index = 0;
    for (const std::forward_list<double>& bucket : buckets) {
        for (double value : bucket) {
            data.at(index++) = value;
        }
    }
    insertionSort(data);
    return;
}
