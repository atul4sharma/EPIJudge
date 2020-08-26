#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  std::stack<char> container;

  for(auto i = 0; i < static_cast<int>(s.size()); ++i)
  {
      if( container.empty() )
      {
          container.emplace(s[i]);
      }
      else
      {
          auto prev_char = container.top();
          if( (s[i] == '}' && prev_char == '{')
              ||
              (s[i] == ')' && prev_char == '(')
              ||
              (s[i] == ']' && prev_char == '[')
            )
          {
              container.pop();
          }
          else
          {
              container.emplace(s[i]);
          }
      }
  }

  return container.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
