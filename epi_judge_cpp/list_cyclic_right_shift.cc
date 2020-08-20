#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

auto list_length(std::shared_ptr<ListNode<int>> l)
    -> int
{
    auto count = 0;
    while( l )
    {
        l = l->next;
        ++count;
    }
    return count;
}

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
    auto dummy_head = std::make_shared<ListNode<int>>();

    auto const size = list_length(L);
    if( size == 0 )
        return nullptr;
    auto       move_after = size - (k%size);

    if( move_after == 0 || move_after == size)
        return L;

    auto iter = L;
    while( --move_after > 0)
        iter = iter->next;

    dummy_head->next = iter->next;
    iter->next = nullptr;

    iter = dummy_head->next;
    while(iter->next != nullptr)
        iter = iter->next;

    iter->next = L;
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
