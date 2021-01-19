#include "test_framework/generic_test.h"

auto fib_impl(std::vector<int> & fib, int n) 
{
    if( n < 2 )
        return n;

    if( fib[n] == -1)
        fib[n] = fib_impl(fib, n-1) + fib_impl(fib, n-2);
    
    return fib[n];
}

int Fibonacci(int n) {
  auto fib = std::vector<int>(n+1, -1);
  return fib_impl(fib, n);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
