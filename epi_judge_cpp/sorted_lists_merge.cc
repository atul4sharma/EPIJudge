#include "list_node.h"
#include "test_framework/generic_test.h"

auto append_node(shared_ptr<ListNode<int>> * node,
                 shared_ptr<ListNode<int>> * tail)
    -> void
{
    (*tail)->next = *node;
    *tail = *node;
    *node = (*node)->next;
}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> l1,
                                              shared_ptr<ListNode<int>> l2) {
    auto dummy_head = std::make_shared<ListNode<int>>();
    auto tail       = dummy_head;

    while( l1 != nullptr && l2 != nullptr )
        append_node( l1->data <= l2->data ? &l1: &l2, &tail);

    tail->next = l1 != nullptr ? l1 : l2;
    return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
