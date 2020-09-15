#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::vector;

auto preorder_traversal_impl(std::unique_ptr<BinaryTreeNode<int>> const & tree)
    -> std::vector<int>
{
    auto result = std::vector<int>{};
    auto s      = std::stack<BinaryTreeNode<int> const *>{};
    s.emplace(tree.get());

    while(!s.empty())
    {
        auto curr = s.top();
        s.pop();
        if(curr)
        {
            result.emplace_back(curr->data);
            s.emplace(curr->right.get());
            s.emplace(curr->left.get());
        }
        
    }
    return result;
}

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return preorder_traversal_impl(tree);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
