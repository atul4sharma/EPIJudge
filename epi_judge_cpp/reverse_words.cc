#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {
  std::string & res = *s;
  std::reverse(res.begin(), res.end());
  auto first = res.begin();
  auto last  = res.end();
  while(first != last)
  {
      auto next_space = std::find_if(first
                                    ,last
                                    ,[] (char const ch) {
                                        return std::isspace(ch);
                                    });
      std::reverse(first, next_space);
      first = std::find_if_not(next_space
                              ,last
                              ,[] (char const ch) {
                                  return std::isspace(ch);
                              });
  }
  return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
