#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

auto shift_forward(char s[], int start, int & end)
{
    for(auto i = end; i > start; --i)
    {
        s[i] = s[i-1];
    }
    s[start] = 'd';
    ++end;
}


int ReplaceAndRemove(int size, char s[]) {
    // TODO : Can be improved
  auto current_end = static_cast<int>(std::distance(s, std::remove(s, s+size, 'b')));

  for(auto i = 0; i < current_end; ++i)
  {
    if(s[i] == 'a')
    {
        s[i] = 'd';
        shift_forward(s, i+1, current_end);
    }
  }

  return current_end;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
