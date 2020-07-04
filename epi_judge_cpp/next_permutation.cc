#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> NextPermutation(vector<int> perm) {
  return std::next_permutation(perm.begin(), perm.end())
         ? perm
         : std::vector<int>{};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
