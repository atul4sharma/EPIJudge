#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
    auto even_start = L;
    auto odd_start  = L;
    if( L && L->next )
        odd_start = L->next;
    else
        return even_start;

    auto even_iter = even_start;
    auto odd_iter = odd_start;
    while(even_iter && even_iter->next && odd_iter && odd_iter->next)
    {
        even_iter->next       = odd_iter->next;
        odd_iter->next        = odd_iter->next->next;
        even_iter->next->next = odd_start;

        even_iter = even_iter->next;
        odd_iter  = odd_iter->next;
    }
    return even_start;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
