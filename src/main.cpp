#include "bucket_sort.hpp"

#include <iostream>
#include <random>
#include <vector>

int main() {
    double min_val = 0;
    double max_val = 10;
    int length = 1000000;
    double buckets_per_item = 0.2;

    std::mt19937 random_engine {0};
    std::uniform_real_distribution<double> data_distribution {max_val, min_val};

    auto generator = [&data_distribution, &random_engine]() {
        return data_distribution(random_engine);
    };

    std::vector<double> input(length);
    std::generate(input.begin(), input.end(), generator);
    bucketSort(input, buckets_per_item);
}
