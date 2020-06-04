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

unsigned long long ReverseBits(unsigned long long x) {
  // TODO - you fill in here.
  for( auto i = 0, j = 63; i < 64/2; ++i, --j)
  {
      x = SwapBits(x, i, j);
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
