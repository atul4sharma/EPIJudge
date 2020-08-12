#include <string>

#include "test_framework/generic_test.h"
using std::string;

string SnakeString(const string& s) {
  auto result = s;
  auto j      = 0;

  for(auto i = 1; i < static_cast<int>(s.size()); i+= 4)
      result[j++] = s[i];

  for(auto i = 0; i < static_cast<int>(s.size()); i+= 2)
      result[j++] = s[i];

  for(auto i = 3; i < static_cast<int>(s.size()); i+= 4)
      result[j++] = s[i];

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "snake_string.cc", "snake_string.tsv",
                         &SnakeString, DefaultComparator{}, param_names);
}
