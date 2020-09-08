#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

auto sum_root_to_leaf_impl(std::unique_ptr<BinaryTreeNode<int>> const & tree, int partial_sum)
    -> int
{
    if( tree == nullptr )
        return 0;

    partial_sum = partial_sum * 2 + tree->data;
    if( tree->left == nullptr && tree->right == nullptr)
        return partial_sum;

    return sum_root_to_leaf_impl(tree->left, partial_sum) + sum_root_to_leaf_impl(tree->right, partial_sum);
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return sum_root_to_leaf_impl(tree, 0);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
