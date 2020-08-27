#include <stdexcept>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::length_error;

class Stack {

    struct element{
        int const data;
        int const max;

        element(int d, int m)
            :data(std::move(d))
            ,max(std::move(m))
        {}

    };

    std::stack<element> underlying_container;

 public:
  bool Empty() const {
    return underlying_container.empty();
  }

  int Max() const {
    return underlying_container.top().max;
  }

  int Pop() {
    auto const return_value = underlying_container.top().data;
    underlying_container.pop();
    return return_value;
  }

  void Push(int x) {
    if( underlying_container.empty() )
        underlying_container.emplace(x, x);
    else
        underlying_container.emplace(x, x > underlying_container.top().max ? x : underlying_container.top().max);
    return;
  }

};
struct StackOp {
  std::string op;
  int argument;
};

namespace test_framework {
template <>
struct SerializationTrait<StackOp> : UserSerTrait<StackOp, std::string, int> {};
}  // namespace test_framework

void StackTester(const std::vector<StackOp>& ops) {
  try {
    Stack s;
    for (auto& x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
