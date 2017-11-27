#include "random.hpp"

#include <algorithm>

namespace Base {

std::vector<int> Partition::Uniform(int num_elements, int num_buckets, int min_val) {
    num_elements -= num_buckets * min_val;

    std::vector<int> delimiters = UniqueNumbers((int)0, num_elements + num_buckets - 1, num_buckets - 1);

    std::sort(delimiters.begin(), delimiters.end());

    delimiters.push_back(num_elements + num_buckets - 1);

    delimiters.insert(delimiters.begin(), -1);

    std::vector<int> sizes;

    for (int i = 1; i <= num_buckets; i += 1) {
        sizes.push_back(delimiters[i] - delimiters[i - 1] - 1 + min_val);
    }

    return sizes;
};

std::vector<int> RandomPermutation(int num_elements, int start_element) {
    std::vector<int> permutation(num_elements);
    int sum = start_element;

    for (auto& itr : permutation) {
        itr = sum;
        sum += 1;
    }

    random_shuffle(permutation.begin(), permutation.end());
    return permutation;
}

}  // namespace Base
