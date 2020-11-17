#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

auto merge_vectors(std::vector<std::vector<int>> const & sorted_arrays
                  ,std::size_t                   const & start
                  ,std::size_t                   const & end)
    -> std::vector<int>
{
    if( start == end)
        return sorted_arrays.at(start);
    if( start + 1 == end )
    {
        auto result = std::vector<int>{};
        auto const & left  = sorted_arrays.at(start);
        auto const & right = sorted_arrays.at(end);

        std::merge(left.begin(), left.end()
                  ,right.begin(), right.end()
                  ,std::back_inserter(result));
        return result;
    }
    auto mid = (start + end) / 2;

    auto result = std::vector<int>{};
    auto left_sorted  = merge_vectors(sorted_arrays, start, mid);
    auto right_sorted = merge_vectors(sorted_arrays, mid+1, end);

    std::merge(left_sorted.begin(), left_sorted.end()
              ,right_sorted.begin(), right_sorted.end()
              ,std::back_inserter(result));
    return result;
}

// TODO: make this better
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  return merge_vectors(sorted_arrays, 0, sorted_arrays.size() - 1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
