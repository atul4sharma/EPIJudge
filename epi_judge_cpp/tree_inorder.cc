#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

#if 0
auto inorder_traversal_impl(std::unique_ptr<BinaryTreeNode<int>> const & node)
    -> std::vector<int>
{
    if( node == nullptr)
        return {};

    auto left_res = inorder_traversal_impl(node->left);
    left_res.emplace_back(node->data);
    auto right_res = inorder_traversal_impl(node->right);
    left_res.insert(left_res.end(), right_res.begin(), right_res.end());

    return left_res;
}

#else

auto inorder_traversal_impl(std::unique_ptr<BinaryTreeNode<int>> const & node)
    -> std::vector<int>
{
    auto s = std::stack<const BinaryTreeNode<int>*>{};
    auto const * curr = node.get();
    auto result = std::vector<int>{};

    while(!s.empty() || curr )
    {
        if(curr)
        {
            s.push(curr);
            curr = curr->left.get();
        }
        else
        {
            curr = s.top();
            s.pop();
            result.emplace_back(curr->data);
            curr = curr->right.get();
        }
    }

    return result;
}

#endif

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return inorder_traversal_impl(tree);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
