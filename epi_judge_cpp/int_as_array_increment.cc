#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  if( A.empty() )
      return {};

  auto const first = A.begin();
  auto       last  = std::prev(A.end());
  ++(*last);
  auto carry = 0;
  for(; first != last; --last)
  {
      *last += carry;
      carry = *last / 10;
      *last %= 10;
  }

  *(A.begin()) += carry;
  carry = *(A.begin()) / 10;
  *(A.begin()) %= 10;

  if( carry )
  {
      A.insert(A.begin(), carry);
  }
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
