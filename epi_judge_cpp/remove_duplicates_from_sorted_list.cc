#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
    auto temp = L;
    while( temp != nullptr && temp->next != nullptr)
    {
        auto next_node = temp->next;
        if(temp->data == next_node->data)
            temp->next = next_node->next;
        else
            temp = next_node;
    }
    return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
