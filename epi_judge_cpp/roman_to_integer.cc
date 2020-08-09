#include <string>

#include "test_framework/generic_test.h"
using std::string;

auto roman_to_integer_impl(std::string const & s)
    -> int
{
    auto const mapping = std::map<char, int>{
                                             {'I', 1}
                                            ,{'V', 5}
                                            ,{'X', 10}
                                            ,{'L', 50}
                                            ,{'C', 100}
                                            ,{'D', 500}
                                            ,{'M', 1000}
                                            };
    auto result = int{};
    auto prev_value = std::numeric_limits<int>::min();
    auto curr_value = int{};
    for( auto i = static_cast<int>(s.size()) - 1; i >= 0; --i)
    {
        curr_value = mapping.at(s[i]);
        if( curr_value >= prev_value )
            result += curr_value;
        else
            result -= curr_value;
        prev_value = curr_value;
    }
    return result;
}

int RomanToInteger(const string& s) {
  return roman_to_integer_impl(s);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
                         &RomanToInteger, DefaultComparator{}, param_names);
}
