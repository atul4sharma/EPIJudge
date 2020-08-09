#include <string>

#include "test_framework/generic_test.h"
using std::string;

auto next_number(std::string const & s)
    -> std::string
{
    auto       first = s.begin();
    auto const last  = s.end();
    auto       temp  = std::string{};
    while(first != last)
    {
        auto const character = *first;
        auto const next_char = std::find_if(first
                                           ,last
                                           ,[&character] (char const ch) {
                                                return ch != character;
                                           });

        auto count = std::distance(first
                                  ,next_char);
        temp += std::to_string(count) + std::string{character};
        first = next_char;
    }
    return temp;
}

string LookAndSay(int n) {
  auto result = std::string{"1"};
  for( auto i = 1; i < n; ++i )
      result = next_number(result);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
