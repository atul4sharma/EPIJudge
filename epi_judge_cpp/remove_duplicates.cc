#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::string;
using std::vector;

struct Name {
  bool operator<(const Name& that) const {
    return first_name != that.first_name ? first_name < that.first_name
                                         : last_name < that.last_name;
  }

  string first_name, last_name;
};
void EliminateDuplicate(vector<Name>* names) {
  auto & names_ = *names;
  std::sort(names_.begin(), names_.end());
  names_.erase(std::unique(names_.begin(),
                           names_.end(),
                           [](Name const & a, Name const & b){
                            return !(a < b) && !(b < a); 
                           }),
                names_.end());
  return;
}

namespace test_framework {
template <>
struct SerializationTrait<Name> : UserSerTrait<Name, std::string, std::string> {
};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Name& n) {
  return out << n.first_name;
}

vector<Name> EliminateDuplicateWrapper(vector<Name> names) {
  EliminateDuplicate(&names);
  return names;
}

bool Comp(vector<std::string> expected, vector<Name> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return std::equal(
      begin(expected), end(expected), begin(result), end(result),
      [](const std::string& s, const Name& n) { return s == n.first_name; });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"names"};
  return GenericTestMain(args, "remove_duplicates.cc", "remove_duplicates.tsv",
                         &EliminateDuplicateWrapper, &Comp, param_names);
}
