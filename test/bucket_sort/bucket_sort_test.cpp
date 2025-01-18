#include "bucket_sort.hpp"

#include <gtest/gtest.h>
#include <random>
#include <vector>

testing::AssertionResult isSorted(std::vector<double> data) {
    if (data.size() == 0) {
        return testing::AssertionSuccess();
    }
    std::vector<double>::const_iterator end = data.cend() - 1;
    for (std::vector<double>::const_iterator it = data.cbegin(); it != end; it++) {
        if (*it > *(it + 1)) {
            return testing::AssertionFailure() << *it << " > " << *(it + 1);
        }
    }
    return testing::AssertionSuccess();
}

// ====================================== TEST SORTS SPECIFIC DATA ====================================== //

std::map<std::string, std::vector<double>> specificTestData {
    {                "EmptyList",                                          {}},
    {      "SinglePositiveValue",                                       {1.0}},
    {      "SingleNegativeValue",                                      {-1.0}},
    {"PositiveAndNegativeValues",                                 {1.0, -1.0}},
    {       "UnevenDistribution", {-9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9}},
};

class SpecificInput : public testing::TestWithParam<std::pair<const std::string, std::vector<double>>> { };

TEST_P(SpecificInput, SortsVector) {
    std::vector<double> input = GetParam().second;
    EXPECT_NO_THROW(bucketSort(input, 1));
    EXPECT_TRUE(isSorted(input));
}

INSTANTIATE_TEST_SUITE_P(BucketSortTest,
                         SpecificInput,
                         testing::ValuesIn(specificTestData),
                         [](const auto& paramInfo) { return paramInfo.param.first; });

// ===================================== TEST SORTS GENERATED DATA ====================================== //

struct GenerateInputParams {
    double max_val;
    double min_val;
    int length;
    double buckets_per_item;
};

std::map<std::string, GenerateInputParams> generateTestData {
    {            "NegativeData",    {-10, 0, 100, 1}},
    {            "PositiveData",     {0, 10, 100, 1}},
    {       "TightlyPackedData",   {0, 1e-8, 100, 1}},
    {           "DuplicateData",      {1, 1, 100, 1}},
    {            "LargeDataset", {0, 10, 1000000, 1}},
    {    "FewerBucketsThanData",   {0, 10, 100, 0.5}},
    {     "MoreBucketsThanData",   {0, 10, 100, 1.5}},
    {"MuchFewerBucketsThanData",  {0, 10, 100, 0.01}},
    { "ManyMoreBucketsThanData",   {0, 10, 100, 100}},
    {       "LessThanOneBucket", {0, 10, 100, 0.001}},
};

class GenerateInput : public testing::TestWithParam<std::pair<const std::string, GenerateInputParams>> { };

TEST_P(GenerateInput, SortsVector) {
    auto& [max_val, min_val, length, buckets_per_item] = GetParam().second;

    std::mt19937 random_engine {0};
    std::uniform_real_distribution<double> data_distribution {max_val, min_val};

    auto generator = [&data_distribution, &random_engine]() {
        return data_distribution(random_engine);
    };

    std::vector<double> input(length);
    std::generate(input.begin(), input.end(), generator);
    bucketSort(input, buckets_per_item);

    EXPECT_NO_THROW(bucketSort(input, buckets_per_item));
    EXPECT_TRUE(isSorted(input));
}

INSTANTIATE_TEST_SUITE_P(BucketSortTest,
                         GenerateInput,
                         testing::ValuesIn(generateTestData),
                         [](const auto& paramInfo) { return paramInfo.param.first; });

// ======================================= TEST THROWS EXCEPTIONS ======================================= //

std::map<std::string, double> badBucketsPerItemValues {
    {    "ZeroBuckets",  0},
    {"NegativeBuckets", -1}
};

class InvalidValues : public testing::TestWithParam<std::pair<const std::string, double>> { };

TEST_P(InvalidValues, ThrowsInvalidArgument) {
    double buckets_per_item = GetParam().second;
    std::vector<double> dummyData {1, 2, 3, 4, 5};
    EXPECT_THROW(bucketSort(dummyData, buckets_per_item), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(BucketSortTest,
                         InvalidValues,
                         testing::ValuesIn(badBucketsPerItemValues),
                         [](const auto& paramInfo) { return paramInfo.param.first; });