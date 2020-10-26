#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

auto is_symmetric(std::unique_ptr<BinaryTreeNode<int>> const & left_subtree
                 ,std::unique_ptr<BinaryTreeNode<int>> const & right_subtree)
    -> bool
{
    if(left_subtree == nullptr && right_subtree == nullptr)
    {
        return true;
    }
    else if(left_subtree != nullptr && right_subtree != nullptr)
    {
        return left_subtree->data == right_subtree->data
               &&
               is_symmetric(left_subtree->left, right_subtree->right)
               &&
               is_symmetric(left_subtree->right, right_subtree->left);
    }
    return false;
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return tree == nullptr || is_symmetric(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
