#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  return std::to_string(x);
}

int StringToInt(const string& s) {
  if( s.empty() )
      return 0;
  int i   = 0;
  int num = 0;
  auto const is_positive = [&i, &s] () {
      if( s[i] == '-' )
      {
          ++i;
          return false;
      }
      else if( s[i] == '+' )
      {
          ++i;
      }
      return true;
  }();

  for( ; i < static_cast<int>(s.size()); ++i)
  {
      num = (num * 10) + (s[i] - '0');
  }

  return is_positive ? num : -num;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
