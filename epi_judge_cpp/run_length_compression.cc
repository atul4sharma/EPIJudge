#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string Decoding(const string &s) {
    auto       result = std::string{};
    auto       first  = s.begin();
    auto const last   = s.end();
    while( first != last )
    {
        auto const current_character = std::find_if(first
                                                   ,last
                                                   ,[] (unsigned char const c) {
                                                      return std::isalpha(c);
                                                   });
        auto const count = std::stoi(s.substr(std::distance(s.begin(), first)
                                             ,std::distance(first, current_character)));
        result += std::string(count, *current_character);
        first = std::next(current_character);
    }
    return result;
}

string Encoding(const string &s) {
  auto       result = std::string{};
  auto       first  = s.begin();
  auto const last   = s.end();
  while( first != last )
  {
      auto const character = *first;
      auto next_char = std::find_if(first
                                   ,last
                                   ,[&character] (char const ch) {
                                       return ch != character;
                                   });
      auto const count = std::distance(first, next_char);
      result += std::to_string(count) + character;

      first = next_char;
  }
  return result;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
