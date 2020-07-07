#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

#define MAPPINGS \
    member(0, 0), \
    member(1, 1), \
    member(2, 2), \
    member(3, 3), \
    member(4, 4), \
    member(5, 5), \
    member(6, 6), \
    member(7, 7), \
    member(8, 8), \
    member(9, 9), \
    member(A, 10), \
    member(B, 11), \
    member(C, 12), \
    member(D, 13), \
    member(E, 14), \
    member(F, 15)

#define member(x, y) {#x, y}
static auto const string_to_int_mappings = std::unordered_map<std::string, int>{
    MAPPINGS
};

#undef member
#define member(x, y) {y, #x}
static auto const int_to_string_mappings = std::unordered_map<int, std::string>{
    MAPPINGS
};

auto to_base_10(std::string const & num_as_string, int from_b)
    -> int
{
    if( num_as_string.empty() )
        return 0;
    auto num = 0;
    for(char c : num_as_string)
    {
        num = (num * from_b) + string_to_int_mappings.at(std::string{c});
    }
    return num;
}

auto from_base_10(int num, int to_b)
    -> std::string
{
    if( num == 0 )
        return std::string{"0"};
    auto result = std::string{};
    while( num )
    {
        result += int_to_string_mappings.at(num % to_b);
        num /= to_b;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
  auto const is_positive = num_as_string.front() != '-';
  auto const number      = num_as_string.substr( is_positive ? 0 : 1);
  auto const result      = from_base_10(to_base_10(number, b1), b2);
  return is_positive ? result : std::string{ "-" + result};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
