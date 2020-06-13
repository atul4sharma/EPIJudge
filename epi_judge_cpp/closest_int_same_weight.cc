#include "test_framework/generic_test.h"

long long SwapBits(long long x, int i, int j) {
  // TODO - you fill in here.
  if( ((x >> i) & 1) != ((x >> j) & 1) )
  {
      auto bit_mask = (1L << i) | (1L << j);
      x ^= bit_mask;
  }
  return x;
}

unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  for(auto i = 0; i < 63; ++i)
  {
      if( ((x >> i) & 1) != ((x >> (i+1)) & 1) )
      {
          x = SwapBits(x, i, i+1);
          break;
      }
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
