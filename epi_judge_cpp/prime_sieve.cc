#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
    if( n < 2)
        return {};

    auto primes = std::vector<bool>(n+1, true);
    primes[0] = false;
    primes[1] = false;
    auto num = int{2};
    while( num <= n)
    {
        for( auto i = num + num; i <= n; i += num)
        {
            primes[i] = false;
        }
        num = std::distance(primes.begin()
                           ,std::find(primes.begin()+ num + 1, primes.end(), true));
    }

    auto prime_numbers = std::vector<int>{};
    for(auto i = 0; i <= n; ++i)
        if(primes[i])
            prime_numbers.emplace_back(i);
  
    return prime_numbers;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
