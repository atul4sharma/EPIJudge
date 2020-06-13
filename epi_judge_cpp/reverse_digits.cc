#include "test_framework/generic_test.h"
long long Reverse(int x) {
  long long result = 0;
  auto x_ = std::abs(x);
  while(x_){
      result = (result * 10) + (x_ % 10);
      x_ /= 10;
  }

  return x < 0 ? -1 * result : result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
